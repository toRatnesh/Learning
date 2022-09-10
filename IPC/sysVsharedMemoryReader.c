/* This program creates a system V shared memory segment and read data 
	from shared memory segment created by another system V shared memory program */

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	
	/* variable declaration - begin*/
	key_t shm_key = 0;
	int shm_id = 0;
	int ret_val = 0;
	char * cptr = NULL;
	int index = 0;
	struct shmid_ds buff = {0};
	/* variable declaration - end*/

	//fprintf(stdout, "argv[0] : %s\n", argv[0]);
	//fprintf(stdout, "argv[1] : %s\n", argv[1]);
	//fprintf(stdout, "argv[2] : %s\n", argv[2]);
	

	/* arguments checking*/
	if(2 != argc)
	{
		fprintf(stdout, "Wrong no of arguments need exe and path for key\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	shm_key = ftok(argv[1], 'K');
	if(-1 == shm_key)
	{
		fprintf(stdout, "Unable to generate key\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}

	shm_id = shmget(shm_key, (64 * sizeof(char)), IPC_CREAT | S_IRWXU);
	if(-1 == shm_id)
	{
		fprintf(stdout, "Unable to generate shared memory id\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	cptr = (char *)shmat(shm_id, NULL, 0);
	if((void *)-1 == cptr)
	{
		fprintf(stdout, "Unable to map shared memory segment\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	ret_val = shmctl(shm_id, IPC_STAT, &buff);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to STAT shared memory segment\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}
/*
	for(index = 0; index < 32; index++)
		fprintf(stdout, "%d ", index);

	fprintf(stdout, "\n");
*/

	for(index = 0; index < buff.shm_segsz; index++)
		fprintf(stdout, "%c", *cptr++);
/*
	ret_val = shmdt((void *)cptr);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to detach shared memory segment\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}
*/
	ret_val = shmctl(shm_id, IPC_RMID, NULL);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to remove shared memory segment\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	fprintf(stdout, "\n");
	exit(EXIT_SUCCESS);
}



/*
	END OF FILE
*/

