#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

#define SUCCESS 0
#define FAILURE 1
#define ERR -1
#define ZERO 0
#define PORT 39000

int write_request(int,int*);
int read_response(int,char *);
int read_request(int,int *);
int write_response(int,char *);
int check_prime(int,char *);

