#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msgheader.h"

#define SIZE_OF_MSG (sizeof(samplemsgbuf))

int main(void)
{
    samplemsgbuf   buf;
    int            msqid;
    key_t          key;
	int count=0;
    if ((key = ftok(KEY_NAME, PROJ_ID_KEY)) == -1) 
    {
        perror("ftok");
        exit(-1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) 
    {
        perror("msgget");
        exit(-1);
    }
    
    printf("reciever: ready to receive messages.\n");

    for(;;) /* receiver quits only if the queue has been removed */
    {
        /* Only a message of TYPE1 type can be retrieved*/ 
	count =  msgrcv(msqid, (struct msgbuf *)&buf, SIZE_OF_MSG, TYPE2_MSG, 0);
	if(count > 0)	  
        {
    		printf("receiver: %d : \"%s\"\n", buf.mtype, buf.mtext);
        }
        else
        {
            perror("In msgrcv for TYPE2_MSG");
            if (EIDRM == errno)
            {
                perror("msg queue");
                break;
            }
        }
    }
    return 0;
}
