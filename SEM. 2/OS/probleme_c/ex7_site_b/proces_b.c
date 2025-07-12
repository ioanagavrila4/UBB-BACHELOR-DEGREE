//acesta este al doilea proces pt ex 7
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
    char *myfifo1 = "./myfifo1";
    char *myfifo2 = "./myfifo2";
    int f_read = open(myfifo1, O_RDONLY);
    if(-1 == f_read){
        perror("Error for process B!!");
        exit(1);
    }
    int f_write = open(myfifo2, O_WRONLY);
    if(-1 == f_write){
        perror("Error on process B!");
        exit(1);
    }
    int nr = 0;
    while(nr != 10){
        if(read(f_read, &nr, sizeof(int)) < 0){
            perror("Error on reading\n");
            exit(1);
        }
        printf("PROCESS B REC: %d", nr);
        srand(time(NULL));
        nr = rand() % 10 + 1;
        if(write(f_write, &nr, sizeof(int)) < 0){
            perror("Error on writing in process B");
            exit(1);
        }
        printf("PROCESS B: %d\n", nr);


    }
    close(f_read);
    close(f_write);




    return 0;
}






























