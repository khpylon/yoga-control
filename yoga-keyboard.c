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

#include "net_khpylon_yoga900.h"

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

static GDBusObjectManagerServer *manager = NULL;
GDBusConnection *connect;
static keyboard *exported_key_object = NULL;
static timer_t timerid;
static bool keyboardEnabled;

GDBusInterfaceVTable *
keyboard__skeleton_dbus_interface_get_vtable ( );

int ec_init()
{
    if (ioperm(EC_DATA, 1, 1) != 0 || ioperm(EC_SC, 1, 1) != 0) return -1;
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

    if (i >= 100) return 0;
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
read_keyboard_status (bool *status)
{
  uint8_t tmp;
  if (!read_ec (R_EC_KEYBOARD, &tmp)) return 0;

  *status = ((tmp & TABLET_MODE) == 0);
  return 1;
}

static void
on_bus_acquired (GDBusConnection *connection,
                 const gchar     *name,
                 gpointer         user_data)
{
  GError *error = NULL;
  connect = connection;

  exported_key_object = keyboard__skeleton_new ();
  keyboard__set_laptop_mode (exported_key_object, TRUE );

  g_dbus_connection_register_object (connection,
                                     "/net/khpylon/yoga900keyboard",
                                     keyboard__interface_info(),
                                     keyboard__skeleton_dbus_interface_get_vtable ( ),
                                     exported_key_object,
                                     NULL,
                                     NULL);

}

static void
on_name_acquired (GDBusConnection *connection,
                  const gchar     *name,
                  gpointer         user_data)
{
  g_debug ("Acquired the name %s\n", name);
}


static void
on_name_lost (GDBusConnection *connection,
              const gchar     *name,
              gpointer         user_data)
{
  g_debug ("Lost the name %s\n", name);
  connect = NULL;
}

static void
timer_handler (int sig,
               siginfo_t *si,
               void *uc)
{
  if (connect != NULL && si->si_value.sival_ptr == &timerid)
  {
    bool status;
    if (read_keyboard_status (&status))
    {
      if (keyboardEnabled != status)
      {
        keyboardEnabled = status;

        GVariantBuilder props_builder;
        GVariant *props_changed = NULL;
        g_variant_builder_init (&props_builder, G_VARIANT_TYPE ("a{sv}"));
        g_variant_builder_add (&props_builder, "{sv}", "LaptopMode",
                              g_variant_new_boolean (keyboardEnabled));

        props_changed= g_variant_new ("(s@a{sv}@as)", 
                                     "net.khpylon.yoga900keyboard" ,
                                     g_variant_builder_end(&props_builder),
                                     g_variant_new_strv (NULL, 0));


        g_dbus_connection_emit_signal (connect,
                                      NULL,
                                      "/net/khpylon/yoga900keyboard",
                                      "org.freedesktop.DBus.Properties",
                                      "PropertiesChanged",
                                      props_changed, NULL);

        g_message ("LaptopMode set to %s.", status ? "true" : "false");
      }
    }
  }
}


void setup_timer()
{
  struct sigaction sa;
  struct sigevent sev;
  struct itimerspec its;

  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = timer_handler;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGUSR1, &sa, NULL);

  sev.sigev_notify = SIGEV_SIGNAL;
  sev.sigev_signo = SIGUSR1;
  sev.sigev_value.sival_ptr = &timerid;
  timer_create (CLOCK_REALTIME, &sev, &timerid);

  // check the EC status every 1/4 second
  its.it_value.tv_sec = 0;
  its.it_value.tv_nsec = 1000000000/4;
  its.it_interval.tv_sec = its.it_value.tv_sec;
  its.it_interval.tv_nsec = its.it_value.tv_nsec;

  timer_settime (timerid, 0, &its, NULL);
}

gint
main (gint argc, gchar *argv[])
{
  GMainLoop *loop;
  guint id;
  connect = NULL;

  loop = g_main_loop_new (NULL, FALSE);

  id = g_bus_own_name (G_BUS_TYPE_SYSTEM,
                       "net.khpylon.yoga900keyboard",
                       G_BUS_NAME_OWNER_FLAGS_ALLOW_REPLACEMENT |
                       G_BUS_NAME_OWNER_FLAGS_REPLACE,
                       on_bus_acquired,
                       on_name_acquired,
                       on_name_lost,
                       loop,
                       NULL);


  keyboardEnabled = true;
  setup_timer();
  ec_init();

  g_main_loop_run (loop);

  g_bus_unown_name (id);
  g_main_loop_unref (loop);

  return 0;
}
