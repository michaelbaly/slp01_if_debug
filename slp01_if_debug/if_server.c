#include <stdio.h>
#include "if_server.h"
#include "cmd_type.h"

typedef struct r_queue {
	char* p_ack[R_QUEUE_SIZE];
	int front;
	int rear;
}r_queue_s;

r_queue_s rq;

/* init the ring queue */
void rq_init()
{
	rq.front = rq.rear = 0;
}

/* judge empty */
bool isempty(r_queue_s rq)
{
	if(rq.front == rq.rear)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/* judge full */
bool isfull(r_queue_s rq)
{
	if ((rq.rear + 1) % R_QUEUE_SIZE == rq.front)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/* enqueue */
void enqueue(char *packet)
{
	if(isfull(rq))
	{
		printf("qeueu is full\n");
		return;
	}

	rq.p_ack[rq.rear] = packet;
	rq.rear = (rq.rear + 1) % R_QUEUE_SIZE;

}

void dequeue()
{
	if (isempty(rq))
	{
		printf("qeueu is empty\n");
		return;
	}
	/* send packet via the socket */
	send_packet(sfd, rq.p_ack[rq.front]);

	/* release packet buffer */

	/* move head pointer to next */
	rq.front = (rq.front + 1) % R_QUEUE_SIZE
}


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




