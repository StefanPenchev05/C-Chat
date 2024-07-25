#ifndef CLIENT_H
#define CLIENT_H

typedef struct 
{
    int socket;
    char username[50];
} Client;

void socketInit(Client *client, const char *server_ip, int port);
void connectToServer(Client *client);
void sendMessage(Client *client, const char *message);
void receiveMessage(Client *client);
void sendFile(Client *client, const char *filename);
void receiveFile(Client *client);

#endif