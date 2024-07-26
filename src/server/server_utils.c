#include "server.h"
#include "server_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "color_log.h"

pthread_mutex_t server_ready_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t server_ready_con = PTHREAD_COND_INITIALIZER;
int server_ready = 0;

volatile sig_atomic_t stop_flag = 0;

void serverInit(int port)
{
    Server *server = (Server *)malloc(sizeof(Client));
    if (server == NULL)
    {
        LOG_ERROR("Failed to allocate memory for server");
        exit(EXIT_FAILURE);
    }

    pthread_t input_thread;
    pthread_create(&input_thread, NULL, read_input, server);

    server_socketInit(server, port);
    acceptClients(server);

    pthread_join(input_thread, NULL);
}

void shutdown_server(Server *server)
{
    LOG_WARN("Shutting down server...");

    for (int i = 0; i < server->client_count; i++)
    {
        close(server->clients[i].socket);
    }

    close(server->socket);
}

void restart_server(Server *server)
{
    // Shut down server
    shutdown_server(server);

    system("clear");
    LOG_INFO("Server Restarting");

    // Reinitialize the server
    serverInit(ntohl(server->address.sin_port));
}

void kickClient(Server *server, const char *username)
{
    if(server->client_count == 0)
    {
        LOG_WARN("No clients connected at the moment");
        return;
    }

    for (int i = 0; i < server->client_count; i++)
    {
        if (strcmp(username, server->clients[i].username) == -1)
        {
            LOG_WARN("No clients with assosiated username - %s", username);
            continue;
        }

        LOG_WARN("Kicking client with username: %s", username);
        close(server->clients[i].socket);
        break;
    }
}