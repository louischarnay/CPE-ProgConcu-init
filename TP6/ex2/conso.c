#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "dijkstra.h"

#define KEY_1 1
#define KEY_2 2
#define SIZE 5

int main(void) {
	int shmid = shmget(KEY_1, SIZE * sizeof(int), 0);
	if (shmid == -1) {
		perror("Shmget Memory");
		exit(-1);
	}
	int* mem = shmat(shmid, NULL, 0);
	if ((int64_t)mem == -1) {
		perror("Shmat Memory");
		exit(-1);
	}

	int sem_read = sem_create(KEY_2, 0);
	int mutex = sem_create(3, 0);
	for (int i = 0; i < SIZE; i++) {
		P(sem_read);
		P(mutex);
		int var = mem[i];
		printf("read: %d\n", var);
		V(mutex);
		sleep(2);
	}
	shmdt(mem);

	return 0;
}
