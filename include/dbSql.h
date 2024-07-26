#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>

void init_db();
MYSQL* connect_db();
void list_databases(MYSQL *conn);
void close_db(MYSQL *conn);

#endif