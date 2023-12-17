#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define TO_GEN 5

// structure to hold pipes
struct pipes {
	int generator_filter[2];
	int filter_even[2];
	int filter_odd[2];
	int even_generator[2];
	int odd_generator[2];
};

void filter_proc(struct pipes* tubes);
void sum_even_proc(struct pipes* tubes);
void sum_odd_proc(struct pipes* tubes);

int main(){
	srand(time(NULL));

	struct pipes tubes;
    // on crée les pipes que le processus père va utiliser
	if(pipe(tubes.generator_filter) == -1 || pipe(tubes.even_generator) == -1 || pipe(tubes.odd_generator) == -1){
		puts("[X] Error creating pipe");
		exit(-1);
	}

	pid_t filter = fork();

	if(filter == 0){
		filter_proc(&tubes);
	} else {
		close(tubes.generator_filter[0]);
		int to_send = -1;
		for(int i = 0; i < TO_GEN; ++i){
			to_send = rand() % 101;
			//printf("sending: %d\n", to_send);
			write(tubes.generator_filter[1], &to_send, sizeof(int));
		}
		to_send = -1;
		write(tubes.generator_filter[1], &to_send, sizeof(int));


		close(tubes.generator_filter[0]);
		close(tubes.even_generator[1]);
		close(tubes.odd_generator[1]);

		int sum_even = 0;
		int sum_odd = 0;
		read(tubes.even_generator[0], &sum_even, sizeof(int));
		read(tubes.odd_generator[0], &sum_odd, sizeof(int));

		printf("Sum even: %d\nSum odd: %d\n", sum_even, sum_odd);

		close(tubes.even_generator[0]);
		close(tubes.odd_generator[0]);
	
	}
	
	return 0;
}

void filter_proc(struct pipes* tubes){
	int received = -1;

	if(pipe(tubes->filter_even) == -1 || pipe(tubes->filter_odd) == -1){
		puts("[X] Error creating filters pipes");
		exit(-1);
	}


	pid_t even = fork();
	if(even == 0){
        // fils
		sum_even_proc(tubes);
	}else {
        // pere
		pid_t odd = fork();
		if(odd == 0){
            // fils 2
			sum_odd_proc(tubes);
		}else{
            // pere
			close(tubes->generator_filter[1]);

			close(tubes->filter_even[0]);
			close(tubes->filter_odd[0]);
			do {
				read(tubes->generator_filter[0], &received, sizeof(int));
				//printf("filter_proc read: %d\n", received);

				if(received == -1){
					//puts("Received -1");
					break;
				}

				write(received % 2 == 0 ? tubes->filter_even[1] : tubes->filter_odd[1], &received, sizeof(int));
			}while(received != -1);

			received = -1;
			write(tubes->filter_even[1], &received, sizeof(int));
			write(tubes->filter_odd[1], &received, sizeof(int));
			
			close(tubes->filter_even[1]);
			close(tubes->filter_odd[1]);
		}
	}
}

void sum_even_proc(struct pipes* tubes){
	int to_sum = -1;
	int total = 0;
	close(tubes->filter_even[1]);
	do {
		read(tubes->filter_even[0], &to_sum, sizeof(int));
		//printf("sum_even_proc read %d\n", to_sum);
		if(to_sum != -1){
			total += to_sum;
		}else{
			break;
		}
	}while(to_sum != -1);
	//printf("Even sum %d\n", total);
	close(tubes->even_generator[0]);
	write(tubes->even_generator[1], &total, sizeof(int));
}

void sum_odd_proc(struct pipes* tubes){
	int to_sum = -1;
	int total = 0;
	close(tubes->filter_odd[1]);
	do {
		read(tubes->filter_odd[0], &to_sum, sizeof(int));
		//printf("sum_odd_proc read %d\n", to_sum);
		if(to_sum != -1){
			total += to_sum;
		}else {
			break;
		}
	}while(to_sum != -1);
	//printf("Odd sum %d\n", total);
	close(tubes->odd_generator[0]);
	write(tubes->odd_generator[1], &total, sizeof(int));
}