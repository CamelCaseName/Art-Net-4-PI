// Art-Net-4-PI.cpp : Defines the entry point for the application.
//

#include "Art-Net-4-PI.h"

using namespace std;

int main() {
#ifdef WINDOWS
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(1, 1), &wsa)) {
		handle_error("wsa startup failed");
	}
#endif // WINDOWS

	//port for art-net
	const int port = ART_NET_PORT_NUMBER;

	//file descriptor for the socket
	int socket_fd;

	//socket adresses
	struct sockaddr_in sin_local {}, sin_other{};

	//buffer for the data
	char buffer[BUFFER_SIZE];

	//length of a socket adress
	socklen_t addr_len;

	//creating socket
	socket_fd = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (socket_fd < 0) {
		handle_error("socket creation failed");
	}

	//populate socket info
	memset(&sin_local, '\0', sizeof(sin_local));
	sin_local.sin_family = AF_INET;
	sin_local.sin_port = htons(port);
	sin_local.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");

	//binding to socket
	if (bind(socket_fd, (struct sockaddr*)&sin_local, sizeof(sin_local))) {
		handle_error("bind failed");
	}
	addr_len = sizeof(sin_other);

	//check socket and act on it
	while (true) {

		//receiving from socket
		recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&sin_other, &addr_len);

		char header[8] = { buffer[0],buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7] };
		uint16_t op_code = MAKEWORD(buffer[9], buffer[8]);

		if (header != "Art-Net") {
			//ignore later, now for debugging
			//printf("packet header illegal\n");
			//exit(EXIT_FAILURE);
			printf(buffer);
			printf("\n");
		}
		else {
			printf("packet found\n");
			printf(header);
			exit(0);
		}

		//cast buffer into art-net struct depending on op-code and integrity

	}
	return 0;
}