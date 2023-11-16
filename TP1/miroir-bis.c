#include <stdio.h>
#include <string.h>


void print_reverse(const char* output);

int main(int argc, char** argv){

	for(int i = 1; i < argc; ++i){
		print_reverse(argv[i]);
	}
	return 0;
}


void print_reverse(const char* output){
	for(int i = strlen(output); i > -1; --i){
		printf("%c", output[i]);
	}
	printf("\n");
}