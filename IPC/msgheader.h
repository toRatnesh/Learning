#ifndef MSG_H
#define MSG_H

//Default Message queue attributes
#define MSG_SIZE 	256
#define CUR_MSGS 	0
#define MAX_MSGS 	10

#define TYPE1_MSG	1
#define TYPE2_MSG	2
#define TYPE3_MSG	3
#define PROJ_ID_KEY	63

#define MQ_NAME  "/mq00001"

typedef char samplemsgbuf[MSG_SIZE];

#endif
