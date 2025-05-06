#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024
    int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int seq_num = 0;
    char *messages[] = {"Hello", "This", "Is", "Stop-and-Wait", "ARQ"};
    
    int num_messages = sizeof(messages) / sizeof(messages[0]);
    
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
    
    for (int i = 0; i < num_messages; i++) {
        while (1) {
                sprintf(buffer, "%d:%s", seq_num, messages[i]);
                send(sock, buffer, strlen(buffer), 0);
                printf("Sent: %s\n", messages[i]);
                memset(buffer, 0, BUFFER_SIZE);
                recv(sock, buffer, BUFFER_SIZE, 0);
                int ack;
                sscanf(buffer, "%d", &ack);
                
                if (ack == seq_num) {
                    printf("ACK %d received\n", ack);
                    seq_num++;
                    break;
            } else {
                printf("ACK mismatch, resending...\n");sleep(1);
            }
        }
    }
    close(sock);
    return 0;
}
