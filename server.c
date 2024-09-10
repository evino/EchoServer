#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "server.h"

#define PORT 8080
#define BUFFER_SIZE 1024


struct Listener_Socket {
    int fd;
};

// GLOBAL Server Address
struct sockaddr_in address;
unsigned int serverAddrLen = sizeof(address);

int listener_init(listener_socket_t *sock, unsigned int port) {

    printf("Before Socket made\n");
    // Server-socket creation (listening socket)
    sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket made\n");
    if (sock->fd < 0) {
        perror("socket() Error");
        return -1;
    }

    // Defining server address
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    // Bind socket-fd to socket-address
    if (bind(sock->fd, (const struct sockaddr *) &address, sizeof(address)) != 0) {
        perror("bind() Error");
        return -1;
    }

    // Put server in listen/passive mode
    if (listen(sock->fd, 0) != 0) {
        perror("listen() Error");
        return -1;
    }

    return 0;
}


int listener_accept(listener_socket_t *sock) {
    int connfd = accept(sock->fd, (struct sockaddr *) &address, (socklen_t *) &serverAddrLen);
    return connfd;
}



int main() {
    listener_socket_t *sock = malloc(sizeof(listener_socket_t));

    if (listener_init(sock, PORT) != 0) {
        return -1;
    }

    int connfd = listener_accept(sock);

    
    while (1) {
        printf("connfd: %d\n", connfd);
        char dummy_buf[1] = {0};
        char buffer[BUFFER_SIZE] = {0};
        if (recv(connfd, buffer, BUFFER_SIZE, 0) == -1) {
            connfd = listener_accept(sock);
            printf("buffer at this point contains: %s\n", buffer);
        }

        if (send(connfd, dummy_buf, 1, 0) == -1) {
            fwrite("Connfd closed\n", sizeof(char), strlen("Connfd closed\n"), stdout);
            break;
        }


        fwrite(buffer, sizeof(char), strlen(buffer), stdout);
    }

}
