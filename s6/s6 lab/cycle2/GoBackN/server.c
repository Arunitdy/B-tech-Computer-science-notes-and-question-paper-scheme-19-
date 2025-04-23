#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 12346
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024
#define WINDOW_SIZE 3
int main() {
    int sock;struct sockaddr_in server_addr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server.\n");
    
    
    char buffer[BUFFER_SIZE];
    int base = 0, next_seq = 0;
    char *messages[] = {"Message1", "Message2", "Message3", "Message4", "Message5"};
    int num_messages = sizeof(messages) / sizeof(messages[0]);
    
    while (base < num_messages) {
        // Send packets within the window
        while (next_seq < base + WINDOW_SIZE && next_seq < num_messages) {
            sprintf(buffer, "%d:%s", next_seq, messages[next_seq]);
            send(sock, buffer, strlen(buffer), 0);
            printf("Sent: %s (Seq %d)\n", messages[next_seq], next_seq);
            next_seq++;
        }
        // ereceive ACK
        memset(buffer, 0, BUFFER_SIZE);
        recv(sock, buffer, BUFFER_SIZE, 0);
        int ack;
        sscanf(buffer, "%d", &ack);
        printf("ACK received: %d\n", ack);
        if (ack > base) {
            base = ack;
        } else {
            printf("Timeout detected, resending window...\n");
            next_seq = base; // retransmit from base
        }
        sleep(1);
    }
    
    
    close(sock);
    return 0;
}
