#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
typedef struct{
    int idx;
    pthread_mutex_t *m;
    FILE *p;
}data;
typedef struct{
    int no_lines;
    int words;
    int no_charac;
}rez;
int nl, nc, nw;
void *func(void *arg){
    data d = *((data*) arg);
    pthread_mutex_lock(d.m);
    char line[256];
    if(fgets(line, sizeof(line), d.p) == NULL){
        if (ferror(d.p)){

        }
        nl = nl+1;
        perror("error on reading");
        pthread_mutex_unlock(d.m);
    }
    int i = 0, no_ch, no_words;
    no_ch = 0;
    no_words = 0;
    printf("%s\n", line);
    while(line[i]){
        if(' '== line[i]){
            no_words=no_words+1;
        }
        no_ch += 1;
        i++;

    }
    printf("%d no of words, %d no of charac - \n", no_words, no_ch);
    if(no_words >0){
        no_words = no_words + 1;
    }
    nc = nc + no_ch;
    nw = nw + no_words;
    pthread_mutex_unlock(d.m);
    return NULL;

}
int main(int argc, char *argv[]){
    if(argc < 1){
        perror("Invalid number of arguments");
        exit(1);
    }
    FILE *fp;
    fp = fopen(argv[2], "read");
    if(!fp){
        perror("error on opening");
        exit(1);
    }

    int n = atoi(argv[1]);
    pthread_mutex_t *m = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(m, NULL);
    pthread_t *T = malloc(sizeof(pthread_t)*n);
    data *args = malloc(sizeof(data)*n);
    for(int i = 0; i < n; i++){
        args[i].idx = i;
        args[i].m = m;
        args[i].p = fp;
        if(0 != pthread_create(&T[i], NULL, func, (void *) &args[i])){
            perror("error on creating the thread");
            exit(1);
        }

    }
    for(int j = 0; j <  n; j++){
        pthread_join(T[j], NULL);
    }
    printf("%d \n %d\n %d\n", nl, nw, nc);

    return 0;
}
