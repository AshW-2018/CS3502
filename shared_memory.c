#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

void* create_shared_memory(size_t size) {
      int protection = PROT_READ | PROT_WRITE;
      int visibility = MAP_ANONYMOUS | MAP_SHARED;
      return mmap(NULL, size, protection, visibility, -1, 0);
}

int main() {
    char* parent_message = "1111";  // parent process will write this message
    char* child_message = "2222";    // child process will then write this one

    void* shmem = create_shared_memory(128);
    memcpy(shmem, parent_message, sizeof(parent_message));  //copy parent to shared memory

    int pid = fork();

    if (pid == 0) {   //child process
        printf("Child read: %s\n", shmem);
        memcpy(shmem, child_message, sizeof(child_message));   //copy child to shared memory
        printf("Child wrote: %s\n", shmem);

    } else {    //parent process
        printf("Parent read: %s\n", shmem);
        sleep(5);
        printf("After 5s, parent read: %s\n", shmem);
    }
}


