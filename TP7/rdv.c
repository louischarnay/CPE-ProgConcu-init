#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 6
struct structArg
{
    pthread_barrier_t *barrier;
    int id;
};
void *task1(void *arg)
{
    struct structArg *args = arg;
    srand(getpid() + args->id);
    int random = (rand() % 3) * args->id;
    printf("Thread %d sleeping %d\n", args->id, random);
    sleep(random);
    printf("Thread %d wait others\n", args->id);
    pthread_barrier_wait(args->barrier);
    printf("Thread %d awake\n", args->id);
    return NULL;
}
int main(void)
{
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, NULL, N);
    pthread_t thread[N];
    struct structArg args[N];
    for (int i = 0; i < N; i++)
    {
        args[i].barrier = &barrier;
        args[i].id = i + 1;
        pthread_create(&thread[i], NULL, task1, &args[i]);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(thread[i], NULL);
    }
    pthread_barrier_destroy(&barrier);
    return 0;
}