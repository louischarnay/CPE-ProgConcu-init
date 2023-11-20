#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int toggle = 1;
void on_exit(int sig){
    if(sig == SIGUSR1){
        puts("Interception");
        toggle = (toggle + 1) % 2;
    }

    if(sig == SIGUSR2){
        puts("Exit");
        exit(0);
    }
}

int main(void){
    pid_t pid = fork();
    if(pid == 0){
        struct sigaction action;
        action.sa_handler = on_exit;
        sigaction(SIGUSR1, &action, NULL);
        sigaction(SIGUSR2, &action, NULL);
        while(1){
            if(toggle){
                puts("child");
            }
            
            sleep(2);
        }
        return 0;
    }


    for(int i = 0;i < 6; ++i){
        if(i == 3 || i == 5){
            int stat = kill(pid, SIGUSR1);
            if(stat == -1){
                perror("kill");
                return 1;
            }
        }
        puts("father");
        sleep(1);
    }

    int stat = kill(pid, SIGUSR2);
    if(stat == -1){
        perror("kill");
        return 1;
    }
    return 0;
}
