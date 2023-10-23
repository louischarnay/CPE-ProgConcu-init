#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 3

struct structArg{
    int idProd, idCons;
    int tab[N];
    sem_t *producteur;
    sem_t *consommateur;
    pthread_mutex_t *mutex;
};

void* prod(void* arg){
    printf("Je suis le producteur\n");
    struct structArg *args = (struct structArg*) arg;
    sem_wait(args->producteur);
    pthread_mutex_lock(args->mutex);
    srand(time(NULL));
    args->tab[args->idProd] = rand()%10;
    printf("Valeur produite : %d\n", args->tab[args->idProd]);
    args->idProd = (args->idProd + 1) % N;
    pthread_mutex_unlock(args->mutex);
    sem_post(args->consommateur);
    return NULL;
}

void* cons(void* arg){
    printf("Je suis le consommateur\n");
    struct structArg *args = (struct structArg*) arg;
    sem_wait(args->consommateur);
    pthread_mutex_lock(args->mutex);
    printf("Valeur consommée : %d\n", args->tab[args->idCons]);
    args->idCons = (args->idCons + 1) % N;
    pthread_mutex_unlock(args->mutex);
    sem_post(args->producteur);
    return NULL;
}

int main(){
    sem_t producteur, consommateur;
    pthread_mutex_t mutex;
    sem_init(&producteur, 0, N);
    sem_init(&consommateur, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    struct structArg arg;
    arg.idProd = 0;
    arg.idCons = 0;
    arg.producteur = &producteur;
    arg.consommateur = &consommateur;
    arg.mutex = &mutex;

    pthread_t threadProd, threadCons;
    pthread_create(&threadProd, NULL, prod, &arg);
    pthread_create(&threadCons, NULL, cons, &arg);

    pthread_join(threadProd, NULL);
    pthread_join(threadCons, NULL);

    sem_destroy(&producteur);
    sem_destroy(&consommateur);
    pthread_mutex_destroy(&mutex);
}