#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h>

#define PORT 8080


int main() {
    // Server Address
    struct sockaddr_in address;

    // Server-socket creation
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0) {
        printf("socket() errno is %d\n", errno);
        return errno;
    }

    printf("serverfd: %d\n", serverfd);

    // Defining server address
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;
    unsigned int serverAddrLen = sizeof(address);


    // Bind socket-fd to socket-address
    if (bind(serverfd, (const struct sockaddr *) &address, sizeof(address)) != 0) {
        printf("bind() failed iwth errno %d\n", errno);
        perror("bind() Error");
        return -1;
    }


    // Put server in listen/passive mode
    if (listen(serverfd, 0) != 0) {
        printf("listen() errno is %d\n", errno);
        return errno;
    }


    // Gets connection-fd after accepting connection
    int connfd = 0;

    while (1) {
        connfd = accept(serverfd, (struct sockaddr *) &address, (socklen_t *) &serverAddrLen);
        printf("connfd: %d\n", connfd);
    }



    return 0;
}