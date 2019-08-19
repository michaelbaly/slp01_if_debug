#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "if_server.h"
#include "err_code.h"
#include "cmd_type.h"



const char cmd_set[] = "APN,000000,iot.nb,michael,138114#";
const char cmd_query[] = "APN,000000?";

#define SYS_DEFAULT_PASSWD	"123456"
#define SYS_PASSWD_MAX_LEN	6

#define APN_MAX_LEN		MAX_ARG_NUM

char g_apn[MAX_ARG_LEN] = {0};
char g_apn_usrname[MAX_ARG_LEN] = {0};
char a_apn_passwd[MAX_ARG_LEN] = {0};

char g_sys_passwd[SYS_PASSWD_MAX_LEN+1] = SYS_DEFAULT_PASSWD;
extern cmd_pro_reg;

typedef struct apn_cmd_fmt_s {

	char cmd_code[MAX_ARG_LEN];
	char passwd[MAX_ARG_LEN];
	char apn_name[MAX_ARG_LEN];
	char usr_name[MAX_ARG_LEN];
	char usr_passwd[MAX_ARG_LEN];

}APN_CMD_FMT;

#define ACK_PRE_LEN		4
#define MAX_IMEI_LEN	20
#define MAX_DEV_LEN		10
#define MAX_ST_LEN		15

#define ACK_PREFIX		"+ACK"
#define RESP_PREFIX		"+RESP"
#define BUFF_PREFIX		"+BUFF"
#define SACK_PREFIX		"+SACK"
#define ACK_SET_LEN_MAX		256

char ack_buffer[ACK_SET_LEN_MAX];

/* common load */
typedef struct com_load_ack
{
	char ack_prefix[ACK_PRE_LEN];
	char cmd[MAX_ARG_LEN];
	char imei[MAX_IMEI_LEN];
	char dev_name[MAX_DEV_LEN];
	uint8 status;		//status of set method
	char send_time[MAX_ST_LEN];
}COMMON_LOAD;

//+ACK:APN,<IMEI>,<device_name>,<status>,<send_time>#
typedef struct apn_ack_set
{
	char ack_prefix[ACK_PRE_LEN];
	char cmd[MAX_ARG_LEN];
	char imei[MAX_IMEI_LEN];
	char dev_name[MAX_DEV_LEN];
	uint8 status;		//status of set method
	char send_time[MAX_ST_LEN];
}APN_PACKET_S;

//+ACK:APN,<IMEI>,<device_name>,<status>,<send_time>,<apn>,<username>,<password>#
typedef struct apn_ack_query
{
	COMMON_LOAD com_load;
	char apn[MAX_ARG_LEN];
	char apn_usrname[MAX_ARG_LEN];
	char apn_passwd[MAX_ARG_LEN];
}APN_PACKET_Q;

//+ACK:SERVER,<IMEI>,<device_name>,<status>,<send_time>,<main_ip>,<main_port>,<backup_ip>,<backup_port>#
typedef struct server_ack_query
{
	COMMON_LOAD com_load;
	char main_ip[MAX_ARG_LEN];
	char main_port[MAX_ARG_LEN];
	char backup_ip[MAX_ARG_LEN];
	char backup_port[MAX_ARG_LEN];
}SERVER_PACKET_Q;

//+ACK:NOMOVE,<IMEI>,<device_name>,<status>,<send_time>,<minute>#
typedef struct nomove_ack_query
{
	COMMON_LOAD com_load;
	char minute[MAX_ARG_LEN];
}NOMOVE_PACKET_Q;

//+ACK:INTERVAL,<IMEI>,<device_name>,<status>,<send_time>,<second>#
typedef struct intval_ack_query
{
	COMMON_LOAD com_load;
	char second[MAX_ARG_LEN];
}INTVAL_PACKET_Q;

//+ACK:SPEEDALARM,<IMEI>,<device_name>,<status>,<send_time>,<threshold>#
typedef struct salarm_ack_query
{
	COMMON_LOAD com_load;
	char thd[MAX_ARG_LEN];
}SALARM_PACKET_Q;

//+ACK:PROTOCOL,<IMEI>,<device_name>,<status>,<send_time>,<UDP/TCP>,<ACK>#
typedef struct prot_ack_query
{
	COMMON_LOAD com_load;
	char proto[MAX_ARG_LEN];
	char ack_idc[];
}PROT_PACKET_Q;

//+ACK:VERSION,<IMEI>,<device_name>,<status>,<send_time>,<version>#
typedef struct ver_ack_query
{
	COMMON_LOAD com_load;
	char ver[MAX_ARG_LEN];
}VER_PACKET_Q;

//+ACK:MILEAGE,<IMEI>,<device_name>,<status>,<send_time>,<mileage>#
typedef struct mile_ack_query
{
	COMMON_LOAD com_load;
	char mile[MAX_ARG_LEN];
}MILE_PACKET_Q;

//+ACK:RESENDINTERVAL,<IMEI>,<device_name>,<status>,<send_time>,<resend_interval>#
typedef struct rsend_ack_query
{
	COMMON_LOAD com_load;
	char rsd_int[MAX_ARG_LEN];
}RSD_PACKET_Q;

//+ACK:PDNTYPE,<IMEI>,<device_name>,<status>,<send_time>,<PDN_type>#
typedef struct pdn_ack_query
{
	COMMON_LOAD com_load;
	char pdn_t[MAX_ARG_LEN];
}PDN_PACKET_Q;

