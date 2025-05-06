#include <stdio.h>
#include <arpa/inet.h>

int main() {
  int sfd, cfd;
  struct sockaddr_in saddr, caddr;
  
  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) { 
    printf("error in socket\n");
    return 0;
  }
  
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(7888);
  if (inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr) < 0) {
      printf("error\n");
      return 0;
  }
  if (connect(sfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
      
      printf("error connect\n");
  }
   char buffer[1024] = {0};
    recv(sfd, buffer, sizeof(buffer), 0);
    printf("Message from server: %s\n", buffer);
  int a[] = {7,8,7,5};
  send(sfd, a, sizeof(a), 0);

  printf("connect in clientr\n");
  return 0;

}
