#ifndef ART_NET_STRUCTS_H
#define ART_NET_STRUCTS_H

//############################################################################
//using Art-Net� Designed by and Copyright Artistic Licence Holdings Ltd
//############################################################################


#pragma region packet_structs
struct art_net_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code; //The OpCode defines the class of data following ArtPoll within this UDP packet. Transmitted low byte first.
	uint8_t prot_ver_hi; //High byte of the Art-Net protocol revision number.
	uint8_t prot_ver_lo; //Low byte of the Art-Net protocol revision number. Current value 14. Controllers should ignore communication with nodes using a protocol version lower than 14.
	uint8_t talk_to_me; //See page 14 in the manual
	uint8_t priority; //See priority codes
};

struct art_poll_reply_packet { //manual page 21 - 26
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_POLL_REPLY; //OpPollReply Transmitted low byte first.
	uint8_t ip_address[4]; //Array containing the Node�s IP address. First array entry is most significant byte of address. When binding is implemented, bound nodes may share the root node�s IPAddress and the BindIndex is used to differentiate the nodes.
	uint16_t port;
	uint8_t version_info_h;
	uint8_t version_info_l;
	uint8_t net_switch;
	uint8_t sub_switch;
	uint8_t oem_hi;
	uint8_t oem;
	uint8_t ubea_version;
	uint8_t status_1;
	uint8_t esta_man_lo;
	uint8_t esta_man_hi;
	char short_name[18]; //Null-terminated string of the short name
	char long_name[64]; //Null-terminated string of the long name
	char node_report[64]; //Null-terminated string of textual from a node. formatted as: �#xxxx [yyyy..] zzzzz��xxxx is a hex status code as defined in Table 3. yyyy is a decimal counter that increments every time the Node sends an ArtPollResponse. zzzzz is some Text.
	uint8_t num_ports_hi;
	uint8_t num_ports_lo;
	uint8_t port_types[4]; //This array defines the operation and protocol of each channel.
	uint8_t good_input[4]; //This array defines the status of each input node
	uint8_t good_output[4]; //This array defines the status of each output node
	uint8_t sw_in[4];
	uint8_t sw_out[4];
	uint8_t sw_video;
	uint8_t sw_macro;
	uint8_t sw_remote;
	const uint8_t spare_1 = 0;
	const uint8_t spare_2 = 0;
	const uint8_t spare_3 = 0;
	uint8_t style;
	uint8_t mac_hi;
	uint8_t mac_4;
	uint8_t mac_3;
	uint8_t mac_2;
	uint8_t mac_1;
	uint8_t mac_lo;
	uint8_t bind_ip[4];
	uint8_t bind_index;
	uint8_t status_2;
	uint8_t good_output_b[4];
	uint8_t status_3;
	const uint8_t filler[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
};

struct art_ip_prog_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_IP_PROG; //OpIpProg Transmitted low byte first.
	uint8_t port_ver_hi;
	uint8_t port_ver_lo;
	const uint8_t filler1 = 0;
	const uint8_t filler2 = 0;
	uint8_t command;
	const uint8_t filler3 = 0;
	uint8_t prog_ip_hi;
	uint8_t prog_ip_2;
	uint8_t prog_ip_1;
	uint8_t prog_ip_lo;
	uint8_t prog_sm_hi;
	uint8_t prog_sm_2;
	uint8_t prog_sm_1;
	uint8_t prog_sm_lo;
	uint8_t porg_port_hi; //deprecated
	uint8_t porg_port_lo;
	const uint8_t spare[8] = { 0,0,0,0,0,0,0,0 };
};

struct art_ip_prog_reply_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_IP_PROG_REPLY; //OpIpProgReply Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler[4] = { 0,0,0,0 };
	uint8_t prog_ip_hi;
	uint8_t prog_ip_2;
	uint8_t prog_ip_1;
	uint8_t prog_ip_lo;
	uint8_t prog_sm_hi;
	uint8_t prog_sm_2;
	uint8_t prog_sm_1;
	uint8_t prog_sm_lo;
	uint8_t porg_port_hi; //deprecated
	uint8_t porg_port_lo;
	uint8_t status;
	const uint8_t spare[7] = { 0,0,0,0,0,0,0 };
};

