#include "pthread_barrier.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
typedef struct{
    int idx;
    int m;
    pthread_mutex_t *mtx;
    pthread_barrier_t *bar;
}data;

void *f(void *args){
    data p = *((data*)args);
    int i;
    printf("Thread %d is waiting..\n", p.idx);
    pthread_barrier_wait(p.bar);
    for(i = 0; i <p.m; i++){
        pthread_mutex_lock(&p.mtx[i]);
        printf("The thread %d has entered the checkpoint %d\n", p.idx, i);
        usleep(1500);

        pthread_mutex_unlock(&p.mtx[i]);

    }
    printf("Thread %d has finished\n", p.idx);
    return NULL;

}
int main(int argc, char *argv[]){
    int n, m;
    printf("Please type the value for n: \n");
    scanf("%d", &n);
    printf("Please type the value for m: \n");
    scanf("%d", &m);
    //creare thread-uri
    pthread_t *T = malloc(sizeof(pthread_t)*n);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t)*m);//o sa am M asteptari practic
    pthread_barrier_t bar;
    if(0 > pthread_barrier_init(&bar, NULL, n)){
        perror("error on creating the barier");
        exit(1);
    }
    int i = 0;
    for(i = 0;i < m; i++){
        if(0 > pthread_mutex_init(&mtx[i], NULL)){
            perror("error on creating one mutex");
            exit(1);
        }
    }

    data *arg = malloc(sizeof(data)*n);
    for(int i = 0; i < n; i++){
        arg[i].idx = i;
        arg[i].m = m;
        arg[i].mtx = mtx;
        arg[i].bar = &bar;
        if(0 > pthread_create(&T[i], NULL, f, &arg[i])){
            perror("error on creating the threads");
            exit(1);
        }

    }
    int j = n;
    for(j = 0; j < n; j++){
        pthread_join(T[j], NULL);
    }
    free(arg);
    free(T);
    free(mtx);
    return 0;
}
