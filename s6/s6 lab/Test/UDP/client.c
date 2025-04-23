#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main() {
    
    int sockfd;
    struct sockaddr_in saddr, caddr;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
      printf("error in socket\n");
      return 0;
    }
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(8888);
    
    char message[] = "Hi";
    int s = sendto(sockfd ,message ,sizeof(message), 0, (struct sockaddr*)&saddr, sizeof(saddr));
    
    return 0;
}
