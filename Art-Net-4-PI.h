﻿// Art-Net-4-PI.h

//############################################################################
//using Art-Net™ Designed by and Copyright Artistic Licence Holdings Ltd
//############################################################################
#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#define WINDOWS
#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "Art-NetOemCodes.h" //pulled from https://artisticlicence.com/WebSiteMaster/Software/Art-Net/Art-NetOemCodes.h
#include "Art-Net-Codes.h" //manually typed code macros from the latest Art-Net 4 documentation 
#include "Art-Net-Structs.h" //manually typed struct definitions from the latest Art-Net 4 documentation 

constexpr int BUFFER_SIZE = 64;

void handle_error(char* reason) {
#ifdef WINDOWS
	perror(reason);
	int last_error = WSAGetLastError();
	printf("last error encountered was %d", last_error);
	exit(EXIT_FAILURE);
#else
	perror(" failed");
	exit(EXIT_FAILURE);
#endif // WINDOWS
}