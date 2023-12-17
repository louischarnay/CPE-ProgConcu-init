#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char *argv[]){

	if(argc < 2){
		exit(-1);
	}

	int count;
	// atoi function is not safe, use sscanf instead
	int stat = sscanf(argv[1], "%d", &count);

	if(stat <= 0){
        fprintf(stderr, "Usage: %s <nombre de processus>\n", argv[0]);
        exit(1);
	}

	for(int i = 0; i < count; ++i){
		pid_t child_pid = fork();

		// if child_pid == 0, we are in child process
		if(child_pid == 0){
			printf("Mon PID en tant que fils %d, mon pere est %d\n", getpid(), getppid());
			sleep(2* (i + 1));
			exit(i);
		}

		if(child_pid == -1){
			perror("Erreur lors de la création du processus fils");
			exit(1);
		}
	}

    // parent process code
	for(int i = 0; i < count; ++i){
		int status = 0;
		pid_t finished_pid = wait(&status);
		// Note: WIFEXITED(status) is not 0 if the child terminated normally
		// which means that if we have a 0, the child terminated abnormally
		printf("Le fils %d a fini, avec la valeur %d\n", finished_pid, WEXITSTATUS(status));
	}
	return 0;
}