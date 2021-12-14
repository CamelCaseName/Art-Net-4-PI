// Art-Net-4-PI.cpp : Defines the entry point for the application.
//

#include "Art-Net-4-PI.h"
#include "Art-Net-Structs.h" //manually typed struct definitions from the latest Art-Net 4 documentation 

using namespace std;

void send_reply_packet(IN_ADDR address, int socket_fd, ULONG device_address, ULONG counter) {
	//create node status
	char message_string[] = "hi there :)";
	char format_string[] = "#%d[%d]%s";
	char node_report[64] = {};
	snprintf((char*)node_report, 64, (char*)format_string, RC_POWER_OK, counter, message_string);

	if (node_report) {
		//create struct
		art_poll_reply_packet current_packet(device_address, node_report);

		//pack struct into the buffer to send from
		char buffer[BUFFER_SIZE] = {};
		if (buffer != nullptr) {

			//move struct to a buffer for sending
			memcpy(buffer, &current_packet, sizeof(current_packet));

			//send to controller
			sendto(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&address, BUFFER_SIZE);

			printf("Sent reply packet\n");
		}
	}
}

int main(int argc, char* argv[]) {
	//windows specific stuff :(
#ifdef WINDOWS
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(1, 1), &wsa)) {
		print_error("wsa startup failed");
	}
#endif // WINDOWS

	//port for art-net
	const int port = ART_NET_PORT_NUMBER;
	const char* art_net_name = "Art-Net";
	long poll_counter = 0;
	bool header_ok = false;

	//create localhost address for fallback
	ULONG device_address = 0;
	inet_pton(AF_INET, LOCALHOST_ADDRESS, &device_address);

	//file descriptor for the socket
	int socket_fd;

	//socket adresses
	struct sockaddr_in sin_local {}, sin_other{};

	//buffer for the data
	char buffer[BUFFER_SIZE];

	//length of a socket adress
	socklen_t addr_len;

	//get address from input, if possible
	if (argc > 1) {
		inet_pton(AF_INET, argv[2], &device_address);
	}
	else {//assume localhost
		char text_addr[16] = {};
		inet_ntop(AF_INET, &device_address, text_addr, sizeof(text_addr));
		printf("Please provide command line arguments, assuming address of %s\n", text_addr);
	}

	//creating socket
	socket_fd = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//check if socket was created
	if (socket_fd < 0) {
		print_error("socket creation failed");
	}

	//set options
	char options = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(options)) == SOCKET_ERROR) {
		print_error("setsockopt failed");
	}


	//populate socket info
	memset(&sin_local, '\0', sizeof(sin_local));
	sin_local.sin_family = AF_INET;
	sin_local.sin_port = htons(port);
	sin_local.sin_addr.s_addr = device_address;

	//binding to socket
	if (bind(socket_fd, (struct sockaddr*)&sin_local, sizeof(sin_local))) {
		print_error("bind failed");
	}


	addr_len = sizeof(sin_other);

	printf(INFO_OUTPUT_STRING, port);

	//check socket and act on it
	while (true) {

		//receiving from socket
		recvfrom(socket_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&sin_other, &addr_len);

		//create opcode from buffer
		uint16_t op_code = MAKEWORD(buffer[8], buffer[9]);

		//check header
		for (size_t i = 0; i < 8; i++) {
			if (art_net_name[i] != buffer[i]) {
				header_ok = false;
				break;
			}
			header_ok = true;
		}

		if (!header_ok) {
			//packet got mangled, scrap
			printf("received malformed header, ignoring packet\n");
			printf(buffer);
			printf("\n");
		}
		else {//correct packet found, determine type then act on it


			switch (op_code) {
			case OP_POLL: {
				art_net_packet current_packet = {};
				//move buffer into packet depending on packet type
				memcpy(&current_packet, buffer, sizeof(current_packet));
				send_reply_packet(sin_other.sin_addr, socket_fd, device_address, poll_counter++); //send reply and increase pollcounter
			}
						break;
			case OP_POLL_REPLY:
				break;
			case OP_DIAG_DATA:
				break;
			case OP_DMX:
				break;
			case OP_NZS:
				break;
			case OP_SYNC:
				break;
			case OP_ADDRESS:
				break;
			case OP_RDM:
				break;
			default:
				//check own address
				char text_address[16];
				inet_ntop(AF_INET, &sin_local.sin_addr, text_address, sizeof(text_address));
				//printf(text_address);
				//printf("\n");
				printf(buffer);
				printf("\n");
				printf("%d\n", op_code);
				break;
			}
		}

		//cast buffer into art-net struct depending on op-code and integrity

	}

	WSACleanup();
	return 0;
}