#pragma once


/* begin: cmd register */
#define TOTAL_CMD_NUM	34
/* end */

#define TRUE	1
#define FALSE	0

typedef unsigned char bool;
typedef char(*p_arg)[MAX_ARG_LEN];


typedef bool (*cmd_set_func)(p_arg arg_list, uint8 arg_cnt);
typedef bool (*cmd_get_func)(void* cmd_rel_s);


typedef struct cmd_pro_arch_s {

	char* cmd_code;
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

struct apn_info_with_type {
	char apn[MAX_ARG_LEN];
	char apn_usrname[MAX_ARG_LEN];
	char apn_passwd[MAX_ARG_LEN];
	struct apn_info_with_type * data_type;
}apn_info_t;

typedef struct apn_info_with_type APN_INFO_T;