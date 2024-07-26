#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include "server.h"
#include <pthread.h>
#include <signal.h>

extern pthread_mutex_t server_ready_mutex;
extern pthread_cond_t server_ready_con;
extern int server_ready;
extern volatile sig_atomic_t stop_flag;

void serverInit(int port);
void shutdown_server(Server *server);
void restart_server(Server *server);
void kickClient(Server *server, const char *username);

#endif