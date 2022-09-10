#include"header.h"


int main(int argc,char *argv[])
{
        if(NULL == argv[1])
        {
                printf("\nInvalid no of args");
                printf("\nEnter Server's address");
                exit(EXIT_FAILURE);
        }
        if(NULL == argv[2])
        {
                printf("\nInvalid no of args");
                printf("\nEnter Port No");
                exit(EXIT_FAILURE);
        }

        int socket_fd;
        struct sockaddr_in server;
        int ret_val;
	int integer;
	int integer1;
	char prime[20];

        socket_fd = socket(AF_INET,SOCK_STREAM,0);
        if(ERR == socket_fd)
        {
                perror("\nSOcket Error");
                exit(EXIT_FAILURE);
        }

        server.sin_family = AF_INET;
        server.sin_port = htons(atoi(argv[2]));
        server.sin_addr.s_addr = inet_addr(argv[1]);
        ret_val = connect(socket_fd,(struct sockaddr*)&server,sizeof(server));
        if(ERR == ret_val)
        {
                perror("\nConnect error");
                exit(EXIT_FAILURE);
        }
	
	while(1)
	{
		printf("Enter any number : \n");
		scanf("%d",&integer1);
		integer = integer1;
		ret_val = write_request(socket_fd,&integer);
		if(FAILURE == ret_val)
		{
			printf("\nError");
			exit(EXIT_FAILURE);
		}

		if(0 == integer)
			break;

		ret_val = read_response(socket_fd,prime);
		if(FAILURE == ret_val)
		{
			printf("\nError");
			exit(EXIT_FAILURE);
		}
		printf("%s\n",prime);
	}
	close(socket_fd);
	
	return SUCCESS;
}

