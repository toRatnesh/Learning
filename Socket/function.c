#include"header.h"
int read_request(int socket_fd,int *integer)
{
        int n;
        n = read(socket_fd,integer,sizeof(int));
        if(0 > n)
        {
                perror("\nReading error\n");
                return FAILURE;
        }
        *integer = ntohl(*integer);
        return SUCCESS;
}

int check_prime(int integer,char *prime)
{
        int i,count =0;
        memset(prime,0,20);
        for(i = 2;i <= integer/2;i++)
        {
                if(integer%i ==0)
                count++;
        }
        if(count == 0)
        {
                sprintf(prime,"%d is prime",integer);
        }
        else
        {
                 sprintf(prime,"%d is not prime",integer);

        }
        return SUCCESS;

}

int write_response(int socket_fd,char *buffer)
{
        int len;
        int n;
        len = strlen(buffer);
        int bytes=0;
        n = write(socket_fd,&len,sizeof(int));
        if(0 > n)
        {
                perror("Writing err\n");
		return FAILURE;
        }

        while(bytes<len)
        {
                n = write(socket_fd,buffer+bytes,len- bytes);
                if(0 > n)
                {
                        perror("Writing Err\n");
                        return FAILURE;
                }
                bytes = bytes + n;
        }

        return SUCCESS;
}

int write_request(int socket_fd,int *integer)
{
        int n;
        *integer = htonl(*integer);
        n = write(socket_fd,integer,sizeof(int));
        if(0 > n)
        {
                perror("\nWriting Error");
                return FAILURE;
        }
        return SUCCESS;
}

int read_response(int socket_fd,char *buffer)
{
        memset(buffer,0,20);
        int len,bytes=0;
        int n;
        n = read(socket_fd,&len,sizeof(int));
        if(0 > n)
        {
                perror("Reading error\n");
                return FAILURE;
        }
        while(bytes<len)
        {
                n = read(socket_fd,buffer+bytes,len-bytes);
                if(0>n)
                {
                        perror("Reading Error\n");
                        return FAILURE;
                }
                bytes = bytes+n;

        }
        return SUCCESS;
}


