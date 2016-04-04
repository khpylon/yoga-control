/* Copyright (c) 2016 Ken Hughes <ken.l.hughes@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 */

#include <sys/io.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <gio/gio.h>
#include <sys/stat.h>

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// constants from Y2P-PM code base

#define EC_SC 0x66
#define EC_DATA 0x62
#define IBF 1
#define OBF 0
#define EC_SC_READ_CMD 0x80
#define EC_SC_WRITE_CMD 0x81
#define EC_SC_SCI_CMD 0x84

// additional constants for use with EC code

#define R_EC_KEYBOARD 0x40
#define TABLET_MODE 0x20

// signals for which we listen

#define KEYTOGGLE  SIGUSR1
#define KEYLOCK    SIGUSR2
#define TIMERPOLL  (_NSIG-1)

// lockfile name in /var/run

#define PIDFILE "/var/run/yoga.pid"

// hooks to iio-sensor-proxy on DBus

#define IIOSENSORPROXYBUS  "net.hadess.SensorProxy"
#define IIOSENSORPROXYPATH "/net/hadess/SensorProxy"

static GDBusProxy *iioSensorProxy;
static timer_t timerid;

int ec_init()
{
    if (ioperm(EC_DATA, 1, 1) != 0 || ioperm(EC_SC, 1, 1) != 0)
        return -1;
    return 0;
}

uint8_t wait_ec(const uint32_t port, const uint32_t flag, const char value)
{
    uint8_t data;
    int i;

    i = 0;
    data = inb(port);

    while ( (((data >> flag) & 0x1) != value) && (i++ < 100) )
    {
        usleep(1000);
        data = inb(port);
    }

    if (i >= 100)
    {
        return 0;
    }
    return 1;
}

uint8_t read_ec(const uint32_t port, uint8_t *value)
{

    if (!wait_ec(EC_SC, IBF, 0)) return 0;
    outb(EC_SC_READ_CMD, EC_SC);
    if (!wait_ec(EC_SC, IBF, 0)) return 0;
    outb(port, EC_DATA);
    if (!wait_ec(EC_SC, OBF, 1)) return 0;
    *value = inb(EC_DATA);

    return 1;
}

uint8_t write_ec(const uint32_t port, const uint8_t value)
{
    if (!wait_ec(EC_SC, IBF, 0)) return 0;
    outb(EC_SC_WRITE_CMD, EC_SC);
    if (!wait_ec(EC_SC, IBF, 0)) return 0;
    outb(port, EC_DATA);
    if (!wait_ec(EC_SC, IBF, 0)) return 0;
    outb(value, EC_DATA);
    if (!wait_ec(EC_SC, IBF, 0)) return 0;
    return 1;
}

static bool
forkCommand (char **args)
{
  pid_t childPID = fork();

  if (childPID >= 0) // fork was successful
  {
    if (childPID == 0) // child process
    {
      execv( args[0], args );
    }
    return false;
  }
  else // fork failed
  {
    return true;
  }
}

#define TOUCHPAD "SYNA2B29:00 06CB:77C6"

static bool touchpadEnabled;
static char *touchpadArgs[] = {"/usr/bin/xinput", NULL, TOUCHPAD, NULL};
static enum States state;
static bool keyboardEnabled;

static void
restoreTouchpad (void)
{
  touchpadArgs[1] = (touchpadEnabled) ? "enable" : "disable";
  forkCommand (touchpadArgs);
}

static void
toggleTouchpad (void)
{
  touchpadEnabled = ~touchpadEnabled;
  restoreTouchpad ();
}

static void
disableTouchpad (void)
{
  touchpadArgs[1] = "disable";
  forkCommand (touchpadArgs);
}

static char
*xrandrArgs[] = {"/usr/bin/xrandr", 
                 "--output", "eDP1",
                 "--rotate", NULL, NULL};

static void
xrandr (char *data)
{
  if (!strcmp (data,"left-up"))
  {
    xrandrArgs[4] = "left";
  } else if (!strcmp (data,"right-up"))
  {
    xrandrArgs[4] = "right";
  } else if (!strcmp (data,"bottom-up"))
  {
    xrandrArgs[4] = "inverted";
  } else 
  {
    xrandrArgs[4] = "normal";
  }
#if 0
  printf ("%s %s %s %s %s\n", xrandrArgs[0], xrandrArgs[1], 
   xrandrArgs[2], xrandrArgs[3], xrandrArgs[4]);
#endif
  
  forkCommand (xrandrArgs);
}

static char
*onboardArgs[] = {"/usr/bin/dbus-send",
                 "--type=method_call",
                  "--dest=org.onboard.Onboard",
                  "/org/onboard/Onboard/Keyboard",
                  NULL,
                 "--system",
                  NULL};

