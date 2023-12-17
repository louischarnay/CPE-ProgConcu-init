#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    float avg = 0;
    int tmp = 0;

    if (argc > 1) {
        for (int i = 1; i < argc; i++){
            if(sscanf(argv[i], "%d", &tmp) != 1 || tmp < 0 || tmp > 20){
                printf("Notes non valide(s)\n");
                return 1;   
            } else {
                avg += tmp;
            }
        }
        printf("Moyenne : %2.1f\n", avg / (argc - 1));
    } else {
        printf("Aucune note fourni, moyenne impossible à calculer\n");
    }
    
    return 0;
}