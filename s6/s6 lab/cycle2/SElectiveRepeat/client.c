// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <stdbool.h>
#define PORT 9000
#define MAX 1024
#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10
#define TIMEOUT_SEC 2

typedef struct {
    int seq;
    bool acked;
    char data[MAX];
} Packet;

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[MAX];
    Packet packets[TOTAL_PACKETS];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Connected to server.\n");

    // Prepare packets
    for (int i = 0; i < TOTAL_PACKETS; i++) {
        packets[i].seq = i;
        packets[i].acked = false;
        sprintf(packets[i].data, "SEQ:%d", i);
    }

    int base = 0;
    fd_set readfds;
    struct timeval timeout;

    while (base < TOTAL_PACKETS) {
        // Send all packets in the window that haven’t been ACKed
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_PACKETS; i++) {
            if (!packets[i].acked) {
                send(sock, packets[i].data, strlen(packets[i].data), 0);
                printf("Sent packet: %s\n", packets[i].data);
            }
        }

        // Wait for ACKs with timeout
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);
        timeout.tv_sec = TIMEOUT_SEC;
        timeout.tv_usec = 0;

        int activity = select(sock + 1, &readfds, NULL, NULL, &timeout);
        if (activity > 0 && FD_ISSET(sock, &readfds)) {
            memset(buffer, 0, sizeof(buffer));
            recv(sock, buffer, sizeof(buffer), 0);

            int ack_seq;
            if (sscanf(buffer, "ACK:%d", &ack_seq) == 1) {
                packets[ack_seq].acked = true;
                printf("Received ACK: %d\n", ack_seq);

                // Slide window
                while (base < TOTAL_PACKETS && packets[base].acked)
                    base++;
            }
        } else {
            printf("Timeout: Resending unacknowledged packets in window...\n");
        }
    }

    send(sock, "END", 3, 0);
    close(sock);
    return 0;
}

