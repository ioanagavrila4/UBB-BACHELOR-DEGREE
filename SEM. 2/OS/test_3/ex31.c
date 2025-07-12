#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "pthread_barrier.h"
typedef struct{
    int idx;
    pthread_mutex_t *mtx;
    pthread_barrier_t *bar;
    int *flag; //daca e 0-genereaza; daca e 1 moare
}data;

void *f(void* args){
    data *p = (data*)args;
    pthread_barrier_wait(p->bar);
    int numar;
    while(1){
        numar = random()%111111;
        pthread_mutex_lock(p->mtx);
        if(*(p->flag) == 1){
            pthread_mutex_unlock(p->mtx);
            return NULL;
        }
        if(numar % 1001 == 0){
            *(p->flag) = 1;


        }
        printf("The number from %d generated: %d", p->idx, numar);

        pthread_mutex_unlock(p->mtx);

    }


    return NULL;
}
int main(int argc, char *argv[]){
    if(argc < 2){
        perror("invalid number of arguments!!");
        exit(1);
    }

    int n = atoi(argv[1]);
    pthread_t *T = malloc(sizeof(pthread_t)*n);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    pthread_barrier_t bar;
    pthread_barrier_init(&bar, NULL, n);
    data *arg = malloc(sizeof(data)*n);
    int i;
    int *flag = malloc(sizeof(int));
    *(flag) = 0;
    for(i = 0; i < n; i++){
        arg[i].idx = i;
        arg[i].mtx = mtx;
        arg[i].bar = &bar;
        arg[i].flag = flag;
        if(0!=pthread_create(&T[i], NULL, f, &arg[i])){
            perror("error on creating the threads");
        }

    }

    for(i = 0; i < n; i++){
        pthread_join(T[i], NULL);
    }
    free(arg);
    free(mtx);
    free(T);
    return 0;
}
