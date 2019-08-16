#include <stdio.h>
#include "if_server.h"


// interface func
uint8 para_cmd_str(char* cmd_str, char (*arg_list)[MAX_ARG_LEN], CMD_TYPE_E *c_type)
{
	char* cmd_tmp = cmd_str;
	char* arg_start = NULL;
	uint8 arg_cnt = 0;

#ifdef ATEL_DEBUG
		printf("[cmd from server] %s\n", cmd_str);
#endif
#if 0
	if ('?' == *(cmd_tmp + strlen(cmd_tmp) - 1))
	{
		*c_type = QUERY_CMD_E;
	}
	else if ('#' == *(cmd_tmp + strlen(cmd_tmp) - 1)) 
	{
		*c_type = SET_CMD_E;
	}
#endif
	/* parase the count of parameters */
	while (NULL != cmd_tmp)
	{
		arg_start = cmd_tmp;
		cmd_tmp = strchr(cmd_tmp, ',');

		if (cmd_tmp)
		{
			/* extract each param */
			strncpy_s(*arg_list++, MAX_ARG_LEN, arg_start, cmd_tmp - arg_start);
			cmd_tmp++;	/* skip ',' */
		}
		else
		{	
			//cmd_tmp = strchr(arg_start, '#');
			if (cmd_tmp = strchr(arg_start, '#'))
			{
				*c_type = SET_CMD_E;
				strncpy_s(*arg_list++, MAX_ARG_LEN, arg_start, cmd_tmp - arg_start);
				break;
			}
			else if (cmd_tmp = strchr(arg_start, '?'))
			{
				*c_type = QUERY_CMD_E;
				strncpy_s(*arg_list++, MAX_ARG_LEN, arg_start, cmd_tmp - arg_start);
				break;
			}
			else
			{
				printf("error command format\n");
			}
		}

		arg_cnt++;
	}

	return ++arg_cnt;
}
// algrithm




