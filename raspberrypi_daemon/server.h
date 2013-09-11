#ifndef SERVER_H_
# define SERVER_H_

#define WS_SERVER_PORT 7681

#include <syslog.h>
#include <signal.h>
#include "libwebsockets/lib/libwebsockets.h"
#include "serial.h"

/*
 * Some type definitions
 */
typedef struct libwebsocket_context s_libws_ctx;
typedef struct libwebsocket s_libws;
typedef enum libwebsocket_callback_reasons e_libws_cb_r;

/*
 * The structure associated to the "http-only" protocol
 */
struct per_session_data__http {
    int                                 fd;
};

/*
 * The function called when signal terminate is catched
 */
void                                    sighandler(int                  sig);

/*
 * Initialize the socket
 */
s_libws_ctx*                            init_websocket();

/*
 * The main infinite loop
 */
int                                     run_server();

#endif /* !SERVER_H_ */
