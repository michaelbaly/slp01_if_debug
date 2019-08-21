#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "if_server.h"
#include "err_code.h"
#include "cmd_type.h"
#include "common.h"



extern APN_INFO apn_info;
extern CMD_PRO_ARCH_T cmd_pro_reg[];

const char cmd_set[] = "APN,123456,iot.nb,michael,138114#";
const char cmd_query[] = "APN,123456?";

static char g_sys_passwd[SYS_PASSWD_MAX_LEN+1] = SYS_DEFAULT_PASSWD;
//extern cmd_pro_reg;
static char ack_buffer[ACK_SET_LEN_MAX] = {0};

char g_imei_buf[MAX_IMEI_LEN] = { 0 };
char g_dev_name[MAX_DEV_LEN] = DFT_DEV_NAME;
char g_real_time[MAX_RT_LEN] = { 0 };

#define UNIT_TEST

#ifndef ATEL_DEBUG
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
typedef struct hb_ack_query
{
	COMMON_LOAD com_load;
	char min[MAX_ARG_LEN];
}HB_PACKET_Q;

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

#endif


/* obtain IMEI info through api */
char* atel_get_imei()
{

	/* return the addr which contains imei info */
	//return g_imei_buf;
	return "866425037710391";
	
}

char* atel_get_dname()
{
	//return g_dev_name;
	return DFT_DEV_NAME;
}

char* atel_get_real_time()
{
	//return g_real_time;
	return "20190820171650";
}

/* build the packet based on cmd and cmd type */
void build_ack(uint8 cmd_idx, bool cmd_type, bool status, void * cmd_rel_s)
{
	char* p_ack = ack_buffer;
	char* p_imei = NULL;
	char* p_dev_name = NULL;
	char* p_real_time = NULL;
	int use_len = 0;

	APN_INFO *cmd_rel_tmp = (APN_INFO*)cmd_rel_s;
	/* cmd_type(set:1;query:0) */
	//+ACK:APN,<IMEI>,<device_name>,<status>,<send_time>#

	memset(ack_buffer, 0, sizeof(ack_buffer));

#ifndef ATEL_DEBUG
	strcat_s(p_ack, ACK_PRE_LEN, ACK_PREFIX);
	p_ack += ACK_PRE_LEN;
	strcat_s(p_ack, 1, ":");
	p_ack += 1;
	strcat_s(p_ack, strlen(cmd_pro_reg[cmd_idx].cmd_code), cmd_pro_reg[cmd_idx].cmd_code);//arg_list[0] = APN or cmd_pro_reg[index].cmd_code
	p_ack += strlen(cmd_pro_reg[cmd_idx].cmd_code);
	strcat_s(p_ack, 1, ",");
	p_ack += 1;
	//get imei by using api via the atc pipe
	p_imei = atel_get_imei();
	strcat_s(p_ack, strlen(p_imei), p_imei);
	p_ack += strlen(p_imei);

	//get device name
	p_dev_name = atel_get_dname();
	strcat_s(p_ack, strlen(p_dev_name), p_dev_name);
	p_ack += strlen(p_dev_name);

	//get status from execute result in switch case
	if (status)
	{
		//cat "OK" with ack_buffer
		strcat_s(p_ack, 2, "OK");
		p_ack += strlen("OK");

	}
	else
	{
		//cat "ERROR" with ack_buffer
		strcat_s(p_ack, 5, "ERROR");
		p_ack += strlen("ERROR");

	}

	//get current time and cat with ack_buffer
	p_real_time = atel_get_real_time();
	strcat_s(p_ack, strlen(p_real_time), p_real_time);
	p_ack += strlen(p_real_time);


	/* if cmd_type is query */
	if (!cmd_type)
	{
		strcat_s(p_ack, 1, ",");
		p_ack += 1;
		//cat each paras with ack_buffer

	}

	/* add ack terminator char */
	strcat_s(p_ack, 1, "#");
#endif

	//compound ack
	p_imei = atel_get_imei();
	p_dev_name = atel_get_dname();
	p_real_time = atel_get_real_time();
	//sprintf_s(ack_buffer, sizeof(ack_buffer), "+ACK:%s,%s,%s,%s,%s%s", cmd_pro_reg[cmd_idx].cmd_code, p_imei, p_dev_name, "OK", p_real_time,"#");
	sprintf_s(ack_buffer, sizeof(ack_buffer), "+ACK:%s,%s,%s,%s", cmd_pro_reg[cmd_idx].cmd_code, p_imei, p_dev_name, p_real_time);
	use_len += strlen(ack_buffer);

	/* attach execution status */
	if (status)
	{
		sprintf_s(ack_buffer + use_len, sizeof(ack_buffer) - use_len, ",%s", EXEC_STATUS_OK);
		use_len += strlen(EXEC_STATUS_OK) + 1;
	}
	else
	{
		sprintf_s(ack_buffer + use_len, sizeof(ack_buffer) - use_len, ",%s", EXEC_STATUS_ERROR);
		use_len += strlen(EXEC_STATUS_ERROR) + 1;
	}

	/* if cmd_type is query */
	if (!cmd_type)
	{
		/* extract each mem from the struct */
		sprintf_s(ack_buffer + use_len, sizeof(ack_buffer) - use_len, ",%s", cmd_rel_tmp->apn);
		use_len += strlen(cmd_rel_tmp->apn) + 1;

		sprintf_s(ack_buffer + use_len, sizeof(ack_buffer) - use_len, ",%s", cmd_rel_tmp->apn_usrname);
		use_len += strlen(cmd_rel_tmp->apn_usrname) + 1;

		sprintf_s(ack_buffer + use_len, sizeof(ack_buffer) - use_len, ",%s", cmd_rel_tmp->apn_passwd);
		use_len += strlen(cmd_rel_tmp->apn_passwd) + 1;

	}
	/* attch terminiter charactor */
	sprintf_s(ack_buffer + use_len, sizeof(ack_buffer) - use_len, "%s", "#");
	use_len += 1;


	printf("cnt of ack_buffer:%s\nthe use_len is:%d\n", ack_buffer, use_len);

	/* send ack to server through socket */
	//send_packet(sfd, ack_buffer);
}

