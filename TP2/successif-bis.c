#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	for(size_t i = 0; i < 3; ++i){

		pid_t child = fork();

		if(child == 0 && i == 0){

			if(execlp("du", "du", "-sh", "/usr/share", NULL) == -1){
				puts("Failed to exec command : du");
				exit(-1);
			}
		} else if(child == 0 && i == 1){
			if(execlp("ls", "ls", "-l", NULL) == -1){
				puts("Failed to exec command : ls");
				exit(-1);
			}
		} else if(child == 0 && i == 2){
			if(execlp("ps", "ps", NULL) == -1){
				puts("Failed to exec command : ps");
				exit(-1);
			}
		}
		 while (wait(NULL) != -1);
	}
	return 0;
}