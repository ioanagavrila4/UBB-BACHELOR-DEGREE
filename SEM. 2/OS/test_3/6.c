#include <ctype.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
//6. Write a C program that reads strings (words) from stdin until the word stop is given. For each string, the program will launch a thread that receives this string as argument and computes the number of vowels in the string. The thread will send this result as a return value to the main thread. The main thread will print each string and their number of vowels, as well as the total sum.

//Solve the problem without using global variables.

typedef struct{
    int idx;
    char text[100];
    int result;
}data;

void* f(void* args){
    data *d = (data*)args;
    int no_vowels = 0;

    for(int i = 0; d->text[i]; i++){
         char c = tolower(d->text[i]);
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){

        no_vowels++;
    }
    }
    d->result = no_vowels;
    return NULL;
}
int main(int argc, char *argv[]){
    pthread_t *T = malloc(sizeof(pthread_t)*1000);
    data *arg = malloc(sizeof(data)*1000);
    char str[100];
    int contor = 0;
    while(strcmp(str, "stop")){
        printf("Your string: \n");
        scanf("%s", str);
        contor++;
        printf("You typed: %s\n", str);
        arg[contor-1].idx = contor-1;
        strcpy(arg[contor-1].text, str);
        if(0!=pthread_create(&T[contor-1],NULL, f, &arg[contor-1])){
            perror("error on creating one thread");
            }

    }
    contor--;
    int total=0;
    for(int i = 0; i< contor; i++){
        pthread_join(T[i],NULL);
        total = arg[i].result + total;

    }

    printf("The total number of vowels is: %d\n", total);





    free(arg);
    free(T);
    return 0;
}
