#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <wchar.h>
#include <locale.h>

sem_t remain, apple, pear, mutex;
static unsigned int nremain = 3, napple = 0, npear = 0;

void *father(void *);
void *mather(void *);
void *son(void *);
void *daughter(void *);

int main() {
    pthread_t fa, ma, so, da;
    setlocale(LC_ALL, "en_US.utf8");

    sem_init(&remain, 0, 3);
    sem_init(&apple, 0, 0);
    sem_init(&pear, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&fa, NULL, &father, NULL);
    pthread_create(&ma, NULL, &mather, NULL);
    pthread_create(&so, NULL, &son, NULL);
    pthread_create(&da, NULL, &daughter, NULL);

    for(;;);
}

void *father(void *arg) {
    while(1) {
        sem_wait(&remain);
        sem_wait(&mutex);
        printf("father  %lc: before put apple, remain=%u, apple=%u, pear=%u\n",   0x1F468, nremain, napple, npear);
        nremain--;
        napple++;
        printf("father  %lc: after  put apple, remain=%u, apple=%u, pear=%u\n\n", 0x1F468, nremain, napple, npear);
        sem_post(&mutex);
        sem_post(&apple);
        sleep(5);
    }
}

void *mather(void *arg) {
    while(1) {
        sem_wait(&remain);
        sem_wait(&mutex);
        printf("mother  %lc: before put pear , remain=%u, apple=%u, pear=%u\n", 0x1F469, nremain, napple, npear);
        nremain--;
        npear++;
        printf("mother  %lc: after  put pear , remain=%u, apple=%u, pear=%u\n\n",0x1F469,  nremain, napple, npear);
        sem_post(&mutex);
        sem_post(&pear);
        sleep(7);
    }
}

void *son(void *arg) {
    while(1) {
        sem_wait(&pear);
        sem_wait(&mutex);
        printf("son     %lc: before eat pear , remain=%u, apple=%u, pear=%u\n", 0x1F466, nremain, napple, npear);
        nremain++;
        npear--;
        printf("son     %lc: after  eat pear , remain=%u, apple=%u, pear=%u\n\n", 0x1F466, nremain, napple, npear);
        sem_post(&mutex);
        sem_post(&remain);
        sleep(10);
    }
}

void *daughter(void *arg) {
    while(1) {
        sem_wait(&apple);
        sem_wait(&mutex);
        printf("daughter%lc: before eat apple, remain=%u, apple=%u, pear=%u\n", 0x1F467, nremain, napple, npear);
        nremain++;
        napple--;
        printf("daughter%lc: after  eat apple, remain=%u, apple=%u, pear=%u\n\n", 0x1F467, nremain, napple, npear);
        sem_post(&mutex);
        sem_post(&remain);
        sleep(10);
    }
}



