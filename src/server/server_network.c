#include "databaseMySQL.h"
#include "server.h"
#include "color_log.h"
#include "server_utils.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void server_socketInit(Server *server, int port)
{
    init_env();
    MYSQL *dbConnection = connectToDatabase();

    if (dbConnection == NULL)
    {
        LOG_ERROR("Failed to connect to database\n");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Connected to the Database\n");

    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1)
    {
        LOG_ERROR("Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    server->address = serverAddress;

    if (bind(server->socket, (struct sockaddr *)&server->address, sizeof(serverAddress)) == -1)
    {
        LOG_ERROR("Failed to bind socket\n");
        close(server->socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server->socket, 20) == -1)
    {
        LOG_ERROR("Failed to listen on socket\n");
        close(server->socket);
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Server is listening on port %d\n", port);

    pthread_mutex_lock(&g_Server_ready_mutex);
    g_Server_ready = 1;
    pthread_cond_signal(&g_Server_ready_con);
    pthread_mutex_unlock(&g_Server_ready_mutex);
}

void acceptClients(Server *server)
{
    socklen_t addressLength = sizeof(server->address);
    int clientSocket;
    int clientIndex = 0;

    fcntl(server->socket, F_SETFL, O_NONBLOCK);

    while (!stop_flag)
    {
        fd_set read_fds;
        struct timeval timeout;

        FD_ZERO(&read_fds);
        FD_SET(server->socket, &read_fds);

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(server->socket + 1, &read_fds, NULL, NULL, &timeout);

        if (activity < 0 && !stop_flag)
        {
            fprintf(stderr, "Select error\n");
            continue;
        }

        if (activity > 0 && FD_ISSET(server->socket, &read_fds))
        {
            clientSocket = accept(server->socket, (struct sockaddr *)&server->address, &addressLength);
            if (clientSocket == -1)
            {
                if (stop_flag)
                    break;
                fprintf(stderr, "Failed to accept connection\n");
                continue;
            }

            if (clientIndex < MAX_CLIENTS)
            {
                server->clients[clientIndex].socket = clientSocket;
                server->client_count++;
                printf("Accepted new client connection\n");
                clientIndex++;
            }
            else
            {
                fprintf(stderr, "Max clients reached, rejecting new connection\n");
                close(clientSocket);
            }
        }
    }

    shutdown_server(server);
}