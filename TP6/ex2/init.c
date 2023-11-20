#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "dijkstra.h"
#include <sys/shm.h>

#define SEM_WRITE 1
#define SEM_READ 2
#define MUTEX 3
#define SHARED_MEM 1
#define SIZE 5

int main(void){
	sem_create(SEM_WRITE, 1);
	sem_create(SEM_READ, 0);
	sem_create(MUTEX, 1);
	int shmid = shmget(SHARED_MEM, SIZE * sizeof(int), IPC_CREAT| IPC_EXCL| 0600);

	if(shmid == -1){
		puts("Wrongs ids");
		exit(-1);
	}

	int* shared = shmat(shmid, NULL, 0);
	
	if((int64_t)shared == -1){
		puts("failed to create shared var");
		exit(-1);
	}

	*shared = 0;
	shmdt(shared);
	return 0;
}
