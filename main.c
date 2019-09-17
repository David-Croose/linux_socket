#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server;
    int res;
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket create failed!\n");
        exit(-1);
    }

    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(6677);
    server.sin_addr.s_addr = inet_addr("116.24.65.230");    // server.sin_addr.s_addr = htonl(INADDR_ANY)

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("socket connect failed!\n");
        exit(-1);
    }

    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        write(sockfd, sendbuf, sizeof(sendbuf));
        read(sockfd, recvbuf, sizeof(recvbuf));
        fputs(recvbuf, stdout);
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sockfd);
    return 0;
}

