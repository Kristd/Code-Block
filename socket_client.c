#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int client() {
	int clientfd = -1;
	int port = 8181;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	bzero(&server_addr, sizeof(server_addr));
	bzero(&client_addr, sizeof(client_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	client_addr.sin_port = htons(0);
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	client_addr.sin_family = AF_INET;

	if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket failed\n");
	}

	if(bind(clientfd, (struct sockaddr*)&client_addr, sizeof(client_addr))) {
		printf("bind socket failed\n");
	}

	if(inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)) != 1) {
		printf("IP address error\n");
	}

	if(connect(clientfd, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
		printf("connect to server failed\n");
	}

	char buff[1024] = "hello server!";

	while(true) {
		send(clientfd, buff, 1024, 0);
		if(strcmp(buff, "bye") == 0) {
			break;
		}
		bzero(buff, 1024);
		recv(clientfd, buff, 1024, 0);
		printf("buff resp: %s\n", buff);
		bzero(buff, 1024);
		scanf("%s", buff);
	}

	printf("client close\n");
	return 0;
}

int main() {
	return client();
}
