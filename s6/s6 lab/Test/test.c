#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock_fd, cfd;
    struct sockaddr_in saddr, caddr;
    
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("error in socket\n");
        return 0;
    }
    
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr);
    if (connect(sock_fd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
        printf("error in connect\n");
        return 0;
    }
    
    
    char *message[] = {"save", "hey", "there", "hello"};
    int num_messages = sizeof(message) / sizeof(message[0]);
    char buffer[1024];
    int ack = 0;
    for (int i = 0 ; i < num_messages; i++) {
        sprintf(buffer, "%d:%s",ack, message[i]);
        while(1) {
            if (send(sock_fd, buffer, sizeof(buffer), 0) > 0) {
                printf("%s send\n",message[i]);
                break;
            }
            printf("resending message\n");
        }
        ack++;
        sleep(1);
    }
    
    printf("END\n");
    return 0;
}
