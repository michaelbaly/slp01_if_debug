#include <stdio.h>
#include "if_server.h"
#include "cmd_type.h"

/* command process arch */

/* begin: cmd register */
#define TOTAL_CMD_NUM	34
/* end */

#define TRUE	1
#define FALSE	0

typedef unsigned char bool;

typedef bool (*cmd_set_func)(char *arg_list);
typedef bool (*cmd_get_func)(char *arg_list);


typedef struct cmd_pro_arch_s {

	char* cmd_code;
	cmd_set_func cmd_set_f;
	cmd_get_func cmd_get_f;

}CMD_PRO_ARCH_T;

void apn_set(char *arg_list)
{
	char* arg_apn = arg_list;
	strncpy(g_apn, arg_apn, strlen(arg_apn));
}

void apn_query()
{
	return g_apn;
}

void server_set()
{

}

void server_query()
{

}

static CMD_PRO_ARCH_T cmd_pro_reg[TOTAL_CMD_NUM] = {

	/* APN */
	{.cmd_code = "APN",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "SERVER", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "NOMOVE",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "INTERVAL", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "CONFIG",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "SPEEDALARM", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "PROTOCOL",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "VERSION", .cmd_set_f = NULL, .cmd_get_f = server_query},
	{.cmd_code = "PASSWORD",.cmd_set_f = apn_set,.cmd_get_f = NULL },
	{.cmd_code = "GPS", .cmd_set_f = server_set, .cmd_get_f = NULL},
	{.cmd_code = "MILEAGE",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "RESENDINTERVAL", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "PDNTYPE",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "FACTORYRESET", .cmd_set_f = server_set, .cmd_get_f = NULL},
	{.cmd_code = "OTASTART",.cmd_set_f = apn_set,.cmd_get_f = NULL },
	{.cmd_code = "GETADC", .cmd_set_f = NULL, .cmd_get_f = server_query},
	{.cmd_code = "REPORT",.cmd_set_f = NULL,.cmd_get_f = apn_query },
	{.cmd_code = "HEARTBEAT", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "GEOFENCE",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "OUTPUT", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "HEADING",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "IDLINGALERT", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "HARSHBRAKING",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "HARSHACCEL", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "HARSHIMPACT",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "HARSHSWERVE", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "LOWINBATT",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "LOWEXBATT", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "VIRTUALIGNITION",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "CLEARBUFFER", .cmd_set_f = server_set, .cmd_get_f = NULL},
	{.cmd_code = "THEFTMODE",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "TOWALARM", .cmd_set_f = server_set, .cmd_get_f = server_query},
	{.cmd_code = "WATCHDOG",.cmd_set_f = apn_set,.cmd_get_f = apn_query },
	{.cmd_code = "REBOOT", .cmd_set_f = server_set, .cmd_get_f = server_query},

};

bool cmd_match(char* cmd_code, unsigned char *index)
{
	int i = 0;
	for (; i < TOTAL_CMD_NUM; ++i)
	{
		if (!strncmp(cmd_code, cmd_pro_reg[i].cmd_code))
		{
			*index = i;
			return TRUE;
		}
	}

	return FALSE;
}