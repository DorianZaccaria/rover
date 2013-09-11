#include "logger.h"

void                                    log_error(int                   err)
{
  switch (err) {
    case SERIAL_ERROR:
      write(STDERR_FILENO, "Serial connection failed\n", 25);
      break;
    case WEBSOCKET_ERROR:
      write(STDERR_FILENO, "Socket connection failed\n", 25);
      break;
    default:
      write(STDERR_FILENO, "Unknown error\n", 14);
      break;
  }
}

void                                    log_notice(int                  log)
{
  switch (log) {
    case WEBSOCKET_OPEN:
      write(STDOUT_FILENO, "Rover server - Dorian Zaccaria\n", 31);
      break;
    case WEBSOCKET_CLOSE:
      write(STDOUT_FILENO, "Server exited cleanly\n", 22);
      break;
    case WEBSOCKET_CON:
      write(STDOUT_FILENO, "Connection established\n", 24);
      break;
    case SERIAL_OPEN:
      write(STDOUT_FILENO, "Serial tty opened\n", 18);
      break;
    case INIT:
      write(STDOUT_FILENO, "Rover server - Dorian Zaccaria\n", 31);
      break;
    default:
      write(STDOUT_FILENO, "DEBUG\n", 6);
      break;
  }
}
