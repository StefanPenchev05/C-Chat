#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"
#include "server_utils.h"
#include "client.h"
#include "color_log.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        LOG_ERROR("Usage: %s <server|client> <port>", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[2]);

    if (strcmp(argv[1], "server") == 0)
    {
        serverInit(port);
    }
    else if (strcmp(argv[1], "client") == 0)
    {
        // clientInit(port);
    }
    else
    {
        LOG_ERROR("Invalid arguments: %s. Expected 'server' or 'client'", argv[1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}