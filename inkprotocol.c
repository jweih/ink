/*
 * Copyright (c) 2013 HuangTao All rights reserved.
 *
 * kevinhwm@gmail.com
 */


#include "inkcommon.h"
#include "inkprotocol.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct list_slave * position_first = 0;
struct list_slave * position_last = 0;

/*
 * return value:
 * 0    :ok
 * 1    :dup
 */

int list_add(char * id, int id_len)
{
    struct list_slave * cur = position_first;
    for (; cur ; cur = cur->next)
        if (!strcmp(cur->name, id))
            return 1;

    if (id_len > INK_ID_LENGTH)
        return -1;

    struct list_slave * new_slave = (struct list_slave *)malloc(sizeof(struct list_slave));
    memset(new_slave, 0, sizeof(struct list_slave));
    strncpy(new_slave->name, id, id_len);

    // init. no slave
    if (position_last == NULL) {
        position_last = new_slave;
        position_first = new_slave;
    }
    // already have slave
    else {
        new_slave->previous = position_last;
        position_last->next = new_slave;
        position_last = new_slave;
    }

    return 0;
}

int list_del(char * id)
{
    int ret = -1;
    struct list_slave * cur = position_first;
    for (; cur->next; )
    {
        if (!strcmp(cur->name, id))
        {
            cur->previous->next = cur->next;
            cur->next->previous = cur->previous;
            free(cur);

            ret = 0;
            break;
        }
    }

    return ret;
}

int list_clean()
{
    struct list_slave * tmp;
    for (; position_first; )
    {
        tmp = position_first;
        position_first = position_first->next;
        free(tmp);
    }
    return 0;
}

void list_showall()
{
    struct list_slave * cur = position_first;
    int n = 1;

    printf("******* slave list *******\n");
    for ( ; cur; )
    {
        printf("%02d %s\n", n++, cur->name);
        cur = cur->next;
    }
    printf("**************************\n");

    return ;
}



