#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int repl(void);
int main (void){
	repl();
}

int repl(){
	Grid g;
	Grid* gp = &g;
	initGrid(gp);
	printf("Entering REPL Loop: type 'quit' to exit.\n");
	char* cmd;
        char* first;	
	size_t len=0;
	ssize_t nread=0;
	int i=0;
	while(1){
		printf("CMD$");
		nread = getline(&cmd, &len, stdin);
		printf("nread=%zd, CMD= %s\n",nread, cmd);
		nread = sscanf(cmd, "%ms ", &first);
		printf("nread=%zd, CMD= %s\n",nread, first);
		if(strcmp(first,"quit") == 0)
			return(0);
		if(strcmp(first,"print") == 0)
			printGrid(gp);

			
	}
	return(0);
}
