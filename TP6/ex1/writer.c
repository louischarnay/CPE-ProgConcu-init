#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "dijkstra.h"
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SNAME "sem"
#define COUNT 5
#define SHARED_MEM 1

int main(void){
	int mutex_read = semget(1, 1, SEM_A | SEM_R);
	int semid_write = semget(2, 1, SEM_A | SEM_R);
	int shmid = shmget(SHARED_MEM, sizeof(int), 0);

	if(mutex_read == -1){
		puts("first");
	}

	if(semid_write == -1){
		puts("second");
	}

	if(shmid == -1){
		puts("third");
	}

	if(mutex_read == -1 || semid_write == -1 || shmid == -1){
		puts("Wrongs ids");
		exit(-1);
	}

	int* shared = shmat(shmid, NULL, 0);

	if((int64_t)shared == -1){
		puts("Couldn't get shared var");
		exit(-1);
	}

	P(semid_write);
	*shared = *shared + 1;
	V(semid_write);

	int val_sahred = 0;
	do{
		P(mutex_read);
		val_sahred = *shared;
		V(mutex_read);
		sleep(10);
		printf("Read: %d\n", val_sahred);
	}
	while(val_sahred < 5);

	shmdt(shared);
	puts("Steven est gay");

	return 0;
}
