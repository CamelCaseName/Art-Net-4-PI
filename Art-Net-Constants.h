#ifndef ART_NET_CONSTANTS
#define ART_NET_CONSTANTS

#pragma once

//#define MAKEADDRESSARRAY(a) {(BYTE)(((DWORD_PTR)a >> 24) & 0xFF), (BYTE)(((DWORD_PTR)a >> 16) & 0xFF), (BYTE)(((DWORD_PTR)a >> 8) & 0XFF), (BYTE)(((DWORD_PTR)a & 0XFF))}
template<typename T1, typename T2>
constexpr auto GETBYTE(T1 a, T2 b) { return (BYTE)(((DWORD_PTR)a >> 8 * (BYTE)(b & 0xFF)) & 0xFF); }
template<typename T1, typename T2, typename T3>
constexpr auto APPLYSUBNETMASK(T1 a, T2 b, T3 c) { return GETBYTE(a, c) == 0 ? GETBYTE(b, c) : GETBYTE(a, c); }

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
const char* ART_SUBNET_MASK = "0.255.255.255";
constexpr char OUTPUT_SIDE_X = 13;
constexpr char OUTPUT_SIDE_Y = (char)(((float)170 / (float)OUTPUT_SIDE_X) + 0.5f);

#endif