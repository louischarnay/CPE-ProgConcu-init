#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void on_alarm(int sig){
    if(sig == SIGALRM){
        puts("Too late");
        exit(0);
    }
}

int main(void){
    char buffer[100];
    struct sigaction action;
    action.sa_handler = on_alarm;
    sigaction(SIGALRM, &action, NULL);
    while(1){
        alarm(5);
        puts("Entrer un entier en moins de 5 secondes: ");
        fgets(buffer, 100, stdin);
        int i;
        if(sscanf(buffer, "%d", &i) == 1){
            puts("Ok merci !!");
            break;
        }
    }

    return 0;
}
