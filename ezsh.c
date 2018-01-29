// ezsh.c
#include "types.h"
#include "user.h"

struct execcmd {
  char *argv[10];
};

int getWords(char *base, char target[10][10])
{
	int n=0,i,j=0;
	
	for(i=0;i < strlen(base);i++)
	{
		if(base[i]!=' '){
			target[n][j++]=base[i];
		}
		else{
			target[n][j++]='\0';//insert NULL
			n++;
			j=0;
		}
		if(base[i]=='\0')
		    break;
	}
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
        // Step 1
        printf(1, "%d EZ$ ", lineNumber);
        memset(buff, 0, buffSize);
        gets(buff, buffSize);
        int i;
        
        if ((buff[0] == 'e' && buff[1] == 'x' && buff[2] == 'i' && buff[3] == 't') || 
            (buff[0] == 'q' && buff[1] == '(' && buff[2] == ')')) {
            printf(1, "exiting ezsh...\n");
            break;
        }
        
        // Step 3
        else if(buff[0] == 'c' && buff[1] == 'd' && buff[2] == ' '){
         // Chdir must be called by the parent, not the child.
            buff[strlen(buff)-1] = 0;  // chop \n
            if(chdir(buff+3) < 0)
                printf(2, "cannot cd %s\n", buff+3);
            continue;
        }
        
        // Step 4
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
	            char text[size];
	            for (i = 0; i < size; i++) {
	                text[i] = cmdHistory[cmdIndex[dec] + i];
	            }
	            printf(1, "%s\n", text);
	        }
	        buff[0] = '#';
        }
        
        // Step 2
        pid = fork();
        if (pid == 0) {
            // char arguments[10][10];
            // i = getWords(buff, arguments);
            // char *rags = &arguments[0][0];
            // char **ragss = &rags;
            // printf(1, "%s %s\n", rags[0], ragss[0]);
            // exec(ragss[0], ragss);
            // int j;
            
            // for (j = 0; j < i; j++) {
            //     rags[j][0] = &arguments[j][0];
            // }
            struct execcmd *cmd;
            cmd = malloc(sizeof(*buff));
            memset(cmd, 0, sizeof(*cmd));
            
            struct execcmd *ecmd;
            ecmd = (struct execcmd*)cmd;
            printf(1, "%s %s\n", cmd->argv[0], ecmd->argv[0]);
            exec(ecmd->argv[0], ecmd->argv);
        }
        wait();

        // Step 4
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