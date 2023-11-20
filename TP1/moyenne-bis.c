#include <stdio.h>
#include <stdlib.h>

int parse_int(const char* to_validate);

int main(int argc, char const *argv[]){

	if(argc < 2){
		puts("Aucune note fourni, moyenne impossible à calculer");
		exit(-1);
	}

	float sum = 0.0;
	for(int i = 1; i < argc; ++i){
		int res = parse_int(argv[i]);
		if(res == -1){
			puts("Note(s) non valide(s)");
			exit(-1);
		}

		sum += res;
	}

	printf("Moyenne: %4.2f", sum / (argc - 1));
	return 0;
}

int parse_int(const char* to_validate){
	int n;
	if(sscanf(to_validate, "%d", &n) && n >= 0 && n <= 20){
		return n;
	}
	return -1;
}