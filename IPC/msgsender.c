#include <stdio.h>
//#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <mqueue.h>

#include "msgheader.h"

#define OPEN_FLAG       O_RDWR

#define INPUT_MSG_SIZE  MSG_SIZE - 1

int main(void)
{
    int             readchars = 0;
    int             retval = 0;
    mqd_t           msqid;
    struct mq_attr  qattr;
    samplemsgbuf    buf;

    if (-1 == (msqid = mq_open(MQ_NAME, OPEN_FLAG)))				// #define MQ_NAME  "/mq00001"
    {
        perror("mq_open");
        exit(-1);
    }

    for(;;) /* sender in the infinite loop */
    {
        printf("sender: give me a message to send.\n");
        printf("typing \"stop\" would stop sending messages.\n");
        readchars = read(0, buf, INPUT_MSG_SIZE);
        if (0 == strncmp(buf, "stop", 4))
           break;

        /*
        only readchars-1 characters are sent to the peer to avoid sending '\n'
        */
        if (0 > mq_send(msqid, buf, readchars-1, 0))
        {
            perror("msg queue send");
            break;
        }
    }
    mq_close(msqid);
    return 0;
}
