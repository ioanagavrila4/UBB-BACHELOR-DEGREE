#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct{
    int idx;
    int ID;
    pthread_mutex_t *mtx;
    pthread_cond_t *cond;
    int *flag; //0-cand ii f si 1-cand e g
}data;
void *g(void* args){
    data *d = (data*)args;
    while(1){
        pthread_mutex_lock(d->mtx);
        while(*(d->flag) != 0){
            pthread_cond_wait(d->cond, d->mtx);
        }
            pthread_t s = pthread_self();
            printf("THE FIRST ID: %llu\n", (unsigned long long)s);
            *(d->flag) = 1;
            pthread_cond_signal(d->cond);
            pthread_mutex_unlock(d->mtx);


    }
    return NULL;
}
void* f(void* args){
    data *d = (data*)args;
    while(1){
        pthread_mutex_lock(d->mtx);
        while(*(d->flag) != 1){
            pthread_cond_wait(d->cond, d->mtx);

        }
        *(d->flag) = 0;
        pthread_t s = pthread_self();
        printf("THE SECOND ID: %llu\n", (unsigned long long)s);
        pthread_cond_signal(d->cond);
        pthread_mutex_unlock(d->mtx);

    }
    return NULL;
}
int main(int argc, char *argv[]){
    pthread_t *T = malloc(sizeof(pthread_t)*2);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_cond_t *cond = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(cond, NULL);
    pthread_mutex_init(mtx, NULL);
    data *arg = malloc(sizeof(data)*2);

    int *shared_flag = malloc(sizeof(int));
    *shared_flag = 0;
    arg[0].idx = 0;
    arg[0].mtx = mtx;

    arg[0].flag = shared_flag;
    arg[0].cond = cond;
    arg[1].idx = 1;
    arg[1].cond = cond;

    arg[1].flag = shared_flag;
    arg[1].mtx = mtx;
    pthread_create(&T[0], NULL, f, &arg[0]);
    pthread_create(&T[1], NULL, g, &arg[1]);



    for(int i = 0; i < 2; i++){
        pthread_join(T[i], NULL);
    }
    free(arg);
    free(T);
    free(mtx);
    free(cond);
    return 0;
}
