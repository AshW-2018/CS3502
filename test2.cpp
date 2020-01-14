#include <iostream>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
using namespace std;

size_t physical_memory_used_by_process()
{
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != nullptr) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            int len = strlen(line);

            const char* p = line;
            for (; std::isdigit(*p) == false; ++p) {}

            line[len - 3] = 0;
            result = atoi(p);

            break;
        }
    }
    fclose(file);

    return result;
}

int main()
{
    int *p = new int;
    *p = 100;
    while(1) {
            cout << getpid() << ", Current memory usage: " << physical_memory_used_by_process() << ", " << p << ", " << *p << endl;
        sleep(1);
    }
    return 0;
}