/* enqueue the packet */
void send_packet(sockfd, packet)
{

}

/* show apn info */
void apn_info_show()
{
	printf("the apn info:\n");
	printf("apn:%s\n", apn_info.apn);
	printf("apn_usrname:%s\n", apn_info.apn_usrname);
	printf("apn_passwd:%s\n", apn_info.apn_passwd);

	return;
}


void cmd_rel_data_parse(char *cmd_code, CMD_CODE_E index_e)
{
	/* judge data type */
	switch (index_e)
	{
		case GADC_E:

			break;

		default:
			break;
	}

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
	//COMMON_LOAD com_ack;
	//APN_INFO apn_tmp;
	//CMD_PRO_ARCH_T* p_cmd = &cmd_pro_reg[0];

	APN_INFO apn_data = { {0} };

	p_arg arg_each = NULL;


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
	if (!cmd_match(arg_list[0], &index) || strncmp(g_sys_passwd, arg_list[1], SYS_PASSWD_MAX_LEN))
	{
		printf("error cmd or password!\n");
		return ERROR_CMD_PWD_E;
	}

	/* continue the flow */
	switch (cmd_type)
	{
		case QUERY_CMD_E:
			/* execute the registered query function */
			//status = cmd_pro_reg[index].cmd_get_f(&status);
			break;

		case SET_CMD_E:
			/* execute the registered set function */
			arg_each = arg_list[0];
			status = cmd_pro_reg[index].cmd_set_f(arg_each, arg_cnt);
			break;

		default:
		{
			printf("unknown command type\n");
			break;
		}

	}

	/* apn info */
	apn_info_show();

	/* query result test */
#ifdef UNIT_TEST
	memset(arg_list, 0, sizeof(arg_list));
	arg_cnt = para_cmd_str(cmd_query, arg_list, &cmd_type);

	printf("cmd_type: %d\n", cmd_type);
	printf("arg_cnt: %d\n", arg_cnt);

	for (; i < arg_cnt; i++)
	{
		printf("arg_list[arg_cnt]: %s\n", *(arg_list + i));
	}

	/* compound each arg for different use */

	/* return if password is invalid */
	if (!cmd_match(arg_list[0], &index) || strncmp(g_sys_passwd, arg_list[1], SYS_PASSWD_MAX_LEN))
	{
		printf("error cmd or password!\n");
		return ERROR_CMD_PWD_E;
	}

	/* continue the flow */
	switch (cmd_type)
	{
		case QUERY_CMD_E:
			/* execute the registered query function */
			status = cmd_pro_reg[index].cmd_get_f((void*)&apn_data);
			break;

		case SET_CMD_E:
			/* execute the registered set function */
			arg_each = arg_list[0];
			status = cmd_pro_reg[index].cmd_set_f(arg_each, arg_cnt);
			break;

		default:
		{
			printf("unknown command type\n");
			break;
		}

	}

#endif

	/* build ack for server */
	build_ack(index, cmd_type, status, (void*)&apn_data);

	//enqueue the ack
	
	
	return 0;

}