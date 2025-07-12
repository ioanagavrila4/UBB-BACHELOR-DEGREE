#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int *arr;
int n;
pthread_barrier_wait_t bar;
void *f(void *arg){
    int index = *((int*) arg);
    arr[index] = rand() %10;
    free(arg);
    //wait until all other thread populate array position
    int *rez = malloc(sizeof(int)*n);
    //bariera - are nevoie de counter care de fiecare data cand un thread ajunge sa loveasca bariera, scade;
    pthread_barrier_wait(&bar);
    for(int i = 0; i < n; i++){
        rez[i] = arr[n-i-1];
    }
    for(int i = 0; i < n; i++){
        printf("%3d", rez[i]);
    }
    free(rez);
    return NULL;
}
int main(int argc, char *argv[]){
    n = 10;
    pthread_t th[100];
    arr = malloc(sizeof(int)*n);
    pthread_barrier_init(&bar, NULL, n);
    for(int i = 0; i< n; i++){
        //int *tmp = malloc(sizeof(int));
        //tmp = i
        pthread_create(&th[i], NULL, f, (void *)i);

    }
    pthread_barrier_destroy(&bar);

    return 0;
}
