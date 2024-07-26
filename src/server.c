#include "server.h"
#include <stdio.h>
#include <stdlib.h>
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