#include "main.h"

int                                     main(void)
{
  log_notice(INIT);

  if (init_serial() == SERIAL_ERROR) {
    log_error(SERIAL_ERROR);
    return SERIAL_ERROR;
  }

  if (run_server() == WEBSOCKET_ERROR) {
    log_error(WEBSOCKET_ERROR);
    return WEBSOCKET_ERROR;
  }

  return SUCCESS;
}