static void
enableKeyboard (void)
{
  onboardArgs[4] = "org.onboard.Onboard.Keyboard.Show";
  // forkCommand (onboardArgs);
}

static void
disableKeyboard (void)
{
  onboardArgs[4] = "org.onboard.Onboard.Keyboard.Hide";
  // forkCommand (onboardArgs);
}

enum States
{
   LAPTOP,
   TENT,
   TABLET_NORMAL,
   TABLET_OTHER
};

enum Events
{
   ORIENTATION,
   TOUCHPADKEY,
   KEYBOARD,
};


static void
stateMachine (enum Events event,
              char *data)
{
  switch (state) {
  case LAPTOP :
    if (event == TOUCHPADKEY)
    {
      toggleTouchpad();
    } else if (event == ORIENTATION && strcmp (data,"bottom-up") == 0)
    {
      disableTouchpad ();
      xrandr (data);
      enableKeyboard ();
      state = TENT;
      g_message ("state change: LAPTOP -> TENT");
    } else if (event == KEYBOARD) 
    {
      disableTouchpad ();
      enableKeyboard ();
      state = TABLET_NORMAL;
      g_message ("state change: LAPTOP -> TABLET_NORMAL");
    }
    break;
  case TENT :
    if (event == ORIENTATION && strcmp (data,"normal") == 0)
    {
      restoreTouchpad ();
      xrandr (data);
      disableKeyboard ();
      state = LAPTOP;
      g_message ("state change: TENT -> LAPTOP");
    } else if (event == KEYBOARD) 
    {
      state = TABLET_OTHER;
      g_message ("state change: TENT -> TABLET_OTHER");
    }
    break;
  case TABLET_NORMAL :
    if (event == ORIENTATION && strcmp (data,"normal") != 0)
    {
      xrandr (data);
      state = TABLET_OTHER;
      g_message ("state change: TABLET_NORMAL -> TABLET_OTHER");
    } else if (event == KEYBOARD) 
    {
      restoreTouchpad ();
      disableKeyboard ();
      state = LAPTOP;
      g_message ("state change: TABLET_NORMAL -> LAPTOP");
    }
    break;
  case TABLET_OTHER :
    if (event == ORIENTATION && strcmp (data,"normal") == 0)
    {
      xrandr (data);
      state = TABLET_NORMAL;
      g_message ("state change: TABLET_OTHER -> TABLET_NORMAL");
    } else if (event == ORIENTATION && strcmp (data,"bottom-up") != 0)
    {
      xrandr (data);
    } else if (event == KEYBOARD) 
    {
      state = TENT;
      g_message ("state change: TABLET_OTHER -> TENT");
    }
    break;
  }
}

static void
properties_changed (GDBusProxy *proxy,
		    GVariant   *changed_properties,
		    GStrv       invalidated_properties,
		    gpointer    user_data)
{
  GVariant *v;
  GVariantDict dict;

  g_variant_dict_init (&dict, changed_properties);

  if (g_variant_dict_contains (&dict, "HasAccelerometer")) {
    v = g_dbus_proxy_get_cached_property (iioSensorProxy, "HasAccelerometer");
    g_message ("Caught Accelerometer %s", g_variant_get_boolean (v) ? 
               "appeared" : "disappeared");
    g_variant_unref (v);
  }
  if (g_variant_dict_contains (&dict, "AccelerometerOrientation")) {
    v = g_dbus_proxy_get_cached_property (iioSensorProxy, 
                                          "AccelerometerOrientation");
    g_message ("Caught Accelerometer orientation change: %s", 
		g_variant_get_string (v, NULL));
    stateMachine (ORIENTATION, (char *)g_variant_get_string (v, NULL));
    g_variant_unref (v);
  }
}

static void
appear_handler (GDBusConnection *connection,
	        const gchar     *name,
	        const gchar     *name_owner,
	        gpointer         user_data)
{
  GError *error = NULL;

  iioSensorProxy = g_dbus_proxy_new_for_bus_sync (G_BUS_TYPE_SYSTEM,
                                                  G_DBUS_PROXY_FLAGS_NONE,
                                                  NULL,
                                                  IIOSENSORPROXYBUS,
                                                  IIOSENSORPROXYPATH,
                                                  IIOSENSORPROXYBUS,
                                                  NULL, NULL);

  g_signal_connect (G_OBJECT (iioSensorProxy), "g-properties-changed",
                    G_CALLBACK (properties_changed), NULL);

  g_dbus_proxy_call_sync (iioSensorProxy, "ClaimAccelerometer",
                          NULL, G_DBUS_CALL_FLAGS_NONE, -1,
                          NULL, &error);
  g_assert_no_error (error);
}

static void
vanish_handler (GDBusConnection *connection,
	        const gchar *name,
	        gpointer user_data)
{
  g_clear_object (&iioSensorProxy);
}

