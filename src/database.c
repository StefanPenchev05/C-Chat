#include "databaseMySQL.h"
#include "color_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadEnvironmentVariables(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        LOG_ERROR("Failed to open .env file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");
        if (key && value) {
            setenv(key, value, 1);
        }
    }

    fclose(file);
}


void initializeEnvironment(const char *filename) {
    loadEnvironmentVariables(filename);
}


MYSQL* connectToDatabase() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        LOG_ERROR("mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *pass = getenv("DB_PASS");
    const char *dbname = getenv("DB_NAME");

    if (!mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)) {
        LOG_ERROR("mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    return conn;
}

void closeDatabaseConnection(MYSQL *conn) {
    mysql_close(conn);
}