struct art_address_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_ADDRESS; //OpAddress Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t net_switch;
	uint8_t bind_index;
	char short_name[18]; //Null-terminated string of the short name
	char long_name[64]; //Null-terminated string of the long name
	uint8_t sw_in[4];
	uint8_t sw_out[4];
	uint8_t sub_switch;
	uint8_t sw_video;
	uint8_t command;
};

struct art_diag_data_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_DIAG_DATA; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler1 = 0;
	uint8_t priority;
	const uint8_t filler2 = 0;
	const uint8_t filler3 = 0;
	uint8_t length_hi;
	uint8_t length_lo;
	uint8_t data[]; //ascii text, null terminated. Max length 512.
};

struct art_time_code_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_TIME_CODE; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler1 = 0;
	const uint8_t filler2 = 0;
	uint8_t frames; //0-29, depending on mode
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t type;
};

struct art_command_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_COMMAND; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t esta_man_hi;
	uint8_t esta_man_lo;
	uint8_t length_hi;
	uint8_t length_lo;
	uint8_t data[]; /*ASCII text command string, null terminated. Max length is 512 bytes including the null term.
	The Data field contains the command text. The text is ASCII encoded and is null
	terminated and is case insensitive. It is legal, although inefficient, to set the Data array
	size to the maximum of 512 and null pad unused entries.
	The command text may contain multiple commands and adheres to the following syntax:
	Command=Data&
	The ampersand is a break between commands. Also note that the text is capitalised for
	readability; it is case insensitive.
	Thus far, two commands are defined by Art-Net. It is anticipated that additional
	commands will be added as other manufacturers register commands which have
	industry wide relevance.
	These commands shall be transmitted with EstaMan = 0xFFFF.
	Table 6 � ArtCommand Commands:
	The following table details the commands defined for use in ArtCommand.
	Command				Description
	SwoutText			This command is used to re-programme the label associated with the ArtPollReply->Swout fields. Syntax: "SwoutText=Playback&"
	SwinText			This command is used to re-programme the label associated with the ArtPollReply->Swin fields. Syntax: "SwinText=Record&
	*/
};

struct art_trigger_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_TRIGGER; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler1 = 0;
	const uint8_t filler2 = 0;
	uint8_t oem_code_hi;
	uint8_t oem_code_lo;
	uint8_t key;
	uint8_t sub_key;
	uint8_t data[512];
};

/*
ArtDmx packets must be unicast to subscribers of the specific universe contained in the
ArtDmx packet.
The transmitting device must regularly ArtPoll the network to detect any change in
devices which are subscribed. Nodes that are subscribed will list the subscription
universe in the ArtPollReply. Subscribed means any universes listed in either the Swin or
Swout array.
If there are no subscribers to a universe that the transmitter wishes to send, then the
ArtDmx must not be broadcast. If the number of universe subscribers exceeds 40 for a
given universe, the transmitting device may broadcast.

*/
struct art_dmx_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_DMX; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t sequence;
	uint8_t physical;
	uint8_t sub_uni;
	uint8_t net;
	uint8_t length_hi;
	uint8_t length_lo;
	uint8_t data[]; //A variable length array of DMX512 lighting data.
};

struct art_sync_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_SYNC; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t aux1 = 0;
	uint8_t aux2 = 0;
};

struct art_nzs_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_NZS; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t sequence;
	uint8_t start_code; //non zero
	uint8_t sub_uni;
	uint8_t net;
	uint8_t length_hi;
	uint8_t length_lo;
	uint8_t data[]; //A variable length array of DMX512 lighting data
};

struct art_vlc_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_NZS; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t sequence;
	const uint8_t start_code = 0x91;
	uint8_t sub_uni;
	uint8_t net;
	vlc_data vlc; //A variable length array of VLC data
};

