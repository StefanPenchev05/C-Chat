#include "server.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "color_log.h"

void handle_stop_signal()
{
    stop_flag = 1;
}

void *read_input(void *arg)
{

    pthread_mutex_lock(&server_ready_mutex);
    while (!server_ready)
    {
        pthread_cond_wait(&server_ready_con, &server_ready_mutex);
    }
    pthread_mutex_unlock(&server_ready_mutex);

    Server *server = (Server *)arg;
    char *command = NULL;
    size_t len = 0;

    while (1)
    {
        printf("Command > ");
        if (getline(&command, &len, stdin) == -1)
        {
            continue;
        }

        command[strcspn(command, "\n")] = 0;

        char *token = strtok(command, " ");
        if (strcmp(token, "stop") == 0)
        {
            handle_stop_signal();
            break;
        }
        else if (strcmp(token, "status") == 0)
        {
            LOG_WARN("Server is running on port %d\n", ntohs(server->address.sin_port));
        }
        else if (strcmp(token, "ls") == 0)
        {
            token = strtok(NULL, " ");
            if (token != NULL && strcmp(token, "-clients") == 0)
            {
                size_t clientCount = server->client_count;

                if (clientCount == 0)
                {
                    LOG_WARN("No clients connected at this moment");
                }
                else
                {
                    for (size_t i = 0; i < clientCount; i++)
                    {
                        LOG_WARN("Client with username %s is connected\n", server->clients[i].username);
                    }
                }
            }
            else
            {
                LOG_ERROR("Unknown option for ls command. Available option: -clients");
            }
        }
        else
        {
            LOG_ERROR("Unknown command. Run command help to see the avaliable commands");
        }
    }

    free(command);
    return NULL;
}