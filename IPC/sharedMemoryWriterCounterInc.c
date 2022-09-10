/*
	This program will create a Shared Memory Object and write interger values.
	This values will be letter read by some other Shared Memory read program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <semaphore.h>

#define SHMOBJ_LEN 256


typedef struct shmstruct
{
	int count;
}SHMSTRUCT;
sem_t * sem_mutex;			// for semaphore lock


int main(int argc, char **argv)
{
	// variable declaration - start
	int shm_fd = -1;
	int ret_val = 0;
	//int index = 0;
	
	struct stat shmfd_strct;
	SHMSTRUCT *cnt_ptr;
	// variable declaration - end

	//fprintf(stdout, "Inside main\n");
	if(3 != argc)
	{
		fprintf(stdout, "Wrong no of arguments\n");
		fprintf(stdout, "After exe give one shared memory argument path and one semaphore lock\n");
		exit(EXIT_FAILURE);
	}
	

	// function to open a shared memory object descriptor using shm_open()
	shm_fd = shm_open(argv[1], O_CREAT|O_RDWR, S_IRWXU);
	if(-1 == shm_fd)
	{
		fprintf(stdout, "Unable to create shared memory object descriptor\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}

	
	// update the length of shared memory object
	ret_val = ftruncate(shm_fd, sizeof(shm_fd));
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to update shared memory object lenghth\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	// get info of shared memory object (st_mode, st_size, st_uid, st_gid)
	shmfd_strct.st_mode = 0;	shmfd_strct.st_uid = 0;
	shmfd_strct.st_size = 0;	shmfd_strct.st_gid = 0;
	
	ret_val = fstat(shm_fd, &shmfd_strct);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to get info of shared memory object\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}
		
	

	// map the descriptor to shared memory
	//cnt_ptr = (struct shmstruct *)mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	cnt_ptr = (SHMSTRUCT *)mmap(NULL, shmfd_strct.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(MAP_FAILED == cnt_ptr)
	{
		fprintf(stdout, "Unable to map shared memory object \n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "cnt_ptr: %p\n", cnt_ptr);

	// after call to mmap descriptor may be closed
	ret_val = close(shm_fd);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to close descriptor\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	// open and close semaphore
	sem_mutex = sem_open(argv[2], O_CREAT | O_RDWR, S_IRWXU, 1);
	if(SEM_FAILED == sem_mutex)
	{
		fprintf(stdout, "Unable to open semaphore\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}
	
	fprintf(stdout, "Inside semaphore server\n");

	ret_val = sem_close(sem_mutex);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to close semaphore\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	// remove maping of shared memory object
	ret_val = munmap(NULL, shmfd_strct.st_size);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to unmap shared memory object\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}

/*	
UNLINK AFTER READING	 
	ret_val = shm_unlink(argv[1]);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to unlink shared memory object\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}
	
	
*/
	cnt_ptr = NULL;
	fprintf(stdout, "\n");
	exit(EXIT_SUCCESS);

}	// end of int main(int argc, char **argv)


/*******************
		END OF FILE
********************/