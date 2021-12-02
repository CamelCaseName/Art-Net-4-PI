#ifndef ART_NET_CODES_H
#define ART_NET_CODES_H

//############################################################################
//using Art-Net™ Designed by and Copyright Artistic Licence Holdings Ltd
//############################################################################

#pragma region op_codes
constexpr auto OP_POLL = 0x2000; //This is an ArtPoll packet, no other data is contained in this UDP packet.
constexpr auto OP_POLL_REPLY = 0x2100; //This is an ArtPollReply Packet. It contains device status information.
constexpr auto OP_DIAG_DATA = 0x2300; //Diagnostics and data logging packet.
constexpr auto OP_COMMAND = 0x2400; //Used to send text based parameter commands.
constexpr auto OP_OUTPUT = 0x5000; //This is an ArtDmx data packet. It contains zero start code DMX512 information for a single Universe.
constexpr auto OP_DMX = 0x5000; //This is an ArtDmx data packet. It contains zero start code DMX512 information for a single Universe.
constexpr auto OP_NZS = 0x5100; //This is an ArtNzs data packet. It contains non-zero start code(except RDM) DMX512 information for a single Universe.
constexpr auto OP_SYNC = 0x5200; //This is an ArtSync data packet. It is used to force synchronous transfer of ArtDmx packets to a node’s output.
constexpr auto OP_ADDRESS = 0x6000; //This is an ArtAddress packet.It contains remote programming information for a Node.
constexpr auto OP_INPUT = 0x7000; //This is an ArtInput packet. It contains enable – disable data for DMX inputs.
constexpr auto OP_TOD_REQUEST = 0x8000; //This is an ArtTodRequest packet. It is used to request a Table of Devices(ToD) for RDM discovery.
constexpr auto OP_TOD_DATA = 0x8100; //This is an ArtTodData packet. It is used to send a Table of Devices(ToD) for RDM discovery.
constexpr auto OP_TOD_CONTROL = 0x8200; //This is an ArtTodControl packet. It is used to send RDM discovery control messages.
constexpr auto OP_RDM = 0x8300; //This is an ArtRdm packet. It is used to send all non discovery RDM messages.
constexpr auto OP_RDM_SUB = 0x8400; //This is an ArtRdmSub packet. It is used to send compressed, RDM Sub - Device data.
constexpr auto OP_VIDEO_SETUP = 0xa010; //This is an ArtVideoSetup packet. It contains video screen setup information for nodes that implement the extended video features.
constexpr auto OP_VIDEO_PALETTE = 0xa020; //This is an ArtVideoPalette packet. It contains colour palette setup information for nodes that implement the extended video features.
constexpr auto OP_VIDEO_DATA = 0xa040; //This is an ArtVideoData packet. It contains display data for nodes that implement the extended video features.
constexpr auto OP_MAC_MASTER = 0xf000; //This packet is deprecated.
constexpr auto OP_MAC_SLAVE = 0xf100; //This packet is deprecated.
constexpr auto OP_FIRMWARE_MASTER = 0xf200; //This is an ArtFirmwareMaster packet. It is used to upload new firmware or firmware extensions to the Node.
constexpr auto OP_FIRMWARE_REPLY = 0xf300; //This is an ArtFirmwareReply packet. It is returned by the node to acknowledge receipt of an ArtFirmwareMaster packet or ArtFileTnMaster packet.
constexpr auto OP_FILE_TN_MASTER = 0xf400; //Uploads user file to node.
constexpr auto OP_FILE_FN_MASTER = 0xf500; //Downloads user file from node.
constexpr auto OP_FILE_FN_REPLY = 0xf600; //Server to Node acknowledge for download packets.
constexpr auto OP_IP_PROG = 0xf800; //This is an ArtIpProg packet. It is used to reprogramme the IP address and Mask of the Node.
constexpr auto OP_IP_PROG_REPLY = 0xf900; //This is an ArtIpProgReply packet. It is returned by the node to acknowledge receipt of an ArtIpProg packet.
constexpr auto OP_MEDIA = 0x9000; //This is an ArtMedia packet. It is Unicast by a Media Server and acted upon by a Controller.
constexpr auto OP_MEDIA_PATCH = 0x9100; //This is an ArtMediaPatch packet. It is Unicast by a Controller and acted upon by a Media Server.
constexpr auto OP_MEDIA_CONTROL = 0x9200; //This is an ArtMediaControl packet. It is Unicast by a Controller and acted upon by a Media Server.
constexpr auto OP_MEDIA_CONTRL_REPLY = 0x9300; //This is an ArtMediaControlReply packet. It is Unicast by a Media Server and acted upon by a Controller.
constexpr auto OP_TIME_CODE = 0x9700; //This is an ArtTimeCode packet. It is used to transport time code over the network.
constexpr auto OP_TIME_SYNC = 0x9800; //Used to synchronise real time date and clock.
constexpr auto OP_TRIGGER = 0x9900; //Used to send trigger macros.
constexpr auto OP_DIRECTORY = 0x9a00; //Requests a node's file list.
constexpr auto OP_DIRECTORY_REPLY = 0x9b00; //Replies to OpDirectory with file list.
#pragma endregion

