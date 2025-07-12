//acesta este primul proces pt ex 7
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
//Scrieti 2 programe C care comunica prin fifo. Cele doua procese isi vor trimite alternant unul celuilalt numere intre 1 si 10 (inclusiv) pana cand unul din ele trimite numarul 10. Afisati mesaje pe masura ce se trimit numere. Unul dintre procese va fi responsabil pentru crearea si stergerea canalelor fifo.



int main(int argc, char *argv[]){
    char *myfifo1 = "./myfifo1";
    char *myfifo2 = "./myfifo2";
    if(0 > mkfifo(myfifo1, 0600)){
        perror("Error on making the fifo 1!");
        exit(1);
    }
    if(0 > mkfifo(myfifo2, 0600)){
        perror("Error on making the fifo 1!");
        exit(1);
    }
    //ai nevoie de doua fifo uri pentru ca FIFO este UNIDIRECTIONAL!!!!
    int f_write = open(myfifo1, O_WRONLY);
    if(-1 == f_write){
        perror("Error on opening fifo in process A!");
        exit(1);
    }
    int f_read = open(myfifo2, O_RDONLY);
    if(f_read == -1){
        perror("Error on opening fifo in process A!");
        exit(1);
    }
    srand(time(NULL));
    int nr;
    while(nr != 10){
        nr = rand() %10+1;
        if(0>write(f_write, &nr, sizeof(int))){
            perror("Error on writing from process A!");
            exit(1);
        }
        printf("PROCESS A: %d\n", nr);
        if(0 > read(f_read, &nr, sizeof(int))){
            perror("Error on reading in process A!");
            exit(1);
        }
        printf("A RECEIVED.\n");
    }
    close(f_read);
    close(f_write);
    if(0 > unlink(myfifo1)){
        perror("Error on removing fifo 1");
    }
    if(0 > unlink(myfifo2)){
        perror("Error on removing fifo 2");
    }
    return 0;
}


















