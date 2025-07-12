#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "pthread_barrier.h"
typedef struct{
    int idx;
    pthread_barrier_t *bar;
    pthread_mutex_t *mtx;
}data;
int sum;
void* fu(void* args){
    data d = *((data*)args);
    int n1, n2, n3;
    n1 = random()%11;
    n2 = random()%11;
    n3 = random()%11;
    printf("Thread %d generated: %d, %d, %d\n", d.idx, n1, n2, n3);
    pthread_barrier_wait(d.bar);
    pthread_mutex_lock(d.mtx);
    if(n1 % 2 == 1) sum = sum + n1;
    if(n2 % 2 == 1) sum = sum + n2;
    if(n3 % 2 == 1) sum = sum + n3;
    if(n1 % 2 == 0) sum = sum - n1;
    if(n2 % 2 == 0) sum = sum - n2;
    if(n3 % 2 == 0) sum = sum - n3;
    pthread_mutex_unlock(d.mtx);

    return NULL;
}
int main(int argc, char *argv[]){
    int n, i;
    if(argc < 2){
        perror("invalid number of arguments");
        exit(1);
    }
    n = atoi(argv[1]);
    pthread_t *T = malloc(sizeof(pthread_t)*n);
    pthread_barrier_t bar;
    pthread_barrier_init(&bar, NULL, n);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    data *arg = malloc(sizeof(data)*n);
    for(i = 0; i < n; i++){
        arg[i].idx = i;
        arg[i].bar = &bar;
        arg[i].mtx = mtx;
        if(0!= pthread_create(&T[i], NULL, fu, &arg[i])){
            perror("error on creating the threads");
            free(arg);
            free(mtx);
            free(T);
            exit(1);
        }
    }
    for(i = 0; i < n; i++){
        pthread_join(T[i], NULL);


    }
    printf("THE SUM IS: %d\n", sum);
    free(arg);
    free(mtx);
    free(T);
    return 0;
}
