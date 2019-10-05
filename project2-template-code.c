#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int num[3];

void *myThread(void *threadid)
{
    int i = (int)threadid;
    num[i] = i;
    pthread_exit(NULL);
}


int main()
{
    int rc, t=0;
    pthread_t threads[3];

    for(t=0; t<3; t++){
         rc = pthread_create(&threads[t], NULL, myThread, (void *) (size_t)t);
         if (rc){
                   printf("ERROR; return code from pthread_create() is %d\n", rc);
                   exit(1);
         }
    }

    for(t=0; t<3; t++){
          pthread_join(threads[t], NULL);
    }

    for(t=0; t<3; t++) {
        printf("num:%d\n", num[t]);
    }
    return 0;
}


