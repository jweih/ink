/*
 * Copyright (c) 2013 HuangTao All rights reserved.
 *
 * huangtao@antiy.com
 */


#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>

#include "inkcommon.h"

#define BUFLEN 128

int main()
{
    int sockfd;
    int so_broadcast = 1;
    char buf[BUFLEN] = "blablabla";
    struct sockaddr_in addr;
    int bin_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        printf("create socket error\n");
        return -1;
    }

    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof(so_broadcast));

    memset(&addr, 0, sizeof(addr));
    inet_pton(AF_INET, "255.255.255.255", &bin_addr);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(30033);
    addr.sin_addr.s_addr = bin_addr;

    if ((n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&addr, sizeof(struct sockaddr))) < 0)
        printf("send error \n");
    else
        printf("send: [%04d]%s\n", strlen(buf), buf);

    if ((n = recvfrom(sockfd, buf, BUFLEN, 0, NULL, NULL)) < 0)
        ;
    else
        printf("recv: [%04d]%s\n", strlen(buf), buf);

    close(sockfd);

    return 0;
}