//+ACK:GETADC,<IMEI>,<device_name>,<status>,<send_time>,<power>,<battery>,<external>#
typedef struct adc_ack_query
{
	COMMON_LOAD com_load;
	char power[MAX_ARG_LEN];
	char batt[MAX_ARG_LEN];
	char ext_batt[MAX_ARG_LEN];
}GADC_PACKET_Q;

//+ACK:HEARTBEAT,<IMEI>,<device_name>,<status>,<send_time>,<minute>#
typedef struct adc_ack_query
{
	COMMON_LOAD com_load;
	char min[MAX_ARG_LEN];
}GADC_PACKET_Q;

//+ACK:OUTPUT,<IMEI>,<device_name>,<status>,<send_time>,<index>,<level>#
typedef struct d_out_ack_query
{
	COMMON_LOAD com_load;
	char d_out[MAX_ARG_LEN];
}DOUT_PACKET_Q;

//+ACK:LOWINBATT,<IMEI>,<device_name>,<status>,<send_time>,<threshold>#
typedef struct batt_ack_query
{
	COMMON_LOAD com_load;
	union {
		char in_thd[MAX_ARG_LEN];
		char ex_thd[MAX_ARG_LEN];
	}batt_thd;
}BATT_PACKET_Q;

//+ACK:THEFTMODE,<IMEI>,<device_name>,<status>,<send_time>,<enable/disable>,<report_interval>,<total_interval>#
#define SEC_LEN 2
#define DEF_H_LEN 2
typedef struct t_mod_ack_query
{
	COMMON_LOAD com_load;
	char en_flag;
	char rep_int[SEC_LEN];
	char tot_int[DEF_H_LEN];
}TMOD_PACKET_Q;

//+ACK:WATCHDOG,<IMEI>,<device_name>,<status>,<send_time>,<enable/disable>,<day>#
#define DEF_D_LEN 2
typedef struct wdog_ack_query
{
	COMMON_LOAD com_load;
	char en_flag;
	char day[DEF_D_LEN];
}WDOG_PACKET_Q;




/* build the packet based on cmd and cmd type */
void build_ack(uint8 cmd_index, bool cmd_type, bool status)
{
	/* cmd_type(set:1;query:0) */
	//+ACK:APN,<IMEI>,<device_name>,<status>,<send_time>#
	//strcpy(com_ack.ack_prefix,);
	memset(ack_buffer, '\0', sizeof(ack_buffer));
	strncpy(ack_buffer, ACK_PREFIX, ACK_PRE_LEN);
	strcat(ack_buffer + ACK_PRE_LEN, ":");
	strcat(ack_buffer + ACK_PRE_LEN, cmd_pro_reg[cmd_index].cmd_code);//arg_list[0] = APN or cmd_pro_reg[index].cmd_code
	//get imei by using api via the atc pipe

	//get device name

	//get status from execute result in switch case
	if (status)
	{
		//cat "OK" with ack_buffer
	}
	else
	{
		//cat "ERROR" with ack_buffer
	}

	//get current time and cat with ack_buffer

	/* if cmd_type is query */
	if (!cmd_type)
	{
		//cat each paras with ack_buffer
	}

	/* send ack to server through socket */
	send_packet();
}

/* enqueue the packet */
void send_packet(sockfd, packet)
{

}

/* show apn info */
void apn_info_show()
{
	printf("the apn info:\n");
	printf("g_apn:%s\n", g_apn);
	printf("g_apn_usrname:%s\n", g_apn_usrname);
	printf("g_apn_usrname:%s\n", g_apn_usrname);

	return;
}


int main()
{
	uint8 arg_cnt = 0;
	uint8 status = 0xff;
	int i = 0;
	uint8 index = 0xff;
	char arg_list[MAX_ARG_NUM][MAX_ARG_LEN] = { 0 };
	CMD_TYPE_E cmd_type = 0xff;
	COMMON_LOAD com_ack;

	char* arg_each = &arg_list[0];


	memset(arg_list, 0, sizeof(arg_list));
	arg_cnt = para_cmd_str(cmd_set, arg_list, &cmd_type);

	printf("cmd_type: %d\n", cmd_type);
	printf("arg_cnt: %d\n", arg_cnt);

	for (; i < arg_cnt; i++)
	{
		printf("arg_list[arg_cnt]: %s\n", *(arg_list + i));
	}

	/* compound each arg for different use */

	/* return if password is invalid */
	if (!cmd_match(arg_list[0], index) && strncmp(g_sys_passwd, arg_list[1], SYS_PASSWD_MAX_LEN))
	{
		printf("error cmd or password!\n");
		return ERROR_CMD_PWD_E;
	}

	/* continue the flow */
	switch (cmd_type)
	{
		case QUERY_CMD_E:
			/* execute the registered query function */
			status = cmd_pro_reg[index].cmd_get_f(arg_each);
			break;

		case SET_CMD_E:
			/* execute the registered set function */
			status = cmd_pro_reg[index].cmd_set_f(arg_each);
			break;

		default:
		{
			printf("unknown command type\n");
			break;
		}

	}

	/* apn info */
	apn_info_show();

	/* build apn set ack */
	




	return 0;

}