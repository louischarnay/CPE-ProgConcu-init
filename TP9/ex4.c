#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int toggle = 0;
void on_exit(int sig){
    if(sig == SIGINT){
        puts("kill");
        toggle = !toggle;
    }
}

int main(void){
    pid_t pid = fork();
    if(pid == 0){
        while(1){
            puts("child");
            sleep(2);
        }
        return 0;
    }


    for(int i = 0; i < 3; ++i){
        puts("father");
        sleep(1);
    }

    int stat = kill(pid, SIGKILL);

    if(stat == -1){
        perror("kill");
        return 1;
    }

    return 0;
}
