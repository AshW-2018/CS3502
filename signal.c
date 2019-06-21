#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void int_handler(int signum)
{
    printf("\nSIGINT signal handler.\n");
    printf("exit.\n");
    exit(-1);
}

int main()
{
    signal(SIGINT, int_handler);
    printf("int_handler set for SIGINT\n");

    while(1)
    {
        printf("go to sleep.\n");
        sleep(60);
    }

    return 0;
}