struct vlc_data {
	uint8_t length_hi;
	uint8_t length_lo;
	uint8_t man_id_hi = 0x41;
	uint8_t man_id_lo = 0x4C;
	uint8_t sub_code = 0x45;
	uint8_t flags;
	uint8_t trans_hi;
	uint8_t trans_lo;
	uint8_t slot_addr_hi;
	uint8_t slot_addr_lo;
	uint8_t pay_count_hi;
	uint8_t pay_count_lo;
	uint8_t pay_check_hi;
	uint8_t pay_check_lo;
	const uint8_t spare1 = 0;
	uint8_t vlc_depth;
	uint8_t vlc_freq_hi;
	uint8_t vlc_freq_lo;
	uint8_t vlc_mod_hi;
	uint8_t vlc_mod_lo;
	uint8_t pay_lang_hi;
	uint8_t pay_lang_lo;
	uint8_t beac_rep_hi;
	uint8_t beac_rep_lo;
	uint8_t payload[];
};

struct art_input_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_INPUT; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler1 = 0;
	uint8_t bind_index;
	uint8_t num_ports_hi;
	uint8_t num_ports_lo;
	uint8_t input[4]; //set bit 0 to 1 to disable the input
};

struct art_firmware_master_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_FIRMWARE_MASTER; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler1 = 0;
	const uint8_t filler2 = 0;
	uint8_t type;
	uint8_t block_id;
	uint8_t firmware_length_3;
	uint8_t firmware_length_2;
	uint8_t firmware_length_1;
	uint8_t firmware_length_0;
	const uint8_t spare[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	uint8_t data[512];
};

struct art_firmware_reply_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_FIRMWARE_REPLY; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler1 = 0;
	const uint8_t filler2 = 0;
	uint8_t type;
	const uint8_t spare[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
};

struct art_tod_request_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_TOD_REQUEST; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler1 = 0;
	const uint8_t filler2 = 0;
	const uint8_t spare[7] = { 0,0,0,0,0,0,0 };
	uint8_t net;
	uint8_t add_count;
	uint8_t adress[32];
};

struct art_tod_data_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_TOD_DATA; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t rdm_ver;
	uint8_t port; //Physical Port = (BindIndex-1) * ArtPollReply->NumPortsLo + ArtTodData->Port
	const uint8_t spare[6] = { 0,0,0,0,0,0 };
	uint8_t bind_index;
	uint8_t net;
	uint8_t command_response;//either 0x00 (tod full) or 0xff (tod not available)
	uint8_t address;
	uint8_t uid_total_hi;
	uint8_t uid_total_lo;
	uint8_t block_count;
	uint8_t uid_count;//length of tod
	rdm_uid tod[];
};

struct rdm_uid {
	uint16_t manu_id;
	uint32_t id;
};

struct art_tod_control_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_TOD_CONTROL; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	const uint8_t filler1 = 0;
	const uint8_t filler2 = 0;
	const uint8_t spare[7] = { 0,0,0,0,0,0,0 };
	uint8_t net;
	uint8_t command; //0 for none, 1 to tod flush
	uint8_t address;
};

struct art_rdm_packet {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_RDM; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t rdm_ver;
	const uint8_t filler2 = 0;
	const uint8_t spare[7] = { 0,0,0,0,0,0,0 };
	uint8_t net;
	uint8_t command = 0; //0 to process packet
	uint8_t address;
	uint8_t rdm_packet[]; //rdm packet excluding dmx start code
};

struct art_rdm_sub {
	char id[8] = { 'A','r','t','-','N','e','t','\0' };
	uint16_t op_code = OP_RDM_SUB; //OpCode Transmitted low byte first.
	uint8_t prot_ver_hi;
	uint8_t prot_ver_lo;
	uint8_t rdm_ver;
	const uint8_t filler2 = 0;
	rdm_uid uid;
	const uint8_t spare1 = 0;
	uint8_t command_class;
	uint16_t parameter_id;
	uint16_t sub_device;
	uint16_t sub_count;
	const uint8_t spare[4] = { 0,0,0,0 };
	uint16_t data[];
};

#pragma endregion
#endif //ART_NET_STRUCTS_H