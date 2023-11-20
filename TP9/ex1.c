#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void on_exit(int sig){
    if(sig == SIGINT){
        puts("Exit");
        exit(0);
    }
}

int main(void){
    struct sigaction action;
    action.sa_handler = on_exit;
    sigaction(SIGINT, &action, NULL);
    while(1){
        puts("Waiting for SIGINT");
        sleep(10);
    }
    return 0;
}
