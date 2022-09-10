/*
	This program will create a Shared Memory Object and read interger values.
	This values had been wriiten by some other Shared Memory write program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>

#define SHMOBJ_LEN 256

int main(int argc, char **argv)
{
	// variable declaration - start
	int shm_fd = -1;
	int ret_val = 0;
	int index = 0;

	struct stat shmfd_strct;
	char * ptr = NULL;
	// variable declaration - end

	//fprintf(stdout, "Inside main\n");
	if(2 != argc)
	{
		fprintf(stdout, "Wrong no of arguments\n");
		fprintf(stdout, "After exe give one shared memory argument path\n");
		exit(EXIT_FAILURE);
	}
	

	// function to open a shared memory object descriptor using shm_open()
	//shm_fd = shm_open(argv[1], O_CREAT|O_RDWR, S_IRWXU);
	shm_fd = shm_open(argv[1], O_RDONLY, S_IRWXU);
	if(-1 == shm_fd)
	{
		fprintf(stdout, "Unable to open shared memory object descriptor\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}

/*
CAN NOT UPDATE FOR READ ONLY	
	// update the length of shared memory object
	ret_val = ftruncate(shm_fd, 256);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to update shared memory object lenghth\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}

*/

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
	//ptr = mmap(NULL, 256, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	//ptr = mmap(NULL, shmfd_strct.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	ptr = mmap(NULL, shmfd_strct.st_size, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(MAP_FAILED == ptr)
	{
		fprintf(stdout, "Unable to map shared memory object \n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	// after call to mmap descriptor may be closed
	ret_val = close(shm_fd);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to close descriptor\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}


	// write data to shared memory
	for(index = 0; index < shmfd_strct.st_size; index++)
	{
		//if( (*ptr++) != (index % 256) )
		//	fprintf(stdout, "Mismatched value in shared memory\n");
		fprintf(stdout, "%c", *ptr++);
	}

		 
	ret_val = shm_unlink(argv[1]);
	if(-1 == ret_val)
	{
		fprintf(stdout, "Unable to unlink shared memory object\n");
		perror(" ERROR: ");
		exit(EXIT_FAILURE);
	}
	

	fprintf(stdout, "\n");
	exit(EXIT_SUCCESS);

}	// end of int main(int argc, char **argv)