#pragma region node_report_codes
constexpr auto RC_DEBUG = 0x0000; //Booted in debug mode (Only used in development)
constexpr auto RC_POWER_OK = 0x0001; //Power On Tests successful
constexpr auto RC_POWER_FAIL = 0x0002; //Hardware tests failed at Power On
constexpr auto RC_SOCKET_WR_1 = 0x0003; //Last UDP from Node failed due to truncated length, Most likely caused by a collision.
constexpr auto RC_PARSE_FAIL = 0x0004; //Unable to identify last UDP transmission. Check OpCode and packet length.
constexpr auto RC_UDP_FAIL = 0x0005; //Unable to open Udp Socket in last transmission attempt
constexpr auto RC_SH_NAME_OK = 0x0006; //Confirms that Short Name programming via ArtAddress, was successful.
constexpr auto RC_LO_NAME_OK = 0x0007; //Confirms that Long Name programming via ArtAddress, was successful.
constexpr auto RC_DMX_ERROR = 0x0008; //DMX512 receive errors detected.
constexpr auto RC_DMX_UDP_FULL = 0x0009; //Ran out of internal DMX transmit buffers.
constexpr auto RC_DMX_RX_FULL = 0x000a; //Ran out of internal DMX Rx buffers.
constexpr auto RC_SWITCH_ERR = 0x000b; //Rx Universe switches conflict.
constexpr auto RC_CONFIG_ERR = 0x000c; //Product configuration does not match firmware.
constexpr auto RC_DMX_SHORT = 0x000d; //DMX output short detected. See GoodOutput field.
constexpr auto RC_FIRMWARE_FAIL = 0x000e; //Last attempt to upload new firmware failed.
constexpr auto RC_USER_FAIL = 0x000f; //User changed switch settings when address locked by remote programming. User changes ignored.
constexpr auto RC_FACTORY_RES = 0x0010; //Factory reset has occurred.
#pragma endregion

#pragma region style_codes
constexpr auto ST_NODE = 0x00; //A DMX to / from Art-Net device.
constexpr auto ST_CONTROLLER = 0x01; //A lighting console.
constexpr auto ST_MEDIA = 0x02; //A Media Server.
constexpr auto ST_ROUTE = 0x03; //A network routing device.
constexpr auto ST_BACKUP = 0x04; //A backup device.
constexpr auto ST_CONFIG = 0x05; //A configuration or diagnostic tool.
constexpr auto ST_VISUAL = 0x06; //A visualiser.
#pragma endregion

#pragma region bit_definitions
constexpr auto TALK_TO_ME_DISABLE_VLC_TRANSMISSION = 0b00010000;
constexpr auto TALK_TO_ME_ENABLE_VLC_TRANSMISSION_MASK = 0b11101111;
constexpr auto TALK_TO_ME_ENABLE_VLC_TRANSMISSION = 0b00000000;
constexpr auto TALK_TO_ME_DIAGNOSTIC_BROADCAST = 0b00000000;
constexpr auto TALK_TO_ME_DIAGNOSTIC_UNICAST = 0b00001000;
constexpr auto TALK_TO_ME_SEND_ME_DIAGNOSTICS = 0b00000100;
constexpr auto TALK_TO_ME_DONT_SEND_ME_DIAGNOSTICS = 0b00000000;
constexpr auto TALK_TO_ME_ONLY_SEND_POLL_RESPONSES = 0b00000000;
constexpr auto TALK_TO_ME_SEND_RESPONSE_ON_CONDITIONS_CHANGE = 0b00000010;

