#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
typedef struct{
    int idx;
    pthread_mutex_t *mtx;
    int *p;

}data;

typedef struct{
    int n1, n2, idx;
}response;
void *fu(void *args){
    data *d = (data*)args ;
    int n1 = random()%101;
    int n2 = random()%101;
    response r;
    r.n1 = n1;
    r.n2 = n2;
    r.idx = d->idx;
    printf("Thread %d has generated: %d, %d\n", d->idx, n1, n2);
    pthread_mutex_lock(d->mtx);
    if(0 > write(d->p[1], &r, sizeof(response))){
        perror("error on sending the response through pipe");
    }
    pthread_mutex_unlock(d->mtx);
    return NULL;

}
int main(int argc, char *argv[]){
    int n;
    if(argc < 1){
        perror("invalid number of arguments");
        exit(1);
    }
    n = atoi(argv[1]);
    int p[2];
    if(0 > pipe(p)){
        perror("error on creating the pipe");
        exit(1);
    }
    int f = fork();
    if(0 > f){
        perror("error on child");
        exit(1);
    }else if(0 == f){
        close(p[1]);
        int i;
        for(i = 0; i < n ;i++){
            response r;
            if(0 > read(p[0], &r, sizeof(response))){
                perror("error on reading");
            }
            double resp = (r.n1+r.n2)/2;
            printf("Thread %d - average: %f\n", r.idx, resp);
        }
        close(p[0]);
        exit(0);

    }else{
        //parinte
        close(p[0]);
        int i;
        pthread_t *T = malloc(sizeof(pthread_t)*n);
        pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init(mtx, NULL);
        data *arg = malloc(sizeof(data)*n);
        for(int i = 1; i < n; i++){
            arg[i].idx = i;
            arg[i].mtx = mtx;
            arg[i].p = p;
            if(0!=pthread_create(&T[i], NULL, fu, &arg[i])){
                perror("error on creating the threads");
                close(p[1]);
                wait(0);
                free(arg);
                free(mtx);
                free(T);
                exit(1);

            }
        }
        for(int i = 1; i < n; i++){
            pthread_join(T[i], NULL);

        }
        close(p[1]);
        wait(0);
        free(arg);
        free(mtx);
        free(T);

    }

    return 0;
}
