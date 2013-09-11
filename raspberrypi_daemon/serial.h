#ifndef SERIAL_H_
# define SERIAL_H_

#include <string.h>
#include <errno.h>
#include <termios.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "logger.h"

#define PORTNAME        "/dev/ttyUSB1"

int                                     fd;

/*
 * set speed to 115,200 bps, 8n1 (no parity)
 *
 * tty.c_cflag: 8-bits chars disable IGNBRK for mismatched speed tests;
 *              otherwise receive break as \000 chars
 * tty.c_iflag: ignore break signal
 * tty.c_lflag: no signaling chars, no echo, no canonical processing
 * tty.c_oflag: no remapping, no delays
 * tty.c_cc[VMIN]: read doesn't block
 * tty.c_cc[VTIME]: 0.5 seconds read timeout
 * tty.c_iflag &= ~(IXON | IXOFF | IXANY): shut off xon/xoff ctrl
 * tty.c_cflag |= (CLOCAL | CREAD): ignore modem controls, enable reading
 * tty.c_cflag &= ~(PARENB | PARODD): shut off parity
 */
int                                     set_interface_attribs(int       fd,
                                                              int       speed,
                                                              int       parity);

/*
 * set no blocking: means should_block = 0. And the tty.c_cc[VTIME] = 5 is
 * for the 0.5 seconds read timeout
 */
int                                     set_blocking(int                fd,
                                                     int                should_block);

/*
 * Initialize the file descriptor in order to write into it
 */
int                                     init_serial();

#endif /* !SERIAL_H_ */
