#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFF_SIZE 128

int main(void){
	srand(time(NULL));

	int tube1[2];
	int tube2[2];
	int pipe_stat = pipe(tube1);
	int pipe_stat2 = pipe(tube2);

	if(pipe_stat == -1 || pipe_stat2 == -1){
		puts("Error creating pipe");
		exit(-1);
	}

	int child = fork();

	if(!child){
		close(tube1[1]);
		close(tube2[0]);
		int guess = 0;
		int secret = rand() % 101;
		char state = 'i';

		while(1){

			read(tube1[0], &guess, sizeof(int));

			if(secret > guess){
				state = 'g';
				write(tube2[1], &state, sizeof(char));
			} else if(secret < guess){
				state = 's';
				write(tube2[1], &state, sizeof(char));
			} else {
				break;
			}
		}
		
		state = 'w';
		write(tube2[1], &state, sizeof(char));

		close(tube1[0]);
		close(tube2[1]);

	} else {
		close(tube1[0]);
		close(tube2[1]);

		char input[BUFF_SIZE];
		int num = 0;
		int won = 'f';

		while(1){
			
			puts("Entrer un mot (limite 128 char): ");
			fgets(input, BUFF_SIZE, stdin);
			
			
			if(sscanf(input, "%d", &num) < 0){
				puts("not a number");
				continue;
			}

			write(tube1[1], &num, sizeof(int));

			read(tube2[0], &won, sizeof(char));

			if(won == 's'){
				puts("It's smaller");
			} else if(won == 'g'){
				puts("It's greater");
			}else {
				if(won == 'w'){
					puts("You won");
					break;
				} else {
					printf("Undefined %c\n", won);
				}
			}

		}

		close(tube1[1]);
		close(tube2[0]);

	}

	return 0;
}