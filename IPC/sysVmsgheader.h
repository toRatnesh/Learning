#ifndef MSG_H
#define MSG_H

#define MSGSIZE 	256
#define TYPE1_MSG	1
#define TYPE2_MSG	2
#define TYPE3_MSG	3
#define PROJ_ID_KEY	63

#define KEY_NAME	"./keyfile6"

typedef struct samplemsgbuf {
    long mtype;
    char mtext[MSGSIZE];
} samplemsgbuf;

#endif
