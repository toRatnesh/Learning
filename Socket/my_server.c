#include"header.h"

int main() {
	struct sockaddr_in server;
	struct sockaddr_in client;
	int socket_fd1;
	int socket_fd2;
	int ret_val;
	char prime[20];
	int integer;
	int size_of_struct;
	
	socket_fd1 = socket(AF_INET,SOCK_STREAM,0);
	if(ERR == socket_fd1)
	{
		perror("\nsocket error");
		exit(EXIT_FAILURE);
	}
	
	printf("Starting Server : \n");	
	
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	ret_val = bind(socket_fd1,(struct sockaddr*)&server,sizeof(server));
	if(ERR == ret_val) {
		perror("\nBind error");
		exit(EXIT_FAILURE);
	}
	
	ret_val = listen(socket_fd1,5);
	if(ERR == ret_val) {
		perror("\nListen Error");
		exit(EXIT_FAILURE);
	}
	
	while(1) {
		size_of_struct = sizeof(client);
		socket_fd2 = accept(socket_fd1,(struct sockaddr*)&client,(socklen_t*)&size_of_struct);
		if(ERR == socket_fd2) {
			perror("\nAccept error");
			exit(EXIT_FAILURE);
		}		
		
		while(1) {
			ret_val = read_request(socket_fd2,&integer);
			if(FAILURE == ret_val) {
				perror("\nError");
				exit(EXIT_FAILURE);
			}
			
			if(0 == integer)
				break;
				
			ret_val = check_prime(integer,prime);
	
			printf("%s\n",prime);
			ret_val = write_response(socket_fd2,prime);
			if(FAILURE == ret_val) {
				perror("\nError");
				exit(EXIT_FAILURE);
			}
		}
		close(socket_fd2);
	}
	
	close(socket_fd1);
	return SUCCESS;
}