static void
key_handler (int signo)
{
  switch (signo) {
  case KEYTOGGLE :
    g_message ("Caught KEYTOGGLE");
    break;
  case KEYLOCK :
    g_message ("Caught KEYLOCK");
    break;
  default :
    break;
  }
}

static bool
read_keyboard_status (bool *status)
{
  uint8_t tmp1;
  if (!read_ec (R_EC_KEYBOARD, &tmp1)) return 0;
  
  *status = ((tmp1 & TABLET_MODE) == 0);
  return 1;
}

static void
timer_handler (int sig,
               siginfo_t *si,
               void *uc)
{
  if (sig == TIMERPOLL && si->si_value.sival_ptr == &timerid) {
    bool status;
    if (read_keyboard_status (&status))
    {
      if (keyboardEnabled != status)
      {
        g_message ("Caught keyboard state change");
        stateMachine (KEYBOARD, NULL);
        keyboardEnabled = status;
      }
    }
  }
}

// Write our PID value to the lock file
void
createPIDFile (void)
{
  pid_t pid = getpid ();
  FILE *f = fopen (PIDFILE, "w");
  fprintf (f, "%d\n", getpid ());
  fclose (f);
}

static void
getProcessInfo (pid_t pid,
                char *cwd,
                char *exe,
                size_t size)
{
  // temporary buffer for file path names
  char buffer[256];
  ssize_t result;

  // clear buffers in case strings are longer than 255 characters
  bzero (cwd, size);
  bzero (exe, size);

  // get the process' current working directory
  sprintf (buffer, "/proc/%d/cwd", pid);
  result = readlink (buffer, cwd, size);

  // get the process' executable name
  sprintf (buffer, "/proc/%d/exe", pid);
  result = readlink (buffer, exe, size);
}

// Check whether there is another copy of the process running.  This
// compares the process' executable name and current working directory to
// one another.  Returns 1 if there is another process runnning.

unsigned char
checkPID (void)
{
  char cwd1[256];
  char cwd2[256];
  char exe1[256];
  char exe2[256];
  int len;
  pid_t pid;

  // Attempt to read PID for a running process.  If the open fails, then
  // assume the process is not running and return 0.
  FILE *f = fopen (PIDFILE, "r");
  if (f == NULL) return 0;

  // If we can't read a valid number from PID file, fail.
  len = fscanf (f, "%d", &pid);
  fclose (f);
  if (len == 0) _exit (-1);

  // If everything is OK, get the info on the running process.
  getProcessInfo (pid, cwd1, exe1, sizeof(cwd1));

  // Repeat for this process.
  pid = getpid ();
  getProcessInfo (pid, cwd2, exe2, sizeof(cwd2));

  // If all strings are less than 255 characters, and the executable
  // and working directories match, return 1.
  return (exe1[255] == 0 && exe2[255] == 0 && 
          cwd1[255] == 0 && cwd2[255] == 0 &&
          strncmp (exe1, exe2, 256) == 0 &&
          strncmp (cwd2, cwd2, 256) == 0);
}


/*
 */
int 
main (int argc,
      char **argv)
{
  sigset_t mask;
  struct sigaction sa;
  struct sigevent sev;
  struct itimerspec its;
  long long freq_nanosecs;
  GMainLoop *loop;

  touchpadEnabled = true;
  state = LAPTOP;

  // exit if another process is already running
  if (checkPID () == 1) return 1;

  // write our PID file into the /var/run directory
  createPIDFile ();

  keyboardEnabled = true;

  // get permissions to read EC memory
  ec_init();

  // handle iio-sensor-proxy PropertyChange events on the DBus
  g_bus_watch_name (G_BUS_TYPE_SYSTEM, IIOSENSORPROXYBUS,
                    G_BUS_NAME_WATCHER_FLAGS_NONE,
                    appear_handler, vanish_handler, NULL, NULL);

  // handle key press events using signals
  signal(KEYTOGGLE, key_handler);
  signal(KEYLOCK, key_handler);

  // handle checking the EC memory using a timer
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = timer_handler;
  sigemptyset(&sa.sa_mask);
  sigaction(TIMERPOLL, &sa, NULL);
  sigaction(SIGKILL, &sa, NULL);

  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = TIMERPOLL;
  sev.sigev_value.sival_ptr = &timerid;
  timer_create (CLOCK_REALTIME, &sev, &timerid);

  its.it_value.tv_sec = 1;
  its.it_value.tv_nsec = 0;
  its.it_interval.tv_sec = its.it_value.tv_sec;
  its.it_interval.tv_nsec = its.it_value.tv_nsec;

  timer_settime (timerid, 0, &its, NULL);

  // wait in the main loop for events to happen
  g_main_loop_run ( g_main_loop_new (NULL, TRUE) );

  return 0;
}
