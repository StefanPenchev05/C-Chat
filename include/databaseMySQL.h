#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>

void initializeEnvironment(const char *filename);
MYSQL* connectToDatabase();
void closeDatabaseConnection(MYSQL *conn);

#endif