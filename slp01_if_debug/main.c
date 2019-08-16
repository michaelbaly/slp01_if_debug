#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "if_server.h"
#include "err_code.h"


const char cmd[] = "APN,000000,iot.nb,abc,def#";
const char cmd1[] = "APN,000000?";

#define SYS_DEFAULT_PASSWD	"123456"
#define SYS_PASSWD_MAX_LEN	6

#define APN_MAX_LEN		MAX_ARG_NUM

char g_apn[APN_MAX_LEN] = {0};

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

#define ACK_PREFIX		"+ACK"
#define RESP_PREFIX		"+RESP"
#define BUFF_PREFIX		"+BUFF"
#define SACK_PREFIX		"+SACK"

//+ACK:APN,<IMEI>,<device_name>,<status>,<send_time>#
typedef struct apn_package_s {

	char ack_prefix[ACK_PRE_LEN];
	char imei[];
	

}APN_ACK_P;



int main()
{
	uint8 arg_cnt = 0;
	int i = 0;
	uint8 index = 0xff;
	char arg_list[MAX_ARG_NUM][MAX_ARG_LEN] = { 0 };
	CMD_TYPE_E cmd_type = 0xff;


	memset(arg_list, 0, sizeof(arg_list));
	arg_cnt = para_cmd_str(cmd, arg_list, &cmd_type);

	printf("cmd_type: %d\n", cmd_type);
	printf("arg_cnt: %d\n", arg_cnt);

	for (; i < arg_cnt; i++)
	{
		printf("arg_list[arg_cnt]: %s\n", *(arg_list + i));
	}

	/* compond each arg for different use */

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
			cmd_pro_reg[index].cmd_get_f(arg_list);
			break;

		case SET_CMD_E:
			/* execute the registered set function */
			cmd_pro_reg[index].cmd_set_f();
			break;

		default:
		{
			printf("unknown command type\n");
			break;
		}

	}

	





	return 0;

}