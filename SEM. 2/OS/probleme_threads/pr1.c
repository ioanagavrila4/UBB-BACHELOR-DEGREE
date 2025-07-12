#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct{
    int idx;
    int *potato;
    pthread_mutex_t *m;
}data;
void *f(void *a){
      data *d = (data*)arg;
      while(1){
        pthread_mutex_lock(d->m);
        if(*(d->potato) < 0){
            break;
        }
        *(d->potato) -=rand()%91 + 10;
        if(*(d->potato) < 0){
            printf("Thread with id %d has expload", d->idx);
        }

        pthread_mutex_unlock(d->m);
      }
      return NULL;
}
int main(int argc, char *argv[]){
    int n = atoi(argv[1]);
    srandom(time(0));
    int potato = rand() % 9001 + 10000;
    int a[10000];
    pthread t[10000];
    data *args = malloc(sizeof(data)* n);
    int i;
    pthread_mutex m;
    pthread_mutex_init(&m, NULL);
    for(i = 0; i < n; i++){
       args[i].idx = i+1;
       args[i].potator = &potato;
       args[i].m =
        pthread_create(&t[i], NULL, f, (void*)&args[i]);
    }

    for(i = 0; i < n; i++){
        pthread_join(t[i], NULL);

    }
    pthread_mutex_destroy(&m);
    return 0;
}
