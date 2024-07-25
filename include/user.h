#ifndef USER_H
#define USER_H

#include <time.h>

typedef struct 
{
    int userId;
    char username[50];
    char passwordHashed[256];
    char email[100];
    time_t created_at;
} User;
 

#endif