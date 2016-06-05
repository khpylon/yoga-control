/* Copyright (c) 2016 Ken Hughes <ken.l.hughes@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 */

#include <sys/types.h>
#include <sys/io.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

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

// define prototype for kernel module EC read procedure
static uint8_t read_ec_sys (uint8_t *value);

// default method is kernel module EC read
static uint8_t (*get_ec) (uint8_t *value) = read_ec_sys;

// file descriptor for kernel module EC read
static int fd = -1;

/* -------------------------------------------------- */
/* Direct port I/O procedures                         */
/* -------------------------------------------------- */

// set I/O port permissions
static int 
ec_io_init (void)
{
  if (ioperm (EC_DATA, 1, 1) != 0 || ioperm (EC_SC, 1, 1) != 0) return -1;
  return 0;
}

// wait while I/O port is busy
static uint8_t
wait_ec_io (const uint32_t flag, const char value)
{
  uint8_t data;
  int i;

  i = 0;
  data = inb(EC_SC);

  while ( (((data >> flag) & 0x1) != value) && (i++ < 100) )
  {
    usleep(1000);
    data = inb(EC_SC);
  }

  return (i < 100);
}

// read keyboard status using direct I/O
static uint8_t 
read_ec_io (uint8_t *value)
{
    if (!wait_ec_io (IBF, 0)) return 0;
    outb (EC_SC_READ_CMD, EC_SC);
    if (!wait_ec_io (IBF, 0)) return 0;
    outb (R_EC_KEYBOARD, EC_DATA);
    if (!wait_ec_io (OBF, 1)) return 0;
    *value = inb (EC_DATA);
    return 1;
}

/* -------------------------------------------------- */
/* Kernel module EC procedures                        */
/* -------------------------------------------------- */

static
uint8_t read_ec_sys (uint8_t *value)
{
  unsigned char status;
  off_t result;

  // if the kernel module hasn't be initialized, try it
  if (fd == -1) {
    fd = open ("/sys/kernel/debug/ec/ec0/io", O_RDONLY);

    // if open fails, then fall back to direct I/O methods
    if (fd == -1) {
      get_ec = read_ec_io;
      ec_io_init ();
      return 0;
    }
  }

  // if this is a real request....
  if (value != NULL) {
    // seek to offset for keyboard status, then read
    lseek (fd, R_EC_KEYBOARD, SEEK_SET );
    int x = read (fd, value, 1);
  }
  return 1;
}

/* -------------------------------------------------- */
/* Public procedure                                   */
/* -------------------------------------------------- */

uint8_t 
read_ec (uint8_t *value)
{
  return (*get_ec) (value);
}
