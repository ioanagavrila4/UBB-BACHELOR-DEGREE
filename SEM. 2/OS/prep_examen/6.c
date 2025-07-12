#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *pipe_fp;

    // Deschide pipe către comanda "wc -l" în modul write
    pipe_fp = popen("wc -l", "w");

    if (pipe_fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    // Trimite string-ul către wc -l
    fprintf(pipe_fp, "Hello\nWorld\n");

    // Închide pipe-ul (important pentru a trimite EOF către wc)
    int status = pclose(pipe_fp);

    if (status == -1) {
        perror("pclose failed");
        exit(EXIT_FAILURE);
    }

    printf("Command completed successfully\n");

    return 0;
}
