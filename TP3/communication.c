#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFF_SIZE 128

int main(void){
	srand(time(NULL));

	int tube[2];
	int pipe_stat = pipe(tube);

	if(pipe_stat == -1){
		puts("Error creating pipe");
		exit(-1);
	}

	int son = fork();

	if(!son){
		close(tube[1]);
		
		int to_read = 0;
		char buffer[BUFF_SIZE];

		read(tube[0], &to_read, sizeof(int));
		printf("Will need to read %d char\n", to_read);
		read(tube[0], buffer, to_read);
		printf("Reiceived : %s", buffer);

	} else {
		close(tube[0]);

		char input[BUFF_SIZE];
		puts("Entrer un mot (limite 128 char): ");
		fgets(input, BUFF_SIZE, stdin);
		
		int len_to_read = strlen(input) + 1;

		write(tube[1], &len_to_read, sizeof(int));
		write(tube[1], input, sizeof(char) * (strlen(input) + 1));
		close(tube[1]);
	}
	return 0;
}