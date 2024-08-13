#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    // Server Address
    struct sockaddr_in address;

    // Server-socket creation (listening socket)
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

        connfd = accept(serverfd, (struct sockaddr *) &address, (socklen_t *) &serverAddrLen);
        printf("connfd: %d\n", connfd);
    while (1) {
        char dummy_buf[1] = {0};
        char buffer[BUFFER_SIZE] = {0};
        // int recv_data = recv(connfd, buffer, BUFFER_SIZE, MSG_PEEK);
        if (recv(connfd, buffer, BUFFER_SIZE, 0) == -1) {
            perror("recv() Error");
        }

        if (send(connfd, dummy_buf, 1, 0) == -1) {
            fwrite("Connfd closed\n", sizeof(char), strlen("Connfd closed\n"), stdout);
            break;
        }


        fwrite(buffer, sizeof(char), strlen(buffer), stdout);
    }



    return 0;
}