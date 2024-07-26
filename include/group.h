#ifndef GROUP_H
#define GROUP_H

#include <time.h>
#include "user.h"
#include "message.h"

#define MAX_USERS 100

typedef struct 
{
    int groupId;
    char groupName[100];
    time_t created_at;
    User users[MAX_USERS];
} Group;

void addMemder(User user);
void removeMember(User user);
void sentMessage(Message message);

Group createGroup(int groupId, const char *groupName);

#endif // GROUP_H