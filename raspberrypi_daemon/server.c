#include "server.h"

int                                     force_exit = 0;

/*
 * The function called when a connection "http-only" is established
 */
static int                              callback_http(s_libws_ctx*      this,
                                                      s_libws*          wsi,
                                                      e_libws_cb_r      reason,
                                                      void*             user,
                                                      void*             in,
                                                      size_t            len)
{
  char*                                 buf = (char*) in;

  switch (reason) {
    case LWS_CALLBACK_ESTABLISHED:
      log_notice(WEBSOCKET_CON);
      break;
    case LWS_CALLBACK_RECEIVE:
      printf("received data: %s\n", buf);
      write(fd, buf, strlen(buf));
      break;
    default:
      break;
  }
  return 0;
}

/*
 * The structure which list all protocols apt to be called
 */
static struct libwebsocket_protocols    protocols[] = {
  {
    "http-only",
    callback_http,
    sizeof(struct per_session_data__http),
    0,
  },
  { NULL, NULL, 0, 0 }
};

void                                    sighandler(int                  sig)
{
  force_exit = 1;
}

s_libws_ctx*                            init_websocket()
{
  struct lws_context_creation_info      info;
  s_libws_ctx*                          context;
  const char*                           iface = NULL;
  unsigned int                          oldus = 0;
  int                                   debug_level = 7;
  int                                   opts = 0;

  memset(&info, 0, sizeof info);
  info.port = WS_SERVER_PORT;

  signal(SIGINT, sighandler);

  lws_set_log_level(debug_level, lwsl_emit_syslog);

  info.iface = iface;
  info.protocols = protocols;
  info.ssl_cert_filepath = NULL;
  info.ssl_private_key_filepath = NULL;
  info.gid = -1;
  info.uid = -1;
  info.options = opts;

  context = libwebsocket_create_context(&info);

  return context;
}

int                                     run_server()
{
  s_libws_ctx*                          context;
  int                                   i = 0;

  context = init_websocket();
  if (context == NULL)
    return WEBSOCKET_ERROR;

  log_notice(WEBSOCKET_OPEN);
  while (i >= 0 && !force_exit)
    i = libwebsocket_service(context, 50);

  libwebsocket_context_destroy(context);
  log_notice(WEBSOCKET_CLOSE);

  return SUCCESS;
}
