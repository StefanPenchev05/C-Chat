#ifndef FILE_H
#define FILE_H

#include <time.h>

typedef struct {
    int fileId;
    int senderId;
    int receiverId;
    char fileName[100];
    char filePath[256];
    time_t timestamp;
} File;

#endif