// Art-Net-4-PI.cpp : Defines the entry point for the application.
//

#include "Art-Net-4-PI.h"

using namespace std;

int main() {
	//port for art-net
	const int port = ART_NET_PORT_NUMBER;

	//file descriptor for the socket
	int socket_fd;

	//socket adresses
	struct sockaddr_in sin_local {}, sin_other{};

	//buffer for the data
	char buffer[1024];

	//length of a socket adress
	socklen_t addr_len;

	//creating socket
	socket_fd = (int)socket(AF_INET, SOCK_DGRAM, 0);

	//memset(&socket_in_local, '\0', sizeof(socket_in_local));
	sin_local.sin_family = AF_INET;
	sin_local.sin_port = htons(port);
	sin_local.sin_addr.s_addr = INADDR_ANY;

	//binding to socket
	if (!bind(socket_fd, (struct sockaddr*)&sin_local, sizeof(sin_local))) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	addr_len = sizeof(sin_other);

	//receiving from socket
	recvfrom(socket_fd, buffer, 1024, 0, (struct sockaddr*)&sin_other, &addr_len);

	//printing from socket
	printf("[+]Data Received: %s", buffer);

	//cast buffer into art-net struct depending on op-code and integrity

	return 0;
}