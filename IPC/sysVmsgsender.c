#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msgheader.h"


//#define TYPE_SIZE  4


int main(void)
{
    int           msqid;
    size_t        readchars = 0;
//    char          mtype[TYPE_SIZE];
    key_t         key;
    samplemsgbuf  mbuf;

    if ((key = ftok(KEY_NAME, PROJ_ID_KEY)) == -1) 
    {
        perror("ftok");
        exit(-1);
    }

    if ((msqid = msgget(key, 0644)) == -1) {
        perror("msgget");
        exit(-1);
    }
    
    printf("Enter data to be sent to receiver\n");

    for(;;)
    {
        readchars = read(0, mbuf.mtext, MSGSIZE-1);
        mbuf.mtext[readchars-1] = '\0';
        mbuf.mtype = TYPE2_MSG;
        if (msgsnd(msqid, (struct msgbuf *)&mbuf, sizeof(mbuf), 0) == -1)
        {
                perror("msgsnd");
                if (EIDRM == errno)
                    break;
        }
    }
    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(-1);
    }
    return 0;
}
