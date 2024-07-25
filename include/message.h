#ifndef MESSAGE_H
#define MESSAGE_H

#include <time.h>

typedef struct
{
    int massageId;
    int senderId;
    int receiverId;
    char content[256];
    time_t timestamp;
    bool isEncrypted;
} Message;

#endif