constexpr auto ART_NET_PORT_NUMBER = 0x1936;

constexpr auto STATUS_INDICATORS_UNKNOWN = 0b00000000;
constexpr auto STATUS_INDICATORS_LOCATE = 0b01000000;
constexpr auto STATUS_INDICATORS_IDENTIFY = 0b01000000;
constexpr auto STATUS_INDICATORS_MUTE = 0b10000000;
constexpr auto STATUS_INDICATORS_NORMAL = 0b11000000;
constexpr auto STATUS_PORT_AUTHORITY_UNKNOWN = 0b00000000;
constexpr auto STATUS_PORT_ADRESS_FRONT_PANEL = 0b00010000;
constexpr auto STATUS_PORT_ADRESS_NETWORK = 0b00100000;
constexpr auto STATUS_FIRMWARE_INDICATORS_NORMAL = 0b00000000;
constexpr auto STATUS_FIRMWARE_BOOT = 0b00000000;
constexpr auto STATUS_FLASH_BOOT = 0b00000000;
constexpr auto STATUS_ROM_BOOT = 0b00000100;
constexpr auto STATUS_RDM_CAPABLE = 0b00000010;
constexpr auto STATUS_NOT_RDM_CAPABLE = 0b00000000;
constexpr auto STATUS_UBEA_PRESENT = 0b00000001;
constexpr auto STATUS_UBEA_CORRUPT = 0b00000000;
constexpr auto STATUS_UBEA_NOT_PRESENT = 0b00000000;

constexpr auto STATUS2_NODE_SUPPORTS_RDM = 0b10000000;
constexpr auto STATUS2_NODE_SUPPORTS_OUTPUT_STYLE_SWITCHING = 0b01000000;
constexpr auto STATUS2_NODE_SQUAWKING = 0b00100000;
constexpr auto STATUS2_NODE_SUPPORTS_S_ACN_AND_ART_NET = 0b00010000;
constexpr auto STATUS2_NODE_SUPPORTS_ART_NET_2 = 0b000000000;
constexpr auto STATUS2_NODE_SUPPORTS_ART_NET_3_OR_4 = 0b000001000;
constexpr auto STATUS2_NODE_SUPPORTS_DHCP = 0b000000100;
constexpr auto STATUS2_NODE_IS_DHCP_CONFIG = 0b000000010;
constexpr auto STATUS2_NODE_SUPPORTS_WEB_CONFIG = 0b000000001;

constexpr auto STATUS3_FAIL_OVER_HOLD_LAST = 0b00000000;
constexpr auto STATUS3_FAIL_OVER_OUTPUTS_ZERO = 0b01000000;
constexpr auto STATUS3_FAIL_OVER_OUTPUTS_FULL = 0b10000000;
constexpr auto STATUS3_FAIL_OVER_PLAYBACK_SCENE = 0b11000000;
constexpr auto STATUS3_FAIL_OVER_SUPPORTED = 0b00100000;
constexpr auto STATUS3_FAIL_OVER_NOT_SUPPORTED = 0b00000000;

constexpr auto IP_PROG_REPLY_STATUS_DHCP_ENABLED = 0b01000000;

constexpr auto PORT_TYPE_ART_NET_OUTPUT = 0b10000000; //if the port can output from art net
constexpr auto PORT_TYPE_ART_NET_INPUT = 0b01000000; //if the port can input into art net
constexpr auto PORT_TYPE_DMX512 = 0b00000000;
constexpr auto PORT_TYPE_MIDI = 0b00000001;
constexpr auto PORT_TYPE_AVAB = 0b00000010;
constexpr auto PORT_TYPE_COLORTRAN_CMX = 0b00000011;
constexpr auto PORT_TYPE_ADB_62_5 = 0b00000100;
constexpr auto PORT_TYPE_ART_NET = 0b00000101;

constexpr auto GOOD_INPUT_DATA_RECEIVED = 0b10000000;
constexpr auto GOOD_INPUT_DMX512_TEST_PACKET = 0b01000000;
constexpr auto GOOD_INPUT_DMX512_SIP_PACKET = 0b00100000;
constexpr auto GOOD_INPUT_DMX512_TEXT_PACKET = 0b00010000;
constexpr auto GOOD_INPUT_INPUT_IS_DISABLED = 0b00001000;
constexpr auto GOOD_INPUT_RECEIVE_ERRORS = 0b00000100;

