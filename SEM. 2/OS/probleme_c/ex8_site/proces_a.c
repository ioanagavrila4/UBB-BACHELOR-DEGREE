//Scrieti 2 programe C, A si B. A primeste un numar oarecare de argumente la linia de commanda si le trimite procesului B. B converteste toate literele mici in litere mari din argumentele primite si trimite rezultatul inapoi procesului A. A citeste rezultatele procesului B, le concateneaza si le afiseaza.
//
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Please put some arguments!");
        exit(1);
    }
    char *myfifo1 = "./myfifo1";
    if(mkfifo(myfifo1, 0600) < 0){
        perror("Error on creating a fifo");
        exit(1);
    }

    int i = 1;
    int f_write = open(myfifo1, O_WRONLY);
    if(-1 == f_write){
        perror("Error on opening a fifo");
        exit(1);
    }
    if(0>write(f_write, &argc, sizeof(int))){
        perror("Error on writing the argc to process B");
        exit(1);
    }

    if(0 > write(f_write, argv+1,argc*sizeof(char))){
        perror("Error on writing the argc to process B");
        exit(1);
    }
    if(0 > unlink(myfifo1)){
        perror("error on unlinking");
    }
    return 0;
    }
