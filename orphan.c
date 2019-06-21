#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid = fork();

    // Parent process
    if (child_pid > 0) {
            printf("parent is stopped!\n");
        exit(0);
    }
    // Child process
    else {
        sleep(10);
        printf("child is stopped!");
    }

    return 0;
}



