#ifndef ART_NET_4_PI_H
#define ART_NET_4_PI_H
// Art-Net-4-PI.h

//############################################################################
//using Art-Net™ Designed by and Copyright Artistic Licence Holdings Ltd
//############################################################################
#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <string>
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

void print_error(char* reason) {
#ifdef WINDOWS
	perror(reason);
	int last_error = WSAGetLastError();
	printf("last error encountered was %d\n", last_error);
	exit(EXIT_FAILURE);
#else
	perror(" failed");
	exit(EXIT_FAILURE);
#endif // WINDOWS
}

#define MAKEADDRESSARRAY(a) {(BYTE)(((DWORD_PTR)a >> 24) & 0xFF), (BYTE)(((DWORD_PTR)a >> 16) & 0xFF), (BYTE)(((DWORD_PTR)a >> 8) & 0XFF), (BYTE)(((DWORD_PTR)a & 0XFF))}
template<typename T1, typename T2>
constexpr auto GETBYTE(T1 a, T2 b) { return (BYTE)(((DWORD_PTR)a >> 8 * (BYTE)(b & 0xFF)) & 0xFF); }

constexpr auto DEFAULT_STATUS1 = NULL;
constexpr auto DEBUG_STATUS1 = STATUS_INDICATORS_NORMAL | STATUS_PORT_ADRESS_NETWORK | STATUS_FLASH_BOOT | STATUS_RDM_CAPABLE | STATUS_UBEA_NOT_PRESENT;
constexpr auto DEFAULT_STATUS2 = NULL;
constexpr auto DEFAULT_STATUS3 = NULL;
constexpr auto DEFAULT_GOOD_OUTPUT = GOOD_OUTPUT_B_RDM_ENABLED | GOOD_OUTPUT_B_OUT_STYLE_CONTINUOUS;
constexpr int BUFFER_SIZE = 1024;
constexpr char* LOCALHOST_ADDRESS = "127.0.0.1";
constexpr auto FIRMWARE_VERSION = 0x0412;
constexpr auto ESTA_MANUFACTURER_CODE = 0x414c;
//constexpr auto DEVICE_NAME = "pixelflut by rinderhacc on a PI4B";
constexpr auto DEVICE_NAME = "pixelflut by rinderhacc on a PI4B                              ";
//constexpr auto SHORT_DEVICE_NAME = "pixelflut";
constexpr auto SHORT_DEVICE_NAME = "pixelflut        ";
const char* INFO_OUTPUT_STRING = "########################################\n##  Art-Net-4-PI running on port %d ##\n##   ready to receive packets now...  ##\n########################################\n";


#endif // !ART_NET_4_PI_H