// ezsh.c
#include "types.h"
#include "user.h"

int main(int argc, char* argv[]) {
    static char buff[100];
    int buffSize = sizeof(buff);
    
    while (1) {
        printf(1, "EZ$ ");
        memset(buff, 0, buffSize);
        gets(buff, buffSize);
        if ((buff[0] == 'e' && buff[1] == 'x' && buff[2] == 'i' && buff[3] == 't') || buff[0] == 'q') {
            printf(1, "Exiting ezsh...\n");
            exit();
        }
        else {
            printf(1, "%s", buff);
        }
            
    }
    exit();
    return 0;
}