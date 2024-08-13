#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>



#define PORT 8080


#define BUFFER_SIZE 1024


void ClientWriter(int sockfd) {
    char buffer[BUFFER_SIZE] = {0};
    printf("Enter message (\"KILL\" to close socket):\n");


    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        printf("Error on fgets()");
    }

    // buffer[strcspn(buffer, "\n")] = '\0';


    if (strcmp(buffer, "KILL\n") == 0) {
        printf("should die\n");
        close(sockfd);
    }

    // if (send(sockfd, buffer, strlen(buffer)) != strlen(buffer) + 1) {
    //     printf("issue with send()");
    // };

    assert(send(sockfd, buffer, strlen(buffer), 0) == strlen(buffer));

    return;
}




int main() {
    // Socket used to communicate with server
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

    char serverIPAddr[16] = {0};

    fwrite("Enter server IP: ", sizeof(char), strlen("Enter server IP: "), stdout);
    // fread(serverIPAddr, 32, sizeof(char), stdin);
    fgets(serverIPAddr, 16, stdin);
    serverIPAddr[strcspn(serverIPAddr, "\n")] = '\0';

    // printf("\nIP: %s", serverIPAddr);



    // char *serverIPAddr = "127.0.0.1";
    // char *serverIPAddr = "10.0.0.50";


    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, serverIPAddr, &serv_addr.sin_addr) != 1) {
        printf("inet_pton() returned %d\n", errno);
        return -1;
    }


    // Connect to server-fd
    if (connect(sockfd, (const struct sockaddr *) &serv_addr, (socklen_t) servAddrSize) != 0) {
        printf("Connection failed with error code %d\n", errno);
        return -1;
    }

    while (1) {
        ClientWriter(sockfd);
    }


    return 0;
}