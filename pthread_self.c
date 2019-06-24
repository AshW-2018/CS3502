#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void *myThread(void)
{
    pid_t pid;
    pthread_t tid;

    printf("thread pid %u tid %u \n",
            (unsigned int)getpid(), (unsigned int)pthread_self());
}


int main()
{
    int ret=0;
    pthread_t id1, id2;

    printf("This is main thread pid %u!\n", (unsigned int)getpid());

    ret = pthread_create(&id1, NULL, (void*)myThread, NULL);
    ret = pthread_create(&id2, NULL, (void*)myThread, NULL);
    if (ret)
    {
        printf("Create pthread error!/n");
        return 1;
    }

    pthread_join(id1, (void *)ret);
    pthread_join(id2, (void *)ret);


    pthread_exit(NULL);

    return 0;
}


