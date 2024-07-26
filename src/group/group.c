#include "../../include/group.h"
#include <stdlib.h>
#include <string.h>

Group createGroup(int groupId, const char *groupName)
{
    Group *newGroup = (Group *)malloc(sizeof(Group));
    newGroup->groupId = groupId;
    strncpy(newGroup->groupName, groupName, sizeof(newGroup->groupName) - 1);
    newGroup->groupName[sizeof(newGroup->groupName) - 1] = '\0';
    newGroup->created_at = time(NULL);

    for (size_t i = 0; i < MAX_USERS; i++)
    {
        newGroup->users[i] = (User){0};
    }
    return *newGroup;
}