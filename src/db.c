#include "dbSql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_env(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open .env file");
        exit(1);
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


void init_db() {
	load_env(".env");
}

MYSQL* connect_db() {
	MYSQL *conn = mysql_init(NULL);

	const char *host = getenv("DB_HOST");
	const char *user = getenv("DB_USER");
	const char *pass = getenv("DB_PASS");
	const char *dbname = getenv("DB_NAME");

	if (!mysql_real_connect(conn, host, user,pass, dbname, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	return conn;
}


void list_databases(MYSQL *conn)
{
    if (mysql_query(conn, "SHOW DATABASES"))
    {
        fprintf(stderr, "SHOW DATABASES failed. Error: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL)
    {
        fprintf(stderr, "mysql_store_result() failed. Error: %s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row;
    printf("Databases:\n");
    while ((row = mysql_fetch_row(result)))
    {
        printf("%s\n", row[0]);
    }

    mysql_free_result(result);
}


void close_db(MYSQL *conn) {
	mysql_close(conn);
}