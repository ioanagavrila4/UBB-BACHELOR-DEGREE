#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
//A C program receives command line args pairs of numbers, and creates for each pair a thread that checks is the two numbers are relatively prime (gcd=1), incrementing a global variable. The program prints at the end how many relatively prime pairs have been found and the respective pairs.
typedef struct{
    int idx;
    int a;
    int b;
    pthread_mutex_t *mtx;
}data;
int final_number;
void* f(void* args)
{
    data d = *((data*)args);
    int result;
    int no1 = d.a;
    int no2 = d.b;
    result = ((no1<no2) ? no1:no2 );
    while(result > 0){
        if(no1%result == 0 && no2 %result == 0){
            break;
        }
        result--;
    }
    pthread_mutex_lock(d.mtx);
    if(result == 1)
    {
        final_number++;
    }
    pthread_mutex_unlock(d.mtx);

    return NULL;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Invalid number of arguments");
        exit(1);
    }
    if(argc % 2 != 1){
        perror("The number of arguments mudt be %2");
        exit(1);
    }
    int n = argc/2;
    pthread_t *th = malloc(sizeof(pthread_t)*n);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    data *args1 = malloc(sizeof(data)*n);
    int contor = 1;
    for(int i = 0; i < n; i++){
        int no1 = atoi(argv[contor]);
        contor++;
        int no2 = atoi(argv[contor]);
        contor++;
        args1[i].idx = i;
        args1[i].a = no1;
        args1[i].b = no2;
        args1[i].mtx = mtx;
        if(0!=pthread_create(&th[i], NULL, f, &args1[i])){
            perror("ERROR ON CREATING THE THREAD");
            exit(1);
        }

    }
    for(int j = 0; j < n; j++){
        pthread_join(th[j], NULL);
    }
    printf("THE NUMBER OF PAIRS WITH GCD = 1 IS: %d\n", final_number);
    free(th);
    free(mtx);
    free(args1);



    return 0;
}
