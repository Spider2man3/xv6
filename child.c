#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int pid = fork();
    if (pid == 0) {
        printf(1, "Child process PID: 0\n");
        printf(1, "Child process exiting\n");
        exit();
    }
    else {
        printf(1, "Parent process PID: %d\n", pid);
        wait();
    }
    printf(1, "Parent process exiting\n");
    exit();
    return 0;
}