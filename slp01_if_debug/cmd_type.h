#pragma once


/* begin: cmd register */
#define TOTAL_CMD_NUM	34
/* end */

#define TRUE	1
#define FALSE	0

typedef unsigned char bool;
typedef char(*p_arg)[MAX_ARG_LEN];


typedef bool (*cmd_set_func)(p_arg arg_list, uint8 arg_cnt);
typedef bool (*cmd_get_func)(void* cmd_rel_st);


typedef struct cmd_pro_arch_s {

	char* cmd_code;
	void* cmd_rel_st;
	uint8 ele_num;
	cmd_set_func cmd_set_f;
	cmd_get_func cmd_get_f;

}CMD_PRO_ARCH_T;

#define ACTUAL_ARG_OFFSET 2
#define CMD_OK		"OK"
#define CMD_ERROR	"ERROR"

typedef struct apn_info_s {
	char apn[MAX_ARG_LEN];
	char apn_usrname[MAX_ARG_LEN];
	char apn_passwd[MAX_ARG_LEN];
}APN_INFO;

#define APN_ELE_NUM		sizeof(APN_INFO)/MAX_ARG_LEN


typedef struct adc_info_s {
	char power[MAX_ARG_LEN];
	char in_batt[MAX_ARG_LEN];
	char ex_batt[MAX_ARG_LEN];
}ADC_INFO;


struct apn_info_with_type {
	char apn[MAX_ARG_LEN];
	char apn_usrname[MAX_ARG_LEN];
	char apn_passwd[MAX_ARG_LEN];
	struct apn_info_with_type *data_type;
}apn_info_t;

typedef struct apn_info_with_type APN_INFO_T;