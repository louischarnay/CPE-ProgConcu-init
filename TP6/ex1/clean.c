#include <stdio.h>
#include "dijkstra.h"
#include <sys/sem.h>
#include <sys/shm.h>

int main(void){
	sem_delete(semget(1, 1, SEM_A | SEM_R));
	sem_delete(semget(2, 1, SEM_A | SEM_R));
	int shmid = shmget(1, sizeof(int), 0);
	return shmctl(shmid, IPC_RMID, NULL);
}
