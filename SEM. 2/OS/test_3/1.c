#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
//Write a program that creates 20 threads, giving each thread a string as parameter. Each thread will count and add to the global variables v and n as follows: the number of vowels contained by the string added to v, and the number of digits contained in the string added to n. Synchronise threads using mutex and check for memory leaks.
typedef struct {
    char text[29];
    int idx;
    pthread_mutex_t *mtx;
}data;
int v, n;
void* f(void *dat){
    data d = *((data*)dat);
    int vowels_count=0, digit_count=0;
    int i = 0;
    while(d.text[i]!=0){
        char c = tolower(d.text[i]);
        if(c=='a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            vowels_count++;
        }
        if(isdigit(d.text[i])){
            digit_count++;
        }
        i++;
    }

    pthread_mutex_lock(d.mtx);
    v+=vowels_count;
    n+=digit_count;
    pthread_mutex_unlock(d.mtx);

    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t *T = malloc(sizeof(pthread_t)*21);
    data *args = malloc(sizeof(data)*20);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);

    int i;
    char* test_strings[20] = {
    "Hello123World",          // 4 vowels, 3 digits
    "Programming456",         // 3 vowels, 3 digits
    "OpenAI789",             // 4 vowels, 3 digits
    "Computer2024Science",    // 6 vowels, 4 digits
    "DataStructures101",      // 5 vowels, 3 digits
    "Algorithm999",          // 4 vowels, 3 digits
    "Software42Engineering", // 7 vowels, 2 digits
    "Database555Query",      // 5 vowels, 3 digits
    "Network777Protocol",    // 5 vowels, 3 digits
    "Security888Test",       // 4 vowels, 3 digits
    "Thread333Sync",         // 1 vowel, 3 digits
    "Mutex111Lock",          // 2 vowels, 3 digits
    "Race222Condition",      // 5 vowels, 3 digits
    "Parallel666Computing",  // 5 vowels, 3 digits
    "Concurrent444Tasks",    // 5 vowels, 3 digits
    "Memory999Management",   // 5 vowels, 3 digits
    "Process888Control",     // 4 vowels, 3 digits
    "System777Call",         // 2 vowels, 3 digits
    "Buffer555Overflow",     // 4 vowels, 3 digits
    "Stack222Pointer"        // 2 vowels, 3 digits
};
    for(i=0; i < 20; i++){
        args[i].idx = i;

        strcpy(args[i].text, test_strings[i]);
        args[i].mtx = mtx;
        if(0!=pthread_create(&T[i], NULL, f, &args[i])){
            perror("Error on creating thread");
        }



    }

    for(int j = 0; j <20; j++){
        pthread_join(T[j], NULL);
    }
    printf("NUMBER OF VOWELS: %d\nNUMBER OF DIGITS: %d\n", v, n);
    pthread_mutex_destroy(mtx);
    free(mtx);
    free(T);
    free(args);


    return 0;
}
