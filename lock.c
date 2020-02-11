#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(void)
{
        int i = 0;
        int res;

        pthread_mutex_t lock;
        pthread_mutex_init(&lock, NULL);

        pthread_mutex_lock(&lock);
        if((res = pthread_mutex_lock(&lock) != 0)) {
                printf("don't lock\n");
        } else {
                printf("locked\n");
        }

        return 0;
}