constexpr auto GOOD_OUTPUT_DATA_IN_TRANSMIT = 0b10000000;
constexpr auto GOOD_OUTPUT_DMX512_TEST_PACKET = 0b01000000;
constexpr auto GOOD_OUTPUT_DMX512_SIP_PACKET = 0b00100000;
constexpr auto GOOD_OUTPUT_DMX512_TEXT_PACKET = 0b00010000;
constexpr auto GOOD_OUTPUT_IS_MERGING_ART_NET = 0b00001000;
constexpr auto GOOD_OUTPUT_DMX_SHORT_ON_POWER_SETUP = 0b00000100;
constexpr auto GOOD_OUTPUT_MERGE_MODE_LTP = 0b00000010;
constexpr auto GOOD_OUTPUT_OUTPUT_TRANSMIT_S_ACN = 0b00000001;
constexpr auto GOOD_OUTPUT_OUTPUT_TRANSMIT_ART_NET = 0b00000000;

constexpr auto GOOD_OUTPUT_B_RDM_DISABLED = 0b10000000;
constexpr auto GOOD_OUTPUT_B_RDM_ENABLED = 0b00000000;
constexpr auto GOOD_OUTPUT_B_OUT_STYLE_CONTINUOUS = 0b01000000;
constexpr auto GOOD_OUTPUT_B_OUT_STYLE_DELTA = 0b00000000;

constexpr auto ADRESS_COMMAND_AC_NONE = 0x00;
constexpr auto ADRESS_COMMAND_AC_CANCEL_MERGE = 0x01;
constexpr auto ADRESS_COMMAND_AC_LED_NORMAL = 0x02;
constexpr auto ADRESS_COMMAND_AC_LED_MUTE = 0x03;
constexpr auto ADRESS_COMMAND_AC_LED_LOCATE = 0x04;
constexpr auto ADRESS_COMMAND_AC_RESET_RX_FLAGS = 0x05;
constexpr auto ADRESS_COMMAND_AC_FAIL_HOLD = 0x08;
constexpr auto ADRESS_COMMAND_AC_FAIL_ZERO = 0x09;
constexpr auto ADRESS_COMMAND_AC_FAIL_FULL = 0x0a;
constexpr auto ADRESS_COMMAND_AC_FAIL_SCENE = 0x0b;
constexpr auto ADRESS_COMMAND_AC_FAIL_RECORD = 0x0c;
constexpr auto ADRESS_COMMAND_AC_MERGE_LTP_0 = 0x10;
constexpr auto ADRESS_COMMAND_AC_MERGE_LTP_1 = 0x11;
constexpr auto ADRESS_COMMAND_AC_MERGE_LTP_2 = 0x12;
constexpr auto ADRESS_COMMAND_AC_MERGE_LTP_3 = 0x13;
constexpr auto ADRESS_COMMAND_AC_MERGE_HTP_0 = 0x50;
constexpr auto ADRESS_COMMAND_AC_MERGE_HTP_1 = 0x51;
constexpr auto ADRESS_COMMAND_AC_MERGE_HTP_2 = 0x52;
constexpr auto ADRESS_COMMAND_AC_MERGE_HTP_3 = 0x53;
constexpr auto ADRESS_COMMAND_AC_ART_NET_SEL_0 = 0x60;
constexpr auto ADRESS_COMMAND_AC_ART_NET_SEL_1 = 0x61;
constexpr auto ADRESS_COMMAND_AC_ART_NET_SEL_2 = 0x62;
constexpr auto ADRESS_COMMAND_AC_ART_NET_SEL_3 = 0x63;
constexpr auto ADRESS_COMMAND_AC_S_ACN_SEL_0 = 0x70;
constexpr auto ADRESS_COMMAND_AC_S_ACN_SEL_1 = 0x71;
constexpr auto ADRESS_COMMAND_AC_S_ACN_SEL_2 = 0x72;
constexpr auto ADRESS_COMMAND_AC_S_ACN_SEL_3 = 0x73;
constexpr auto ADRESS_COMMAND_AC_CLEAR_OP_0 = 0x90;
constexpr auto ADRESS_COMMAND_AC_CLEAR_OP_1 = 0x91;
constexpr auto ADRESS_COMMAND_AC_CLEAR_OP_2 = 0x92;
constexpr auto ADRESS_COMMAND_AC_CLEAR_OP_3 = 0x93;
constexpr auto ADRESS_COMMAND_AC_STYLE_DELTA_0 = 0xa0;
constexpr auto ADRESS_COMMAND_AC_STYLE_DELTA_1 = 0xa1;
constexpr auto ADRESS_COMMAND_AC_STYLE_DELTA_2 = 0xa2;
constexpr auto ADRESS_COMMAND_AC_STYLE_DELTA_3 = 0xa3;
constexpr auto ADRESS_COMMAND_AC_STYLE_CONST_0 = 0xb0;
constexpr auto ADRESS_COMMAND_AC_STYLE_CONST_1 = 0xb1;
constexpr auto ADRESS_COMMAND_AC_STYLE_CONST_2 = 0xb2;
constexpr auto ADRESS_COMMAND_AC_STYLE_CONST_3 = 0xb3;
constexpr auto ADRESS_COMMAND_AC_RDM_ENABLE_0 = 0xc0;
constexpr auto ADRESS_COMMAND_AC_RDM_ENABLE_1 = 0xc1;
constexpr auto ADRESS_COMMAND_AC_RDM_ENABLE_2 = 0xc2;
constexpr auto ADRESS_COMMAND_AC_RDM_ENABLE_3 = 0xc3;
constexpr auto ADRESS_COMMAND_AC_RDM_DISABLE_0 = 0xd0;
constexpr auto ADRESS_COMMAND_AC_RDM_DISABLE_1 = 0xd1;
constexpr auto ADRESS_COMMAND_AC_RDM_DISABLE_2 = 0xd2;
constexpr auto ADRESS_COMMAND_AC_RDM_DISABLE_3 = 0xd3;

