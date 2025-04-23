#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    int sock_fd, cfd;
    struct sockaddr_in saddr, caddr;
    
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("error in socket\n");
        return 0;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(8888);
    
    if (bind(sock_fd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
        printf("error in bind\n");
        return 0;
    }
    if (listen(sock_fd, 3) < 0) {
        printf("error in listen\n");
        return 0;
    }
    int size = sizeof(caddr);
    int c = accept(sock_fd, (struct sockaddr*)&caddr, &size);
    if (c < 0) {
      printf("error in accept\n");
      return 0;
    }
    
    
    char buffer[1024];
    char message[1024];
    int ack;
    while (1) {
        if(recv(c, buffer, sizeof(buffer), 0) <= 0) {
            break;
        }
        sscanf(buffer, "%d:%s",&ack, message);
        printf("%d, %s\n",ack, message);
    }
    
    
    printf("END\n");
    return 0; 
} 
