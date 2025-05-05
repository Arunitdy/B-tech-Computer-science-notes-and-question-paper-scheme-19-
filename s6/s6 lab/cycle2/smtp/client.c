#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define PORT 8888
#define MAX_EMAIL 256
#define MAX_SUBJECT 512
#define MAX_MESSAGE 1024
#define MAX_COMMAND 512
#define MAX_RESPONSE 1024


void send_command(int sock, const char *command) {
	char response[MAX_RESPONSE] = {0};
	send(sock, command, strlen(command), 0);
	recv(sock, response, sizeof(response) - 1, 0);
	printf("Server: %s", response);
}
int main() {
	int sock;
	struct sockaddr_in server_addr;
	char sender[MAX_EMAIL], recipient[MAX_EMAIL], subject[MAX_SUBJECT];
	char message[MAX_MESSAGE], temp[MAX_MESSAGE];
	printf("Enter sender email: ");
	
	fgets(sender, sizeof(sender), stdin);
	sender[strcspn(sender, "\n")] = 0;
	printf("Enter recipient email: ");
	
	fgets(recipient, sizeof(recipient), stdin);
	recipient[strcspn(recipient, "\n")] = 0;
	printf("Enter subject: ");
	
	fgets(subject, sizeof(subject), stdin);
	subject[strcspn(subject, "\n")] = 0;
	printf("Enter message body (end with a single dot '.' on a new line):\n");
	message[0] = '\0';
	
	while (1) {
		fgets(temp, sizeof(temp), stdin);
		if (strcmp(temp, ".\n") == 0) break;
		if (strlen(message) + strlen(temp) >= MAX_MESSAGE - 1) {
			printf("Message too long. Truncating.\n");
			break;
		}
		strcat(message, temp);
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("Connection failed");
		close(sock);
		exit(EXIT_FAILURE);
	}
	char buffer[MAX_RESPONSE] = {0};
	recv(sock, buffer, sizeof(buffer) - 1, 0);
	printf("Server: %s", buffer);
	send_command(sock, "HELO localhost\r\n");
	char mail_from[MAX_COMMAND];
	
	snprintf(mail_from, sizeof(mail_from), "MAIL FROM:<%s>\r\n", sender);
	
	send_command(sock, mail_from);
	char rcpt_to[MAX_COMMAND];
	
	snprintf(rcpt_to, sizeof(rcpt_to), "RCPT TO:<%s>\r\n", recipient);
	
	send_command(sock, rcpt_to);
	send_command(sock, "DATA\r\n");
	char email_content[MAX_MESSAGE + MAX_SUBJECT + 100];
	
	snprintf(email_content, sizeof(email_content),
	"Subject: %s\r\n\r\n%s\r\n.\r\n", subject, message);
	
	send_command(sock, email_content);
	send_command(sock, "QUIT\r\n");
	close(sock);
	return 0;
}

