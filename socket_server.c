#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int server() {
	int serverfd = -1;
	int port = 8123;
	struct sockaddr_in server;
	bzero(&server, sizeof(server));

	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverfd < 0) {
		printf("create socket failed\n");
	}

	if(bind(serverfd, (struct sockaddr*)&server, sizeof(server))) {
		printf("bind socket address failed\n");
	}

	if(listen(serverfd, 20)) {
		printf("listen on port %d failed\n", port);
	}
	else {
		printf("server listening..\n");
	}

	while(true) {
		struct sockaddr_in client;
		bzero(&client, sizeof(client));
		socklen_t length = sizeof(client);

		int clientfd = accept(serverfd, (struct sockaddr*)&client, &length);

		if(clientfd < 0) {
			printf("accept client failed\n");
		}
		else {
			printf("connect succ\n");
		}

		char buff[1024];
		bzero(buff, 1024);
		int len = 0;
		//int len = recv(clientfd, buff, 1024, 0);

		while((len = recv(clientfd, buff, 1024, 0)) >= 0) {
			if(strcmp(buff, "bye") == 0) {
				printf("clinet close\n");
				break;
			}
			printf("buff revc: %s\n", buff);
			bzero(buff, 1024);
			strcpy(buff, "msg revced");
			send(clientfd, buff, 1024, 0);
		}
	}

	printf("server close\n");
	return 0;
}

int main() {
	return server();
}
