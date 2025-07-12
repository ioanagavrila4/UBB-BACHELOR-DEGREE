//Scrieti un program C care genereaza N numere intregi aleatoate (N dat la linia de comanda). Apoi creeaza un proces fiu si ii trimite numerele prin pipe. Procesul fiu calculeaza media numerelor si trimite rezultatul inapoi parintelui.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
int main(int argc, char *argv[]){
    if(argc < 2){
        printf("lease put some arguments!!");
        exit(1);
    }

    int n = atoi(argv[1]);
    int medie = 0;
    int pipe_p_c[2];
    int pipe_c_p[2];
    pipe(pipe_p_c);
    pipe(pipe_c_p);
    int pid = fork();
    if(pid == -1){
        printf("Error on creating a child program!");
        exit(1);
    }else{
        if(pid == 0){
            //ne aflam in procesul copil - calculam media numerelor
            //in procesul copil - citim din p_c(inchidem scrierea)
            //scriem in c_p(inchidem citirea);
            //read 0 si write 1

            close(pipe_p_c[1]);
            close(pipe_c_p[0]);
            int n = 0, i, nr;

            float rez = 0;

            //prima oara il citim pe n
            if(read(pipe_p_c[0], &n, sizeof(int)) < 0){
                perror("Error on reading n from parent!!");
                close(pipe_p_c[0]);
                close(pipe_c_p[1]);
                exit(1);
            }
            //acum in n il avem pe n
            for(i = 0; i< n; i++){
                if(read(pipe_p_c[0], &nr, sizeof(int)) < 0){
                  perror("Error on reading a number from parent!!");
                  close(pipe_p_c[0]);
                  close(pipe_c_p[1]);
                  exit(1);
              }
                rez+=nr;
            }
            rez = rez/n;
            if(write(pipe_c_p[1], &rez, sizeof(float)) < 0){
                perror("Error on sending the number to parent!!");
                close(pipe_p_c[0]);
                close(pipe_c_p[1]);
                exit(1);

            }
            close(pipe_p_c[0]);
            close(pipe_c_p[1]);

            exit(1);
        }
        else{
        //ne aflam in procesul parinte
        close(pipe_p_c[0]);
        close(pipe_c_p[1]);
        if(write(pipe_p_c[1], &n, sizeof(int)) < 0){
            perror("Error on sending n to child!!");
            close(pipe_p_c[1]);
            close(pipe_p_c[0]);
            exit(1);
        }
        //l-a trimis pe n
        int nr;
        float rez;
        for(int i = 0; i < n; i++){
            nr = rand()%100;
            printf("numar random: %d\n", nr);
            if(write(pipe_p_c[1], &nr, sizeof(int)) < 0){
              perror("Error on sending nr to child!!");
              close(pipe_p_c[1]);
              close(pipe_p_c[0]);
              exit(1);
          }


        }
        if(read(pipe_c_p[0], &rez, sizeof(float)) < 0){
            perror("Error on reading rez to child!!");
            close(pipe_p_c[1]);
            close(pipe_p_c[0]);
            exit(1);
        }
        printf("The result: %f", rez);
        close(pipe_p_c[1]);
        close(pipe_p_c[0]);
        wait(0);
        }
    }
    return 0;
}

