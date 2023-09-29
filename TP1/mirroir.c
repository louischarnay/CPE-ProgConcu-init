#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    if (argc > 1) {
        for (int i = 1; i < argc; i++){
            int length = strlen(argv[i]);
            for (int j = length - 1; j >= 0; j--){
                printf("%c", argv[i][j]);
            }
            printf(" ");
        }
        printf("\n");
    } else {
        printf("Veuillez entrer au moins un argument\n");
    }
    return 0;
}

