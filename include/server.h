#ifndef SERVER_H
#define SERVER_H

#include "client.h"
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>

#define MAX_CLIENTS 100
extern volatile sig_atomic_t stop_flag;

typedef struct 
{
    int socket;
    struct sockaddr_in address;
    Client clients[MAX_CLIENTS];
    int client_count;
} Server;

extern pthread_mutex_t server_ready_mutex;
extern pthread_cond_t server_ready_con;
extern int server_ready;

void server_socketInit(Server *server, int port);
void acceptClients(Server *server);
void handleMessages(Server *server);
void handle_stop_signal();
void* read_input(void* arg);

#endif