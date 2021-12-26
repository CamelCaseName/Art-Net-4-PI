// Art-Net-4-PI.cpp : Defines the entry point for the application.

#include "Art-Net-4-PI.h"

using namespace std;

void send_reply_packet(sockaddr_in socket_data, int socket_fd, ULONG device_address, ULONG counter) {
	//create node status
	char message_string[] = "hi there :)";
	char format_string[] = "#%d[%d]%s";
	char node_report[64] = {};
	snprintf((char*)node_report, 64, (char*)format_string, RC_POWER_OK, counter, message_string);

	//clean node report of trailing junk
	for (size_t i = 0; i < 63; i++) {
		if (node_report[i] == '\0') {
			node_report[i + 1] = '\0';
		}
	}

	if (node_report) {
		//create struct
		art_poll_reply_packet current_packet(device_address, node_report);

		//pack struct into the buffer to send from
		char buffer[BUFFER_SIZE] = {};
		if (buffer != nullptr) {

			//move struct to a buffer for sending
			memcpy(&buffer, &current_packet, sizeof(current_packet));

			//temp values for address manipulation
			ULONG address = 0;
			ULONG address_mask = 0;

			//"cast" mask to ulong
			inet_pton(AF_INET, ART_SUBNET_MASK, &address_mask);

			//add mask to address
			char address_format_string[] = "%d.%d.%d.%d";
			char address_string[17] = {};
			//so some string magic
			snprintf(
				(char*)address_string,
				17,
				(char*)address_format_string,
				APPLYSUBNETMASK(address_mask, device_address, 0),
				APPLYSUBNETMASK(address_mask, device_address, 1),
				APPLYSUBNETMASK(address_mask, device_address, 2),
				APPLYSUBNETMASK(address_mask, device_address, 3)
			);

			//"cast" address back into numbers
			inet_pton(AF_INET, address_string, &address);
			socket_data.sin_addr.s_addr = address;

			//send back to controller
			if (sendto(socket_fd, buffer, sizeof(current_packet), 0, (struct sockaddr*)&socket_data, sizeof(current_packet)) == WSAGetLastError()) {
				print_error("send failed\n");
			}

			//print notification and address
			char text_addr[17] = {};
			inet_ntop(AF_INET, &address, text_addr, sizeof(text_addr));
			printf("reply sent to: %s\n", text_addr);
		}
	}
}

void display_dmx(char* data, short len) {
#ifdef WINDOWS //on windows so console
	char id = 0;
	for (char i = 0; i < OUTPUT_SIDE_Y; i++) {
		for (char j = 0; j < OUTPUT_SIDE_X; j++) {
			//when using rgb profile
			id = (i * OUTPUT_SIDE_Y + j) * 3;
			if (id < len - 2) {
				cout << "\x1b[48;2;" << data[id] << ";" << data[id + 1] << ";" << data[id + 2] << "m";
			}
			break;
		}
		cout << endl;
	}
#else //raspi (or linux but why)
	printf("hi pi);
#endif // WINDOWS
}

void use_dmx_data(char* buffer) {
	//printf("DMX packet received\n");

	//create packet and populate
	art_dmx_packet packet = {};
	memcpy(&packet, buffer, BUFFER_SIZE);

	//check address to ensure only running correct data
	uint16_t port_address = (uint16_t)MAKEWORD(packet.sub_uni, packet.net);

	//create array to hold dmx data
	uint16_t dmx_data_length = (uint16_t)MAKEWORD(packet.length_lo, packet.length_hi);

	//create arrray
	char* dmx_data = (char*)calloc(dmx_data_length, sizeof(char));
	if (dmx_data != nullptr) {
		//move data to memory place for it
		memcpy(dmx_data, packet.data, dmx_data_length * sizeof(char));

		//display data, depending on build type :)
		display_dmx(dmx_data, dmx_data_length);

	}
	//give back memory (no leak)
	free(dmx_data);
}

int main(int argc, char* argv[]) {
	//windows specific stuff :(
#ifdef WINDOWS
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(1, 1), &wsa)) {
		print_error("wsa startup failed\n");
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
		char text_addr[17] = {};
		inet_ntop(AF_INET, &device_address, text_addr, sizeof(text_addr));
		printf("Please provide command line arguments, assuming address of %s\n", text_addr);
	}

	//creating socket
	socket_fd = (int)socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//check if socket was created
	if (socket_fd < 0) {
		print_error("socket creation failed\n");
	}

	//set options
	char options = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof(options)) == SOCKET_ERROR) {
		print_error("setsockopt failed\n");
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

			//check own address
			char text_address[17];
			inet_ntop(AF_INET, &sin_local.sin_addr, text_address, sizeof(text_address));

			switch (op_code) {
			case OP_POLL: {//poll to find all nodes, every 2 to 3 seconds
				send_reply_packet(sin_other, socket_fd, device_address, poll_counter++); //send reply and increase pollcounter
			}break;
			case OP_POLL_REPLY: {//reply to poll packets
				//ignore
			}break;
			case OP_DIAG_DATA: {//diagnostics and logging
			}break;
			case OP_DMX: {//dmx data
				use_dmx_data(buffer);
			}break;
			case OP_NZS: {//nonzero start code dmx data
			}break;
			case OP_SYNC: {//time sync packet
			}break;
			case OP_ADDRESS: {//remote address programming info
			}break;
			case OP_RDM: {//rdm data (no discovery)
			}break;
			case OP_TOD_REQUEST: {//Table of Device discorvery request
			}break;
			case OP_TOD_DATA: {//table of device answer
			}break;
			default: {//display info to console
				printf("received something from :%s\n", text_address);
				//printf("\n");
				printf(buffer);
				printf("\n");
				printf("%d\n", op_code);
			}break;
			}
		}
	}

	WSACleanup();
	return 0;
}