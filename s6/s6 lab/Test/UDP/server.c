#include <stdio.h>
#include<arpa/inet.h>

int main() {
    
    int sockfd , cfd;
    struct sockaddr_in saddr, caddr;
    
    sockfd =  socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("error in socket\n");
        return 0;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(8888);
    
    if (bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0 ) {
        printf("error in bind\n");
        return 0;
    }
    char message[1024];
    int size =sizeof(caddr);
    int n = recvfrom(sockfd, message, sizeof(message), 0, (struct sockaddr*)&caddr, &size);
    printf("%s",message);
    return 0;
}
