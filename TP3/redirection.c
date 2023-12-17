#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void exercice_1() {
    // Exercice 1 //
    int input = open("/etc/passwd", O_RDONLY);
    if (input == -1) {
        perror("Open");
        exit(-1);
    }

    // 0 = stdin
    // 1 = stdout
    // 2 = stderr

    dup2(input, STDIN_FILENO);
    execlp("wc", "wc", "-l", NULL);
}

void exercice_2() {
    // Exercice 2 //
	int tube[2];
	int res = pipe(tube);
	if (res == -1) {
		perror("Création Pipe");
		exit(-1);
	}

	if (fork() == 0) {
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
		execlp("tr","tr","a-z", "A-Z", NULL);
	} else {
		close(tube[0]);
		dup2(tube[1], STDOUT_FILENO);
		close(tube[1]);
		execlp("cut","cut", "-f", "1,3", "-d", ":", "/etc/passwd", NULL);
	}
}


// le fichier /etc/passwd est l'entrée standard de la commande cut
// la sortie de cut va dans le tube1 pour aller à la commande sed
// la sortie de sed va dans le tube2 pour aller à la commande sort
// la sortie de sort va dans le fichier "users"
void exercice_3() {
    // Exercice 3 //
    int tube1[2];
    int res1 = pipe(tube1);

    int tube2[2];
    int res2 = pipe(tube2);

    if (res1 == -1 || res2 == -1){
        perror("Création Pipe");
        exit(-1);
    }

    pid_t child_pid = fork();

    if (child_pid == -1){
        perror("fork");
        exit(1);
    }
    else if (child_pid == 0) { // Code exécuté par le fils
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(1);
        }
        else if (child_pid == 0) {
            int output = open("users", O_CREAT | O_WRONLY, 0644);
            
            // tout ce qui passe dans le stdout est redirigé vers le fichier "users"
            dup2(output, STDOUT_FILENO);
            close(output);

            close(tube2[1]);

            // le tube2 est l'entrée standard
            dup2(tube2[0], STDIN_FILENO);
            close(tube2[0]);
            close(tube1[1]);
            close(tube1[0]);
            execlp("sort", "sort", "-n", NULL);
        }
        else {
            close(tube1[1]);
            

            // le tube1 est l'entrée standard de la commande sed
            dup2(tube1[0], STDIN_FILENO);
            close(tube1[0]);

            close(tube2[0]);

            // le tube2 est la sortie standard de la commande sed
            dup2(tube2[1], STDOUT_FILENO);
            close(tube2[1]);
            execlp("sed", "sed", "s+^\\(.*\\):\\(.*\\)+\\2:\\1+", NULL);
        }
    }
    else {
        int input = open("/etc/passwd", O_RDONLY);

        // le fichier /etc/passwd est l'entrée standard de la commande cut
        dup2(input, STDIN_FILENO);
        close(input);

        close(tube1[0]);

        // le tube1 est la sortie standard de la commande cut
        dup2(tube1[1], STDOUT_FILENO);
        close(tube1[1]);
        close(tube2[1]);
        close(tube2[0]);
        execlp("cut", "cut", "-f", "1,3", "-d", ":", NULL);
    }
}

int main() {
    exercice_3();
    return 0;
}