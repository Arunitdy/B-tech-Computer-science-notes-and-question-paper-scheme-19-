#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main() {
  int server_fd, new_socket;
  struct sockaddr_in server_address;
  socklen_t address_length = sizeof(server_address);
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("Failed to create socket");
    return 1;
  }
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_address.sin_port = htons(8080);
  if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    perror("Binding failed");close(server_fd);
    return 1;
  }
  if (listen(server_fd, 3) < 0) {
    perror("Failed to listen");
    close(server_fd);
    return 1;
  }
  printf("Server is listening on port 8080...\n");
  new_socket = accept(server_fd, (struct sockaddr *)&server_address, &address_length);
  if (new_socket < 0) {
    perror("Failed to accept connection");
    close(server_fd);
    return 1;
  }
  char filename[100], buffer[1000];
  int bytes_received = recv(new_socket, filename, sizeof(filename) - 1, 0);
  if (bytes_received < 0) {
    perror("Failed to receive filename");
    close(new_socket);
    close(server_fd);
    return 1;
  }
  filename[bytes_received] = '\0';
  printf("Requested file: %s\n", filename);
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("File not found");
    send(new_socket, "File not found", strlen("File not found"), 0);
    close(new_socket);
    close(server_fd);
    return 1;
  }
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    send(new_socket, buffer, strlen(buffer), 0);
  }
  printf("File sent successfully!\n");
  fclose(file);
  close(new_socket);
  close(server_fd);
  return 0;

}
