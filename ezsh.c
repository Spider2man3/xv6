// ezsh.c
#include "types.h"
#include "user.h"

int getWords(char *base, char target[10][10])
{
	int n=0,i,j=0;
	base[strlen(base) - 1] = ' ';
	for(i=0;i < strlen(base);i++)
	{
		if(base[i]!=' '){
			target[n][j++]=base[i];
		}
		else{
			target[n][j++]='\0';
			n++;
			j=0;
		}
		if(base[i]=='\0')
		    break;
	}
	if (n == 0 && i > 0)
	    n++;
	return n;
	
}

int main(int argc, char* argv[]) {
    static char buff[100];
    int buffSize = sizeof(buff);
    int pid;
    char cmdHistory[1000];
    int cmdIndex[100]; // Stores the start of each command in history
    int lineNumber = 0;
    int pos = 0;
    
    while (1) {
        // Step 1: print out line numbers
        printf(1, "%d EZ$ ", lineNumber);
        memset(buff, 0, buffSize);
        gets(buff, buffSize);
        int i;
        
        // Exit commands
        if ((buff[0] == 'e' && buff[1] == 'x' && buff[2] == 'i' && buff[3] == 't') || 
            (buff[0] == 'q' && buff[1] == '(' && buff[2] == ')')) {
            printf(1, "exiting ezsh...\n");
            break;
            exit();
        }
        
        // Step 3: change directory, it can only be done in the current directory
        //     and only be done by the parent, so it has to be in the same file
        else if(buff[0] == 'c' && buff[1] == 'd' && buff[2] == ' '){
         // Chdir must be called by the parent, not the child.
            buff[strlen(buff)-1] = 0;  // chop \n
            if(chdir(buff+3) < 0)
                printf(2, "cannot cd %s\n", buff+3);
            continue;
        }
        
        // Step 4: Read from history according to line numbers, 
        //     only if the line numbers exist
        else if (buff[0] == '#') {
            int dec = 0;
            buff[0] = '0';
            for (i = 0; i < (strlen(buff) - 1); i++){
		        dec = dec * 10 + ( buff[i] - '0' );
	        }
	        if (dec >= lineNumber) {
	            printf(2, "index does not exist\n");
	        }
	        else {
	            int size = cmdIndex[dec + 1] - cmdIndex[dec];
	            for (i = 0; i < size; i++) {
	                buff[i] = cmdHistory[cmdIndex[dec] + i];
	            }
	        }
        }
        
        // Step 2 & 5: Create a fork and check to see if it ends in an &,
        //    it will continue without waiting for a reply
        pid = fork();
        int amp = 0;
        if (pid == 0) {
            char arguments[10][10];
            if (buff[strlen(buff) - 2] == '&') {
                buff[strlen(buff) - 2] = ' ';
                amp = 1;
            }
            
            i = getWords(buff, arguments);
            char *array[10];
            int j;
            for (j = 0; j < i; j++) {
                array[j] = arguments[j];
            }
            exec(array[0], array);
            exit();
        }
        if (amp == 0) {
            wait();
        }

        // Step 4: Store the inputs into history
        cmdIndex[lineNumber] = pos;
        for (i = 0; i < (strlen(buff) -1); i++) {
            cmdHistory[pos] = buff[i];
            pos++;
        }
        cmdIndex[lineNumber + 1] = pos;
        printf(1, "\n");
        
        lineNumber++;
    }
    exit();
    return 0;
}