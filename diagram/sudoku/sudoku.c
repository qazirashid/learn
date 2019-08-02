#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int repl(void);
int main (void){
	repl();
}

int repl(){
	Grid g;
	Grid* gp = &g;
	initGrid(gp);
	printf("Entering REPL Loop: type 'quit' to exit.\n");
	char *cmd, *token1;
        char *nextarg;	
	size_t len=0;// tlen=0;
	ssize_t nread=0;
	int i=0, j=0, v=0;
	size_t i_read, j_read, v_read;
	char *iarg, *jarg, *varg;
	while(1){
		//printf("\nCMD$");
		nread = getline(&cmd, &len, stdin);
		if(nread<=1)
			continue;
		if(cmd == NULL)
			continue;
		//printf("nread=%zd, CMD= %s\n",nread, cmd);
		token1 = strtok(cmd, " \n");
		if(token1 == NULL) 
			continue;
		//tlen = strlen(token1);

		//printf("Token1=%s\n", token1);	
		
		//printf("strcmp returned %d\n", strncmp(token1, "quit", tlen));
		
		//'quit' or 'exit' instructions cause interpreter to exit.
		if(strcmp(token1,"quit") == 0){
			//instruction to exit interpreter
			break;
		}
		if(strcmp(token1,"exit") == 0){
			break;
		}
		//Ignore comments
		if(strncmp(token1,"#/",1) == 0){
			//a comment line. Ignore it.
			continue;
		}
		if(strncmp(token1,"print",3) == 0){
			//instruction to print information
			nextarg = strtok(NULL," \n");	
			if(nextarg == NULL){
				printMatrix(gp->Output);
				continue;
			}else if(strncmp(nextarg,"s",1)==0){
				printMatrix(gp->Status);
				continue;
			}else{
				printChoice(gp->Choice);
				continue;
			}
		}
		if(strncmp(token1,"set",3)==0){
			//instruction to set cell value
			//char *iarg, *jarg, *varg;
		       	iarg= strtok(NULL, " \n");
		       	jarg= strtok(NULL, " \n");
		       	varg= strtok(NULL, " \n");
			
			if(iarg == NULL || jarg==NULL || varg==NULL) 
				continue; //instruction to set expects three arguments. x-coordinate, y-coordinate, value to be set.
			i_read = sscanf(iarg, "%d", &i);	
			j_read = sscanf(jarg, "%d", &j);	
			v_read = sscanf(varg, "%d", &v);
			if(i_read == 0 || j_read == 0 || v_read ==0)
				continue; // three args of set instruction were read, but could not be parsed as ints.
			setCellValue(gp, i, j, v);	
		}
	
		if(strncmp(token1,"choice", 3) == 0){
			//prints the number of legal choices for Cell(i,j)
		       	iarg= strtok(NULL, " \n");
		       	jarg= strtok(NULL, " \n");
			
			if(iarg == NULL || jarg==NULL) 
				continue;
			i_read = sscanf(iarg, "%d", &i);	
			j_read = sscanf(jarg, "%d", &j);	
			if(i_read == 0 || j_read == 0)
				continue;
			printf("number of choices for Cell(%d,%d) = %d\n", i,j, getNumChoices(gp, i, j));	
		}
		if(strncmp(token1,"getchoice", 6)==0){
			//prints a legal choices for Cell(i,j)
		       	iarg= strtok(NULL, " \n");
		       	jarg= strtok(NULL, " \n");
			
			if(iarg == NULL || jarg==NULL) 
				continue;
			i_read = sscanf(iarg, "%d", &i);	
			j_read = sscanf(jarg, "%d", &j);	
			if(i_read == 0 || j_read == 0)
				continue;
			int c=getAChoice(gp, i, j);
			if(c == -1){
				printf("Cell is either already set or there is no legal choice left\n");
			}else
			printf("A legal choice for Cell(%d,%d) = %d\n", i,j, c);	
		}

			
	}
	return(0);
}
