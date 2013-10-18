/*
 * Copyright (c) 2013 All rights reserved.
 *
 * kevinhwm@gmail.com
 */


#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/socket.h>

#include "master.h"

void *  thr_reg(void *arg);
void    reg_listen(int sockfd);


int main()
{
    int err;
    pthread_t ntid;

    err = pthread_create(&ntid, NULL, thr_reg, NULL);
    if (err != 0)
        printf("create thread error\n");
    printf("thread id: %d\n", ntid);

    pthread_join(ntid, 0);

    return 0;
}


void * 
thr_reg(void *arg)
{
    int ret;
    int sockfd;
    struct sockaddr_in addr;
    socklen_t alen;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        printf("create socket error\n");
        return 0;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(30033);
    addr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (ret < 0)
    {
        printf("bind socket error.\nclose socket: %d\n", close(sockfd));
        return 0;
    }

    reg_listen(sockfd);

    close(sockfd);
}


void 
reg_listen(int sockfd)
{
    int num;
    char buf[128];
    char abuf[256];
    socklen_t alen = sizeof(abuf);
    struct sockaddr_in *des;
    char des_ip[32] = {0};
    char des_data[16] = {0};
    int count = 0;
    int ret = 0;

    while(1)
    {
        num = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)abuf, &alen);
        if (num == 0) {
            sleep(3);
            continue;
        }
        else if (num < 0) {
            // error
            printf("error: recvfrom -1\n");
            continue;
        }

        // convert net-order number to ip-address string.
        des = (struct sockaddr_in *)abuf;
        memset(des_data, 0, sizeof(des_data));
        memcpy(des_data, &(des->sin_addr.s_addr), sizeof(des->sin_addr.s_addr));
        inet_ntop(AF_INET, des_data, des_ip, sizeof(des_ip));

        ret = list_add(des_ip, strlen(des_ip));
        if (ret == 1)
            printf("\n%s already have\n", des_ip);
        list_showall();

        strncpy(buf, "this is 10.0.215.215", sizeof(buf));
        for (count = 3; count > 0; --count)
        {
            num = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)abuf, alen);
            if (num >= 0)
                break;
            else
                printf("error: sendto -1\n");
        }
    }

    return ;
}


