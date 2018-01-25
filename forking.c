#include “types.h”
#include “user.h”

int main(int argc, char* argv[]) {
    uint fork_answer;
    fork_answer = fork();
    printf(1, “Hello! Fork answered %d\n”, fork_answer);
    if (fork_answer == 0) {
        printf(1, “This is a child process\n”);
    }
    else {
        printf(1, “This is a parent process\n”);
    }
    exit();
    return 0;
}