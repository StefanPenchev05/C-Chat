#include "server.h"
#include "server_utils.h"
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
    pthread_mutex_lock(&g_Server_ready_mutex);
    while (!g_Server_ready)
    {
        pthread_cond_wait(&g_Server_ready_con, &g_Server_ready_mutex);
    }
    pthread_mutex_unlock(&g_Server_ready_mutex);

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
        if (token == NULL)
        {
            LOG_ERROR("No command entered. Run command help to see the available commands");
            continue;
        }

        if (strcmp(token, "stop") == 0)
        {
            handle_stop_signal();
            break;
        }

        if (strcmp(token, "status") == 0)
        {
            LOG_WARN("Server is running on port %d\n", ntohs(server->address.sin_port));
            continue;
        }

        if (strcmp(token, "ls") == 0)
        {
            token = strtok(NULL, " ");
            if (token == NULL || strcmp(token, "-clients") != 0)
            {
                LOG_ERROR("Unknown option for ls command. Available option: -clients");
                continue;
            }
            
            size_t clientCount = server->client_count;
            
            if (clientCount == 0)
            {
                LOG_WARN("No clients connected at this moment");
                continue;
            }
            
            for (size_t i = 0; i < clientCount; i++)
            {
                LOG_WARN("Client with username %s is connected\n", server->clients[i].username);
            }
            continue;
        }

        if (strcmp(token, "help") == 0)
        {
            LOG_WARN("Available commands: \nstop, \nstatus, \nls \n\t-clients, \nhelp, \nrestart, \nshutdown, \nbroadcast <message>, \nkick <username>");
            continue;
        }

        if (strcmp(token, "restart") == 0)
        {
            LOG_WARN("Restarting server");
            restart_server(server);
            continue;
        }

        if (strcmp(token, "shutdown") == 0)
        {
            LOG_WARN("Shutting down server...");
            handle_stop_signal();
            break;
        }

        if (strcmp(token, "broadcast") == 0)
        {
            if (token == NULL)
            {
                LOG_ERROR("No message provided for broadcast command.");
                continue;
            }
            
            token = strtok(NULL, "");
            LOG_WARN("Broadcasting message: %s", token);
            // TODO: make message handling
            continue;
        }

        if (strcmp(token, "kick") == 0)
        {
            if (token == NULL)
            {
                LOG_ERROR("No username provided for kick command.");
                continue;
            }
            
            token = strtok(NULL, " ");
            kickClient(server, token);
            continue;
        }

        LOG_ERROR("Unknown command. Run command help to see the available commands");
    }

    free(command);
    return NULL;
}
