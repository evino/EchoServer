#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <errno.h>


#define PORT 8080


int main() {
    // Creating client socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Client socket is %d\n", sockfd);

    if (sockfd == -1) {
        printf("sockfd() error: %d\n", errno);
    }

    // Defining server address
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    unsigned int servAddrSize = sizeof(serv_addr);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) != 1) {
        printf("inet_pton() returned %d\n", errno);
        return -1;
    }


    // Connect to server-fd
    if (connect(sockfd, (const struct sockaddr *) &serv_addr, (socklen_t) servAddrSize) != 0) {
        printf("Connection failed with error code %d\n", errno);
    }


    return 0;
}