#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "dijkstra.h"
#include <stdlib.h>
#include <time.h>

#define KEY_1 1
#define KEY_2 2
#define SIZE 5

int main(void) {
	srand(time(NULL));
	int shmid = shmget(KEY_1, SIZE * sizeof(int), 0);
	int sem_write = sem_create(KEY_1, 1);
	int sem_read = sem_create(KEY_2, 0);
	int mutex = sem_create(3, 1);

	int* mem = shmat(shmid, NULL, 0);

	if((int64_t)mem == -1){
		puts("Bad shared meme");
		exit(-1);
	}

	int i = 0;
	while(1){
		if(i == SIZE){
			i = 0;
		} else {
			int val = rand() % 10;
			printf("Putting %d\n", val);
			P(sem_write);
			P(mutex);
			mem[i] = val;
			V(mutex);
			V(sem_write);
			V(sem_read);
			sleep(2);
			i++;
		}
	}
	shmdt(mem);

	return 0;
}
