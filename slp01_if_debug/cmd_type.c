#include <stdio.h>
#include "if_server.h"
#include "cmd_type.h"
#include "common.h"

/* command process arch */





/* this contains apn/username/password */
APN_INFO apn_info = { {0} };
APN_INFO apn_data = { {0} };

ADC_INFO adc_info = { {0} };


void apn_info_init(APN_INFO *apn_data)
{
	strncpy(apn_data->apn, DFT_APN, strlen(DFT_APN));
	strncpy(apn_data->apn_usrname, DFT_APN_USRNAME, strlen(DFT_APN_USRNAME));
	strncpy(apn_data->apn_passwd, DFT_APN_PASSWD, strlen(DFT_APN_PASSWD));

}

bool apn_set(p_arg arg_each, uint8 arg_cnt)
{
	/* apn offset */
	p_arg arg_list = arg_each + ACTUAL_ARG_OFFSET;

	/* clear apn info */
	memset(&apn_info, 0, sizeof(apn_info));

	strncpy(apn_info.apn, arg_list, strlen(arg_list));
	if (strncmp(apn_info.apn, arg_list, strlen(arg_list)))
	{
		printf("g_apn:%s\n", apn_info.apn);
		return FALSE;
	}

	/* if username and password specified */
	if (arg_cnt == ACTUAL_ARG_OFFSET + 3)
	{
		arg_list++;
		strncpy(apn_info.apn_usrname, arg_list, strlen(arg_list));
		if (strncmp(apn_info.apn_usrname, arg_list, strlen(arg_list)))
		{
			printf("apn_usrname:%s\n", apn_info.apn_usrname);
			return FALSE;
		}

		arg_list++;
		strncpy(apn_info.apn_passwd, arg_list, strlen(arg_list));
		if (strncmp(apn_info.apn_passwd, arg_list, strlen(arg_list)))
		{
			printf("apn_passwd:%s\n", apn_info.apn_passwd);
			return FALSE;
		}

	}

	return TRUE;
}

bool apn_query(APN_INFO *apn_data)
{
	APN_INFO* apn_tmp = apn_data;

	/* apn info valid ? */
	if (!strlen(apn_info.apn) || (!strlen(apn_info.apn_usrname) && !strlen(apn_info.apn_passwd)))
	{
		/* apn info invalid */
		return FALSE;
	}

	/* fill mem of apn_data */
	strncpy(apn_tmp->apn, apn_info.apn, strlen(apn_info.apn));
	strncpy(apn_tmp->apn_usrname, apn_info.apn_usrname, strlen(apn_info.apn_usrname));
	strncpy(apn_tmp->apn_passwd, apn_info.apn_passwd, strlen(apn_info.apn_passwd));


	return TRUE;
}


void server_set()
{

}

void server_query()
{

}

bool getadc(ADC_INFO* adc_data)
{
	ADC_INFO* adc_tmp = adc_data;

	/* get adc data from BLE through the get_adc_ble api */




	/* apn info valid ? */
	if (!strlen(adc_info.power) && !strlen(adc_info.in_batt) && !strlen(adc_info.ex_batt))
	{
		/* apn info invalid */
		return FALSE;
	}

	/* fill mem of apn_data */
	strncpy(adc_tmp->power, adc_info.power, strlen(adc_info.power));
	strncpy(adc_tmp->in_batt, adc_info.in_batt, strlen(adc_info.in_batt));
	strncpy(adc_tmp->ex_batt, adc_info.ex_batt, strlen(adc_info.ex_batt));


	return TRUE;
}

CMD_PRO_ARCH_T cmd_pro_reg[TOTAL_CMD_NUM] = {

	/* APN */
	{.cmd_code = "APN", .cmd_rel_st = (void*)&apn_data, .ele_num = APN_ELE_NUM, .cmd_set_f = apn_set, .cmd_get_f = apn_query },
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
	{.cmd_code = "GETADC", .cmd_set_f = NULL, .cmd_get_f = getadc},
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