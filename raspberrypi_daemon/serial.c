#include "serial.h"

int                                     set_interface_attribs(int       fd,
                                                              int       speed,
                                                              int       parity)
{
  struct termios                        tty;

  memset (&tty, 0, sizeof(tty));
  if (tcgetattr (fd, &tty) != 0) {
    printf("error %d from tcgetattr", errno);
    return SERIAL_ERROR;
  }

  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
  tty.c_iflag &= ~IGNBRK;
  tty.c_lflag = 0;

  tty.c_oflag = 0;
  tty.c_cc[VMIN]  = 0;
  tty.c_cc[VTIME] = 5;

  tty.c_iflag &= ~(IXON | IXOFF | IXANY);

  tty.c_cflag |= (CLOCAL | CREAD);

  tty.c_cflag &= ~(PARENB | PARODD);
  tty.c_cflag |= parity;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  if (tcsetattr (fd, TCSANOW, &tty) != 0) {
    printf("error %d from tcsetattr", errno);
    return SERIAL_ERROR;
  }

  return SUCCESS;
}

int                                     set_blocking(int                fd,
                                                     int                should_block)
{
  struct termios                        tty;

  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) {
    printf("error %d from tggetattr", errno);
    return SERIAL_ERROR;
  }

  tty.c_cc[VMIN]  = should_block ? 1 : 0;
  tty.c_cc[VTIME] = 5;

  if (tcsetattr (fd, TCSANOW, &tty) != 0) {
    printf("error %d setting term attributes", errno);
    return SERIAL_ERROR;
  }

  return SUCCESS;
}

int                                     init_serial()
{
  char*                                 portname = PORTNAME;
  int                                   ret;

  fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0) {
    printf("error %d opening %s: %s\n", errno, portname, strerror(errno));
    return SERIAL_ERROR;
  }

  ret = set_interface_attribs(fd, B115200, 0);
  if (ret == SERIAL_ERROR)
    return SERIAL_ERROR;

  ret = set_blocking(fd, 0);
  if (ret == SERIAL_ERROR)
    return SERIAL_ERROR;

  log_notice(SERIAL_OPEN);
  return SUCCESS;
}
