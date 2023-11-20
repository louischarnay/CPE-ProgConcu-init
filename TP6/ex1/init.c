#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "dijkstra.h"
#include <sys/shm.h>

#define SHARED_MEM 1

int main(void){
	sem_create(1, 1);
	sem_create(2, 1);
	int shmid = shmget(SHARED_MEM, sizeof(int), IPC_CREAT| IPC_EXCL| 0600);

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
