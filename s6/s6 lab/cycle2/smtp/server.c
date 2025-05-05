#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8888
#define BUFFER_SIZE 1024

void send_response(int client_sock, const char *message) {
	send(client_sock, message, strlen(message), 0);
}

void handle_client(int client_sock) {
	char buffer[BUFFER_SIZE] = {0};
	send_response(client_sock, "220 Simple SMTP Server\r\n");
	while (1) {
		memset(buffer, 0, sizeof(buffer));
		ssize_t bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
		if (bytes_received <= 0) break;
		printf("Client: %s", buffer);
		if (strncmp(buffer, "HELO", 4) == 0) {
			send_response(client_sock, "250 Hello, pleased to meet you\r\n");
		}
		else if (strncmp(buffer, "MAIL FROM:", 10) == 0) {
			send_response(client_sock, "250 Sender OK\r\n");
		}
		else if (strncmp(buffer, "RCPT TO:", 8) == 0) {
			send_response(client_sock, "250 Recipient OK\r\n");
		}
		else if (strncmp(buffer, "DATA", 4) == 0) {
			send_response(client_sock, "354 End data with <CR><LF>.<CR><LF>\r\n");
		}
		else if (strcmp(buffer, ".\r\n") == 0) {
			send_response(client_sock, "250 Message accepted for delivery\r\n");
		}
		else if (strncmp(buffer, "QUIT", 4) == 0) {
			send_response(client_sock, "221 Bye\r\n");
			break;
		}
		else {
			send_response(client_sock, "500 Command not recognized\r\n");
		}
	}
	close(client_sock);
	printf("Client disconnected.\n");
}


int setup_server_socket() {
	int server_sock;
	struct sockaddr_in server_addr;
	// Create socket
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == -1) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("Bind failed");
		close(server_sock);
		exit(EXIT_FAILURE);
	}
	if (listen(server_sock, 5) < 0) {
		perror("Listen failed");
		close(server_sock);
		exit(EXIT_FAILURE);
	}
	printf("SMTP Server listening on port %d...\n", PORT);
	return server_sock;
}


int main() {
	int server_sock = setup_server_socket();
	int client_sock;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	while (1) {
		client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
		if (client_sock < 0) {
			perror("Accept failed");
			continue;
		}
		printf("Client connected...\n");
		handle_client(client_sock);
	}
	close(server_sock);
	return 0;
}
