#include <stdio.h>
#include <arpa/inet.h>


int main () {
  int sockfd, cfd;
  struct sockaddr_in saddr, caddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
      printf("error in socket \n");
      return 0;
  }
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  saddr.sin_port = htons(7888);
  
  if (bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
    printf("error bind\n");
    return 0;
  }
  
  if (listen(sockfd, 3) < 0) {
    printf("error listen\n");
    return 0;
  }
  int size =  sizeof(caddr);
  cfd = accept(sockfd, (struct sockaddr*)&caddr, &size);
  if ( cfd < 0 ) {
    printf("error accept\n");
    return 0;
  }
  char buffer[1024] = "hey there!";
  send(cfd, buffer, sizeof(buffer), 0);
    int a[4];
    recv(cfd, &a, sizeof(a), 0);
   for (int i =0 ; i < 4; i++) { 
      printf("number:%d\n",a[i]);
   }
  printf("connect in server\n");
  return 0;
}
