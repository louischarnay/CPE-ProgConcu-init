#include <stdio.h>
#include "dijkstra.h"
 #include <sys/sem.h>

int main(void){
	sem_delete(semget(1, 1, SEM_A | SEM_R));
	return 0;
}