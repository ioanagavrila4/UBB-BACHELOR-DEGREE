#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>
int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Please provide some atguments!");
        exit(1);
    }

    int i = 1;
    while(i < argc){
        int p[2];
        pipe(p);
        int mes;
        int val = fork();
        if(val == 0){
            if(execlp(argv[i], argv[i], NULL)==-1){

                close(p[0]);
                mes=0;
                write(p[1], &mes, sizeof(int));
                close(p[1]);
                exit(0);
            }
        }else{

            close(p[1]);
            if( read(p[0], &mes, sizeof(int)) != 0){
                if(mes == 0){
                    printf("Unable to run the arg: %s\n", argv[i]);
                    printf("\nChild %d\n", val);
                }
            }
        }
        close(p[0]);

        wait(0);

        i++;
    }

    return 0;
}