constexpr auto DIAG_DATA_PRIORITY_DP_LOW = 0x10;
constexpr auto DIAG_DATA_PRIORITY_DP_MID = 0x40;
constexpr auto DIAG_DATA_PRIORITY_DP_HIGH = 0x80;
constexpr auto DIAG_DATA_PRIORITY_DP_CRITICAL = 0xe0;
constexpr auto DIAG_DATA_PRIORITY_DP_VOLATILE = 0xf0;

constexpr auto TIME_CODE_TYPE_FILM = 0; //24fps
constexpr auto TIME_CODE_TYPE_EBU = 1; //25fps
constexpr auto TIME_CODE_TYPE_DF = 2; //29.97fps
constexpr auto TIME_CODE_TYPE_SMPTE = 3; //30fps

constexpr auto TRIGGER_KEY_ASCII = 0;
constexpr auto TRIGGER_KEY_MACRO = 0;
constexpr auto TRIGGER_KEY_SOFT = 0;
constexpr auto TRIGGER_KEY_SHOW = 0;

constexpr auto VLC_FLAGS_IEEE = 0b10000000;
constexpr auto VLC_FLAGS_REPLY = 0b01000000;
constexpr auto VLC_FLAGS_BEACON = 0b00100000;

constexpr auto INPUT_DISABLE = 0b00000001;
constexpr auto INPUT_ENABLE = 0b00000000;

constexpr auto FIRMWARE_MASTER_TYPE_FIRM_FIRST = 0x00;
constexpr auto FIRMWARE_MASTER_TYPE_FIRM_CONT = 0x01;
constexpr auto FIRMWARE_MASTER_TYPE_FIRM_LAST = 0x02;
constexpr auto FIRMWARE_MASTER_TYPE_UBEA_FIRST = 0x03;
constexpr auto FIRMWARE_MASTER_TYPE_UBEA_CONT = 0x04;
constexpr auto FIRMWARE_MASTER_TYPE_UBEA_LAST = 0x05;

constexpr auto FIRMWARE_REPLY_FIRM_BLOCK_GOOD = 0x00;
constexpr auto FIRMWARE_REPLY_FIRM_ALL_GOOD = 0x01;
constexpr auto FIRMWARE_REPLY_FIRM_FAIL = 0xff;
#pragma endregion

constexpr auto CURRENT_ART_NET_VERSION = 14;


#endif // !ART-NET-CODES_H