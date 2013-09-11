#ifndef LOGGER_H_
# define LOGGER_H_

#include <unistd.h>

/*
 * Define log code
 */
#define SUCCESS         0
#define WEBSOCKET_ERROR 1
#define SERIAL_ERROR    2
#define WEBSOCKET_OPEN  3
#define WEBSOCKET_CLOSE 4
#define WEBSOCKET_CON   5
#define SERIAL_OPEN     6
#define INIT            7

/*
 * Display error messages
 */
void                                    log_error(int                   err);

/*
 * Display log messages
 */
void                                    log_notice(int                  log);

#endif /* !LOGGER_H_ */
