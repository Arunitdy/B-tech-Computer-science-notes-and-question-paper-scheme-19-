// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#define PORT 9000
#define MAX 1024

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    char buffer[MAX];
    int expected_seq = 0;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);
    printf("Server listening on port %d...\n", PORT);

    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("Client connected.\n");

    srand(time(NULL));
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recv(client_sock, buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "END") == 0) break;

        int seq;
        sscanf(buffer, "SEQ:%d", &seq);

        printf("Received packet: %s\n", buffer);

        // Randomly drop some packets (simulate error/loss)
        if (rand() % 4 == 0) {
            printf("Simulating loss of packet SEQ:%d\n", seq);
            continue;  // No ACK sent
        }

        // Send ACK
        char ack[32];
        sprintf(ack, "ACK:%d", seq);
        send(client_sock, ack, strlen(ack), 0);
        printf("Sent %s\n", ack);
    }

    close(client_sock);
    close(server_sock);
    return 0;
}

