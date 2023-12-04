#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_PROCESSES 3

int main(void){
    srand(time(NULL));
    int fd[2];
    int max = 0;
    int max_pid = 0;
    int max_i = 0;

    for(int i = 0; i < NUM_PROCESSES; i++){
        if(pipe(fd) == -1){
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if(pid == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if(pid == 0){ // child process
            close(fd[0]);
            int num = rand() % 100;
            int pid = getpid();
            printf("process %d, iteration %d, number %d\n", pid, i, num);
            write(fd[1], &num, sizeof(int));
            write(fd[1], &pid, sizeof(int));
            write(fd[1], &i, sizeof(int));
            exit(EXIT_SUCCESS);
        }
        else{ // parent process
            close(fd[1]);
            int num = 0;
            int pid = 0;
            int temp_i = 0;
            read(fd[0], &num, sizeof(int));
            read(fd[0], &pid, sizeof(int));
            read(fd[0], &temp_i, sizeof(int));
            if(num > max){
                max = num;
                max_pid = pid;
                max_i = temp_i;
            }
        }
    }

    printf("The maximum number is %d in the process %d, iteration %d\n", max, max_pid, max_i);
    return 0;
}
