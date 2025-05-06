#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Socke t creation failed");
    return 1;
  }
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8080);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed");
    close(sockfd);
    return 1;
  }
  printf("Connected to the server successfully\n");
  char filename[100];
  printf("Enter the filename: ");
  scanf("%99s", filename);
  if (send(sockfd, filename, strlen(filename), 0) < 0) {
    perror("Failed to send filename");
    close(sockfd);
    return 1;
  }
  char buffer[1000];
  int bytes_received;
  printf("\nReceiving file contents:\n");
  while ((bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
    buffer[bytes_received] = '\0';
    printf("%s", buffer);
  }
  if (bytes_received < 0) {
    perror("Error receiving file data");
  }
  printf("\nFile transfer complete!\n");
  return 0;
}
