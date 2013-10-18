/*
 * Copyright (c) 2013 All rights reserved.
 *
 * kevinhwm@gmail.com
 */

#ifndef INK_PROTOCOL_H
#define INK_PROTOCOL_H


#define INK_ID_LENGTH 256

#define ID_MASTER       0x00
#define ID_SLAVE        0x80

#define TYPE_SEARCH     0x00
#define TYPE_REPLY      0x01


struct list_slave
{
    struct list_slave *previous;
    char name[INK_ID_LENGTH];
    struct list_slave *next;
};

extern struct list_slave * position_current;

struct ProtocolReg
{
    int type;
    int id;
    int seq_id;
};


#endif // INK_PROTOCOL_H

