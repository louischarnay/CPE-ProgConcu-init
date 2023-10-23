#include <sys/shm.h>

#include "dijkstra/dijkstra.c"

#define KEY 5942
#define KEY_2 5943
#define KEY_3 5944
#define SIZE 4

int main(void)
{
    sem_create(KEY, 1);
    sem_create(KEY_2, SIZE);
    sem_create(KEY_3, 0);
    int shmid = shmget(KEY, 3 * sizeof(int), IPC_CREAT | IPC_EXCL | 0600);
    if (shmid == -1)
    {
        perror("Shmget Memory");
    }
    return 0;
}