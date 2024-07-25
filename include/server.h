#ifndef SERVER_H
#define SERVER_H

#include "client.h"

#define MAX_CLIENTS 100


typedef struct 
{
    int socket;
    int port;
    Client clients[MAX_CLIENTS];
} Server;
 
void socketInit(Server *server, int port);
void acceptClients(Server *server);
void handleMessages(Server *server);

#endif