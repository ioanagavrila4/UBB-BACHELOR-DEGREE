#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

typedef struct {

    int idx;

    int *potato;
    pthread_barrier_t *b;
    pthread_mutex_t *mtx;
    pthread_cond_t *c;
    int *flag;
} data;
//flag = 1 -> are nevoie de schimbare
int contor_alive=0;
void *parinte(void *arg){

    data *d = (data*) arg;
    while(d->flag != 1){
        pthread_cond_wait();
    }
        if(d->flag == 1){
            d->potato = rand() % 10000 + 100;
            d->flag = 0;
            pthread_cond_signal(d->flag);
        }

   return NULL;

}
void *f(void *arg) {

    data *d = (data*) arg;
    pthread_barrier_wait(d->b);
    while(d->flag != 1){
        pthread_cond_wait();
    }
    while(1) {

        pthread_mutex_lock(d->mtx);

        // *((*d).potato)

        if(*(d->potato) < 0) {

            pthread_mutex_unlock(d->mtx);
            d->flag = 1;
            pthread_cond_signal(d->flag);

            break;

        }

        int sub = rand() % 91 + 10;
        printf("Thread with id %d has subtracted %d from %d\n", d->idx, sub, *(d->potato));

        *(d->potato) -= sub;

        if(*(d->potato) < 0) {

            printf("Thread with id %d has exploded!\n", d->idx);

            pthread_mutex_unlock(d->mtx);
            d->flag = 1;
            pthread_cond_signal(d->flag);
            contor_alive--;
            break;

        }

        pthread_mutex_unlock(d->mtx);

        int sleep = rand() % 101 + 100;

        usleep(sleep * 1000);

    }
    return NULL;

}



int main(int argc, char *argv[]){

    if(argc != 2) {

        perror("Please provide exactly one argument!\n");

        exit(0);

    }

    int n = atoi(argv[1]);

    srand(getpid());

    int potato = rand() % 9001 + 1000;

    printf("Main has generated %d\n", potato);

    pthread_t th[n];

    data *args = malloc(sizeof(data) * n);
    pthread_cond_t c;
    pthread_cond_init(&c, NULL);
    pthread_mutex_t mtx;
    pthread_barrier_t b;
    pthread_barrier_init(&b, NULL, n+1);
    contor_alive = n;
    pthread_mutex_init(&mtx, NULL);
    data *args1;
    args1.idx = 0;
    args1.potato = &potato;
    args1.mtx = &mtx;
    args1.b = &b;
    args1.c = &c;
    pthread_create(&th[i], NULL, parinte, (void *) &args1);
    for(int i = 0; i < n; i++) {

        args[i].idx = i + 1;

        args[i].potato = &potato;

        args[i].mtx = &mtx;
        args[i].b = &b;
        args[i].c = &c;

        pthread_create(&th[i], NULL, f, (void *) &args[i]);

    }



    for(int i = 0; i < n; i++) {

        pthread_join(th[i], NULL);

    }

    pthread_mutex_destroy(&mtx);

    free(args);

    return 0;

}
