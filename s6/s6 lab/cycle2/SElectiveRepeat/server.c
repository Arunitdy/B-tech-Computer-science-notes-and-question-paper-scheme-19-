// selective_repeat_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define TOTAL_PACKETS 10
#define WINDOW_SIZE 4

int main() {
    int sock_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];
    int received[TOTAL_PACKETS] = {0}; // store which packets we've received

    srand(time(NULL)); // for simulating loss

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);

    bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(sock_fd, 5);
    client_fd = accept(sock_fd, (struct sockaddr*)&client_addr, &addr_len);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(client_fd, buffer, sizeof(buffer), 0);
        if (len <= 0) break;

        int seq;
        sscanf(buffer, "%d", &seq);
        printf("Received packet: %d\n", seq);

        if (seq >= 0 && seq < TOTAL_PACKETS && !received[seq]) {
            // Simulate 20% packet loss
            if (rand() % 5 != 0) {
                received[seq] = 1;
                sprintf(buffer, "%d", seq);
                send(client_fd, buffer, strlen(buffer), 0);
                printf("Sent ACK: %d\n", seq);
            } else {
                printf("Simulated ACK loss for packet: %d\n", seq);
            }
        } else if (received[seq]) {
            // Resend ACK if it's a duplicate
            sprintf(buffer, "%d", seq);
            send(client_fd, buffer, strlen(buffer), 0);
            printf("Resent ACK for duplicate packet: %d\n", seq);
        }
    }

    close(client_fd);
    close(sock_fd);
    return 0;
}

