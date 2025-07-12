//Scrieti un program C care ruleaza o comanda bash (potential cu mai multe argumente) primita ca argument la linia de comanda si cronometreaza executia ei.
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Please put a valid number of arguments!!");
        exit(0);
    }
    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    int f = fork();
    if(f == -1){
        printf("Fork has an error!");
    }else{
        if(f == 0){

            //ne aflam in copil
            printf("NOW WE ARE IN THE CHILD: ");
            if(execvp(argv[1],argv+1)==-1){
                perror("ERROR ON RUNNING THE COOMMAND");
                exit(1);
            }
        } else{
            gettimeofday(&t2, NULL);
            double total = (double)(t2.tv_usec - t1.tv_usec)/1000000 + (double)(t2.tv_sec - t1.tv_sec);
            printf("%f", total);
            //ne aflam in parinte
            printf("Now we are in the parent");
            wait(0);

        }

    }
    return 0;
}
