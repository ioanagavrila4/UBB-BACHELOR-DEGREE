#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    //Scrieti 2 programe C care comunica prin fifo. Programul A este responsabil pentru crearea/stergerea fifo. Programul A citeste comenzi de la tastatura, le executa si trimite rezultatul programului B. Programul B citeste din fifo si afiseaza tot ce primeste de la programul A. Programele continua pana cand programul A citeste "stop" de la tastatura.
    //pasul 1: cream fifo-ul
    char *fifo1 = "./fifo1";
//    if(0 > mkfifo(fifo1, 0600)){
  //      perror("Error on creating the fifo!");
    //    exit(1);
    //}
    //din A numai trimitem - avem nevoie de write
    //int f_write = open(fifo1, O_WRONLY);
    //if(0 > f_write){
      //  perror("Error on opening the fifo");
        //exit(1);
   // }
    //comenzile de la tastura moment
    //comenzile le executa prin exec - asa o sa consideram noi ; folosim execlp
    char comanda[100] = "ana";
    printf("%s", comanda);
    printf("Your command: ");
    scanf("%s", comanda);
    printf("%s", comanda);
    memset(comanda, 0, 100*sizeof(char));
    while(0!=strcmp(comanda, "stop")){
       memset(comanda, 0, 100*sizeof(char));
        printf("Your command: ");
        scanf("%s", comanda);
        printf("%s\n", comanda);
    }
    printf("The program will stop now: ");
    return 0;
}
