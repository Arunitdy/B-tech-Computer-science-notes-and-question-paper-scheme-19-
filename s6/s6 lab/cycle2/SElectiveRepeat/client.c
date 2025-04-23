// selective_repeat_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define TOTAL_PACKETS 10
#define WINDOW_SIZE 4
#define TIMEOUT_LIMIT 3

typedef struct {
    int seq;
    int acked;
    int sent_count;
} Packet;

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    Packet window[TOTAL_PACKETS];

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect");
        return 1;
    }

    // Initialize packets
    for (int i = 0; i < TOTAL_PACKETS; i++) {
        window[i].seq = i;
        window[i].acked = 0;
        window[i].sent_count = 0;
    }

    int base = 0;
    while (base < TOTAL_PACKETS) {
        // Send packets within window
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_PACKETS; i++) {
            if (!window[i].acked && window[i].sent_count < TIMEOUT_LIMIT) {
                snprintf(buffer, sizeof(buffer), "%d", window[i].seq);
                send(sock_fd, buffer, strlen(buffer), 0);
                printf("Sent packet: %d\n", window[i].seq);
                window[i].sent_count++;
                usleep(100000); // simulate delay
            }
        }

        // Receive ACK
        memset(buffer, 0, sizeof(buffer));
        int len = recv(sock_fd, buffer, sizeof(buffer), 0);
        if (len > 0) {
            int ack;
            sscanf(buffer, "%d", &ack);
            printf("Received ACK: %d\n", ack);
            if (ack >= base && ack < TOTAL_PACKETS) {
                window[ack].acked = 1;
                // Slide base if possible
                while (window[base].acked && base < TOTAL_PACKETS) {
                    base++;
                }
            }
        }
    }

    printf("All packets sent and acknowledged!\n");
    close(sock_fd);
    return 0;
}

