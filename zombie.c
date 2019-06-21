#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid = fork();

    // Parent process
    if (child_pid > 0) {
            printf("parent process pid:%d\n", getpid());
//        wait(NULL);
        sleep(100);
            printf("parent is stopped!\n");
    }
    // Child process
    else {
        printf("child process pid:%d\n", getpid());
        exit(0);
    }

    return 0;
}




