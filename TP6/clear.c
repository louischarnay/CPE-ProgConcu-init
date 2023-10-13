#include <sys/shm.h>

#include "dijkstra/dijkstra.c"

#define KEY 5942
#define KEY_2 5943
#define KEY_3 5944
#define SIZE 4
int main(void)
{
    int shmid = shmget(KEY, SIZE * sizeof(int), 0);
    int res = shmctl(shmid, IPC_RMID, NULL);
    if (res == -1)
    {
        perror("Delete Shm");
    }
    int mutexId = sem_create(KEY, 1);
    sem_delete(mutexId);
    int semId = sem_create(KEY_2, 0);
    sem_delete(semId);
    int semId2 = sem_create(KEY_3, 0);
    sem_delete(semId2);
    return 0;
}