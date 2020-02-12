/* compile: gcc xxx.c -o xxx.o -pthread  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int iCount = 0;
static pthread_mutex_t mlock;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1_work(void *id) {
        long tid = (long)id;
        while (1) {
                pthread_mutex_lock(&mlock);
                iCount++;
                printf("thread: %ld iCount: %d\n", tid, iCount);
                pthread_mutex_unlock(&mlock);

                pthread_mutex_lock(&mlock);
                if (iCount >= 100) {
                        pthread_cond_signal(&cond);
                        printf("thread: %ld iCount: %d\n", tid, iCount);
                }
                pthread_mutex_unlock(&mlock);
                sleep(1);
        }
}

void *thread2_work(void *id) {
        long tid = (long)id;
        while (1) {
                pthread_mutex_lock(&mlock);
                if (iCount < 100) {
                        pthread_cond_wait(&cond, &mlock);
                }
                iCount = 0;
                printf("thread: %ld iCount: %d\n", tid, iCount);
                pthread_mutex_unlock(&mlock);
                sleep(1);
        }
}



int main() {
        pthread_t thread1, thread2;
        int id1=1, id2=2;
        if (pthread_mutex_init(&mlock, NULL) != 0) {
                printf("mutex init failed\n");
                return 1;
        }

        pthread_create(&thread1, NULL, thread1_work, (void *)(intptr_t)id1);
        pthread_create(&thread2, NULL, thread2_work, (void *)(intptr_t)id2);

        pthread_exit(NULL);
        pthread_mutex_destroy(&mlock);
        exit(0);
}
