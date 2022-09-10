#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <mqueue.h>

#include "msgheader.h"

#define OPEN_FLAG    O_RDWR|O_CREAT|O_EXCL
#define OPEN_MODE    S_IRUSR|S_IWUSR

//cleanup function to clean up the message queue
void cleanup(int signum)
{
    /*
    If one or more processes have the message queue open when mq_unlink()
    is called, the actual destruction of the message queue  shall be 
    postponed until
    all references to the message queue have been closed
    */

    if (-1 == mq_unlink(MQ_NAME))
    {
        perror("mq_unlink failed");
        printf("message queue could not be removed\n");
    }
    printf("message queue removed\n");
    exit(-1);
}

int main(void)
{
    samplemsgbuf    buf;
    int             retval = 0;

    mqd_t           msqid;
    struct mq_attr  qattr;

    /*
    setting the attribute structure before creating the queue
    setting of mq_flags  is not required, that is beign taken 
    from the 2nd parameter to mq_open call
    */
    qattr.mq_msgsize = MSG_SIZE;
    qattr.mq_curmsgs = CUR_MSGS;
    qattr.mq_maxmsg  = MAX_MSGS;

    if (-1 == (msqid = mq_open(MQ_NAME, OPEN_FLAG, OPEN_MODE, &qattr)))			// #define MQ_NAME  "/mq00001"
    {
        perror("mq_open");
        exit(-1);
    }
    printf("reciever: ready to receive messages.\n");


    if (-1 == mq_getattr(msqid, &qattr))
    {
        perror("mq_getattr");
        exit(-1);
    }
    printf("%d : %d : %d\n", qattr.mq_msgsize, qattr.mq_curmsgs, qattr.mq_maxmsg);
    /* 
    The following call to change the attribute of the message queue does not
    work. The mq_msgsize parameter can't be changed. Only mq_flags can be 
    changed by mq_setattr call 
    */
    qattr.mq_msgsize = MSG_SIZE;
    if (-1 == mq_setattr(msqid, &qattr, NULL))
    {
        perror("mq_getattr");
        exit(-1);
    }
    if (-1 == mq_getattr(msqid, &qattr))
    {
        perror("mq_getattr");
        exit(-1);
    }
    printf("%d : %d : %d\n", qattr.mq_msgsize, qattr.mq_curmsgs, qattr.mq_maxmsg);
    /*
    Install signal handler for cleanup as the receiver is in an infinite loop
    return from signal call, the old signal handler function is ignored
    */
    signal(SIGINT, cleanup);
    if (0 != errno)
    {
        printf("SIGINT set error %d \n", errno);
    }

    /*
    receiver started, it quits only if the queue has been removed
    */
    for(;;)
    {
        /*
        Messages with any priority can be received
        */
        if (0 <= (retval = mq_receive(msqid, buf, MSG_SIZE, NULL)))
        {
            buf[retval] = '\0';
            printf("receiver: \"%s\"\n", buf);
        }
        else
        {
            perror("msg queue receive");
            break;
        }
    }
    mq_close(msqid);
    mq_unlink(MQ_NAME);
    return 0;
}
