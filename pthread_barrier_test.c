#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* task(void* param) {
        long id = (long) param;
        printf("step 1   %ld\n", id);
        printf("step 2   %ld\n", id);
        printf("step 3   %ld\n", id);
}

int main() {
        int nThread = 5;
        int i;

        pthread_t thread[nThread];
        printf("step Num ID\n");

        for (i = 0; i < nThread; i++)
                pthread_create(&thread[i], 0, task, (void *)(intptr_t)i);
        for (i = 0; i < nThread; i++)
                pthread_join(thread[i], 0);

        return 0;
}


