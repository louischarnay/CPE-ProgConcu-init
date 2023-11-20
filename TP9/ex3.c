#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int toggle = 0;
void on_exit(int sig){
    if(sig == SIGINT){
        puts("Toggle");
        toggle = !toggle;
    }
}

int main(void){
    struct sigaction action;
    action.sa_handler = on_exit;
    sigaction(SIGINT, &action, NULL);
    while(1){
        if(toggle){
            puts("True");
        } else {
            puts("False");
        }
        sleep(10);
    }
    return 0;
}
