#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
//Scrieti un program C care creeaza doua procese fiu. Cele doua procese isi vor trimite alternativ numere intregi intre 1 si 10 (inclusiv) pana cand unul din ele trimite numarul 10. Afisati mesaje pe masura ce numerele sunt trimise.

int main(int argc, char *argv[]){
    int pipe_1_2[2];
    int pipe_2_1[2];
    if(pipe(pipe_1_2) < 0 || pipe(pipe_2_1) < 0){
        perror("Error on pipes!");
        exit(1);
    }
    int fiu_1=fork();
    if(fiu_1 == -1){
        perror("Error on creating the two processes!");
        exit(1);
    }
    else if(fiu_1 == 0){
    //ne aflam in procesul fiu 1
    //de aici citim din pipe_2_1 si scriem in pipe_1_2
    int nr;
    srand(time(NULL));
    nr = rand()%10+1;
    printf("The number that will be send from child f_1 to child f_2: %d\n", nr);
    close(pipe_1_2[0]);
    close(pipe_2_1[1]);
    if(write(pipe_1_2[1], &nr, sizeof(int)) < 0){
          perror("Error on sending the number to f2");
          exit(1);
      }
    while(1){
    if(read(pipe_2_1[0], &nr, sizeof(int)) < 0){
        perror("Error on reading the f2 number!!");
        exit(1);
    }
    if(nr== 10){
        printf("The game is at the ending...");
        break;
    }
    nr = rand()%10+1;
    printf("F1 TO F2: %d\n", nr);
    if(write(pipe_1_2[1], &nr, sizeof(int)) < 0){
            perror("Error on sending the number to f2");
            exit(1);
        }
    }
    close(pipe_1_2[1]);
    close(pipe_2_1[0]);
    exit(0);

    }

    int fiu_2=fork();
    if(fiu_2 == -1){
        perror("Error on creating fiu 2!!");
        exit(1);
    }
    if(fiu_2 == 0){
        int nr;
        srand(time(NULL));
        nr= rand()%10+1;
        printf("The number that will be send from child f_2 to child f_1: %    d\n", nr);
        close(pipe_2_1[0]);
        close(pipe_1_2[1]);
       while(1){
      if(read(pipe_1_2[0], &nr, sizeof(int)) < 0){
          perror("Error on reading the f2 number!!");
          exit(1);
      }

      if(nr == 10){
          printf("The game is at the ending...");
          break;
      }
      printf("F2 TO F1: %d\n", nr);
      if(write(pipe_2_1[1], &nr, sizeof(int)) < 0){
          perror("Error on sending the number to f2");
          exit(1);
      }

    }
       close(pipe_1_2[0]);
        close(pipe_2_1[1]);
        exit(0);

    }
    close(pipe_1_2[0]);
    close(pipe_1_2[1]);
    close(pipe_2_1[0]);
    close(pipe_2_1[1]);

    wait(NULL);
    wait(NULL);


    return 0;
}
