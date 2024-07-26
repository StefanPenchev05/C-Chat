#include "server.h"
#include "color_log.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void server_socketInit(Server *server, int port)
{
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1)
    {
        LOG_ERROR("Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    server->address = address;

    if (bind(server->socket, (struct sockaddr *)&server->address, sizeof address) == -1)
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

    pthread_mutex_lock(&server_ready_mutex);
    server_ready = 1;
    pthread_cond_signal(&server_ready_con);
    pthread_mutex_unlock(&server_ready_mutex);
}

void acceptClients(Server *server)
{
    socklen_t addr_len = sizeof(server->address);
    int client_socket;
    int i = 0;

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
            client_socket = accept(server->socket, (struct sockaddr *)&server->address, &addr_len);
            if (client_socket == -1)
            {
                if (stop_flag)
                    break;
                fprintf(stderr, "Failed to accept connection\n");
                continue;
            }

            if (i < MAX_CLIENTS)
            {
                server->clients[i].socket = client_socket;
                server->client_count++;
                printf("Accepted new client connection\n");
                i++;
            }
            else
            {
                fprintf(stderr, "Max clients reached, rejecting new connection\n");
                close(client_socket);
            }
        }
    }

    printf("Server is stopping ...\n");
    for (int j = 0; j < i; j++)
        close(server->clients[j].socket);

    close(server->socket);
}