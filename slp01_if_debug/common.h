#pragma once
#define SYS_DEFAULT_PASSWD	"123456"
#define SYS_PASSWD_MAX_LEN		6
#define DFT_APN				"iot.nb"
#define DFT_APN_USRNAME		"michael"
#define DFT_APN_PASSWD		"138114"
#define DFT_DEV_NAME		"ATEL-100"

#define ACK_PRE_LEN		4
#define MAX_IMEI_LEN	20
#define MAX_DEV_LEN		10
#define MAX_ST_LEN		15
#define MAX_RT_LEN		15


#define ACK_PREFIX		"+ACK"
#define RESP_PREFIX		"+RESP"
#define BUFF_PREFIX		"+BUFF"
#define SACK_PREFIX		"+SACK"
#define ACK_SET_LEN_MAX		256

#define EXEC_STATUS_OK			"OK"
#define EXEC_STATUS_ERROR		"ERROR"


#define APN_MAX_LEN		MAX_ARG_NUM


typedef struct apn_cmd_fmt_s {

	char cmd_code[MAX_ARG_LEN];
	char passwd[MAX_ARG_LEN];
	char apn_name[MAX_ARG_LEN];
	char usr_name[MAX_ARG_LEN];
	char usr_passwd[MAX_ARG_LEN];

}APN_CMD_FMT;

typedef char(*p_arg)[MAX_ARG_LEN];

typedef enum {
	APN_E = 0,
	GADC_E = 15,
}CMD_CODE_E;
