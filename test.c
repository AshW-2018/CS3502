#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

unsigned int X = 0;

void Worker(void *pParam)
{
    X++;
}


int main()
{
    pthread_t MultiHandle       = 0;
    unsigned int    i           = 0;
    signed   int    index       = 0;

    for (i = 0; i < 100; i ++)
    {
        index = pthread_create(&MultiHandle, NULL, (void * (*)(void *))(&Worker), (void *)i);
        if (0 != index)
        {
            printf("Create Worker %d failed!\n", i);
            return -1;
        }
    }

    sleep(3);

    printf("In main, X = %d\n", X);

    return 0;
}



