#include <stdio.h>
#include <pthread.h>

void *task(void *arg){
    int r = rand() % 10;
    sem_t *sem = arg;
    puts("start task");
    sleep(r);
    pthread_barrier_wait(&barrier);
    return NULL;
}

int main(void)
{
    int n = 3;
    pthread_barrier_t barrier;
    pthread_t thread[n];
    for (int i = 0; i < n; i++)
    {
        pthread_create(&thread[i], NULL, task, &sem);
    }
    for (int i = 0; i < n; i++)
    {
        pthread_join(thread[i], NULL);
    }
    puts("start rendez-vous");
    sem_destroy(&sem);
    return 0;
}