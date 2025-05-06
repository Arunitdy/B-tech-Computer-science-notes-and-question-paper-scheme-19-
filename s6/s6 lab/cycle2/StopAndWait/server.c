#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024
    int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    int expected_seq = 0;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
       perror("Listen failed");exit(EXIT_FAILURE);
    }
    
    printf("Waiting for connection...\n");
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    
    if (new_socket < 0) {
      perror("Accept failed");
      exit(EXIT_FAILURE);
    }
    
    printf("Client connected.\n");
    
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
           break;
        }
        int seq_num;
        char message[BUFFER_SIZE];
        sscanf(buffer, "%d:%s", &seq_num, message);
        if (seq_num == expected_seq) {
            printf("Received: %s\n", message);
            expected_seq++;
        } else {
           printf("Duplicate packet detected, resending last ACK.\n");
        }
        char ack[12];
        sprintf(ack, "%d", expected_seq - 1);
        send(new_socket, ack, strlen(ack), 0);
    }
    close(new_socket);
    close(server_fd);
    return 0;
}
