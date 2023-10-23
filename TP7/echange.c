#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 3

struct structArg
{
    int min, max, result;
    sem_t *sem1;
    sem_t *sem2;
    sem_t *sem3;
    pthread_mutex_t *mutex;
};

void *max(void *arg)
{
    int tab[N] = {1, 2, 3};
    int result = 0;
    int max = tab[0], index = 0;
    struct structArg *args = (struct structArg *)arg;
    while (result != -1)
    {
        max = tab[0];
        for (int i = 1; i < N; i++)
        {
            if (tab[i] < max)
            {
                max = tab[i];
                index = i;
            }
        }
        pthread_mutex_lock(args->mutex);
        printf("MAX : %d\n", max);
        args->max = max;
        pthread_mutex_unlock(args->mutex);
        sem_post(args->sem3);
        sem_wait(args->sem1);
        pthread_mutex_lock(args->mutex);
        result = args->result;
        tab[index] = args->max;
        pthread_mutex_unlock(args->mutex);
    }
    printf("Array MAX : \n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
    return NULL;
}

void *min(void *arg)
{
    int tab[N] = {1, 2, 3};
    int result = 0;
    int min = tab[0], index = 0;

    struct structArg *args = arg;
    while (result != -1)
    {
        min = tab[0];
        for (int i = 1; i < N; i++)
        {
            if (tab[i] > min)
            {
                min = tab[i];
                index = i;
            }
        }
        pthread_mutex_lock(args->mutex);
        printf("MIN : %d\n", min);
        args->min = min;
        pthread_mutex_unlock(args->mutex);
        sem_post(args->sem3);
        sem_wait(args->sem2);
        pthread_mutex_lock(args->mutex);
        result = args->result;
        tab[index] = args->min;
        pthread_mutex_unlock(args->mutex);
    }
    printf("Array MIN : \n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
    return NULL;
}

void *result(void *arg)
{
    struct structArg *args = arg;
    int result = 0;
    while (result != -1)
    {
        sem_wait(args->sem3);
        sem_wait(args->sem3);
        pthread_mutex_lock(args->mutex);
        if (args->max >= args->min)
        {
            args->result = -1;
        }
        else
        {
            args->result = args->max;
            args->max = args->min;
            args->min = args->result;
            args->result = 0;
        }
        result = args->result;
        pthread_mutex_unlock(args->mutex);
        printf("Resultat : %d\n", result);

        sem_post(args->sem2);
        sem_post(args->sem1);
    }
    return NULL;
}

int main()
{
    sem_t sem1, sem2, sem3;
    pthread_mutex_t mutex;
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    struct structArg arg;
    arg.max = 0;
    arg.min = 0;
    arg.result = 0;
    arg.sem1 = &sem1;
    arg.sem2 = &sem2;
    arg.sem3 = &sem3;
    arg.mutex = &mutex;

    pthread_t threadProd, threadCons, threadResult;
    pthread_create(&threadProd, NULL, max, &arg);
    pthread_create(&threadCons, NULL, min, &arg);
    pthread_create(&threadResult, NULL, result, &arg);

    pthread_join(threadProd, NULL);
    pthread_join(threadCons, NULL);
    pthread_join(threadResult, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    sem_destroy(&sem3);
    pthread_mutex_destroy(&mutex);
}