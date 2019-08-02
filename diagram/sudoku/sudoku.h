#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
#include <stdlib.h>
#define GBASE  3    //Base of the Grid. size of boxes in the grid.
#define GSIZE  GBASE*GBASE   // Number of rows and colums

/*************** Grid Data Structure ************/
typedef struct grid_t{
	int Status[GSIZE][GSIZE];
	int Output[GSIZE][GSIZE];
	int Choice[GSIZE][GSIZE][GSIZE];
} Grid;

/********* Function Declarations *************/
//Grid updaters
int initGrid(Grid* gp);
int setCellValue(Grid* gp, const int i, const int j, const int v);
int setCellAndPrint(Grid* gp, int i, int j, int value);
// Printers 
void printMatrix(const int m[GSIZE][GSIZE]);
void printGrid(const Grid* gp);
void printChoice(const int Choice[GSIZE][GSIZE][GSIZE]);
//Secondary helpers
int canContain(Grid g, int i, int j, int v);
int lowerBlockBound(int i);
int upperBlockBound(int i);
int getNumChoices(Grid* gp, int i, int j);
//getNumChoices returns the number of legal choices for Cell(i,j).
int getAChoice(Grid* gp, int i, int j);
//getAChoice returns lowest value legal choice for Cell(i,j).
//Just for tests
void printG(Grid * const g);
int readGridStr(char* string, Grid* gp); 
int isSolved(Grid* gp);

/***************** Helper Functions ***********************/
void printGrid(const Grid* gp){
		printf("Current Status is:\n");
		printMatrix(gp->Status);
		printf("Current Output is:\n");
		printMatrix(gp->Output);
		printf("Current Legal Choices are:\n");
		printChoice(gp->Choice);
	}

int setCellAndPrint(Grid* gp, int i, int j, int v){
	if (setCellValue(gp, i,j,v)){
		printGrid(gp);	
	}else 
		printf("Failed to Set Cell(%d, %d) to %d \n", i, j, v);
	return(1);
}

int initGrid(Grid* gp){ 
	int i=0, j=0, k=0;
	for(i=0; i<GSIZE; i++)
	       for(j=0; j<GSIZE; j++){
	       	gp->Status[i][j] = 0;
	      }
	for(i=0; i<GSIZE; i++)
	       for(j=0; j<GSIZE; j++){
	       	gp->Output[i][j] = 0;
	      }
	for(i=0; i<GSIZE; i++)
	       for(j=0; j<GSIZE; j++){
		       for(k=0; k< GSIZE; k++)
			       gp->Choice[i][j][k] = k; 
	      }
	return(1); // Sucesss

}

void printMatrix(const int m[GSIZE][GSIZE]){
	
	for(int i=0; i<GSIZE;i++){
		for(int j=0; j<GSIZE; j++){
	       		printf("%d ", m[i][j]);	
			if( (j+1) % GBASE == 0) printf("| ");
	      }
		printf("\n");
		if( (i+1) % GBASE == 0) printf("-----------------------\n");
	}

}

void printChoice(const int Choice[GSIZE][GSIZE][GSIZE]){
	
	for(int i=0; i<GSIZE; i++)
	       for(int j=0; j<GSIZE; j++){
		       printf("Cell(%d,%d) can potentially contain: ", i,j);
		       for(int k=0; k< GSIZE; k++){
			       int v = Choice[i][j][k];
			       if ( v != -1)
			       printf("%d ", Choice[i][j][k]) ;
		       }
		      printf("\n"); 
	      }	
	
}


int setCellValue(Grid* gp, const int i, const int j, const int v){
	// will attempt to set cell(i,j) value to v. On Success, returns 1. On failure returns 0. 
	// Failure occurs when the v is illegal in Cell(i,j).

	if((v<0) || (v >=GSIZE)){
		printf("setCellValue():invalid v was passed to setCellValue()");
		return(0); // invalid v was passed.

	}
	if(canContain((*gp), i,j,v)){
		// If v is legal in Cell(i,j), Then do all of the below
		// 1- set status of Cell(i,j)=1. this indicates that Cell has been occupied.
		gp->Status[i][j] = 1;
		// 2- set output of Cell(i,j)=v+1 (1 added because of C-index starting at 0. This indicates the output user will get. 
		gp->Output[i][j] = v;
		// 3- Set all of Choice[i][j][k] for (0<= k < GSIZE) to -1. This indicates that Cell is occupied. Next attempt to set it to some value will fail.
		for(int kr=0; kr<GSIZE;kr++)
			gp->Choice[i][j][kr] = -1;
		//4- For all Cells in the row i (0<=i<GSIZE), exclude v by setting Choice[i][j][v]=-1, because no further Cell in this row can be set to v.
		for(int ir=0; ir<GSIZE;ir++)
			gp->Choice[ir][j][v] = -1;
		//5- For all Cells in the column j (0<=j<GSIZE), exclude v by setting Choice[i][j][v]=-1, because no further Cell in the column can be set to v.
		for(int jr=0; jr<GSIZE; jr++)
			gp->Choice[i][jr][v] = -1;
		//6- For all Cells in the 3x3 block containing Cell(i,j), exclude v by setting Choice[b][c][v] ==0, because this block cannot contain v in any other Cell.
		// This is 2-D Loop. Calculate lower and upper bounds to contain (i,j) in the 3x3 box containing Cell (i,j)
		int lbbi = lowerBlockBound(i); int ubbi = upperBlockBound(i);
		int lbbj = lowerBlockBound(j); int ubbj = upperBlockBound(j);
		for(int ir=lbbi; ir<ubbi; ir++)
			for(int jr=lbbj; jr<ubbj; jr++)
				gp->Choice[ir][jr][v]=-1;
		// Trying to set any other cell in this block to v will fail in future.
		//ALL DONE. Ready to declare success.
		return(1);

	}
	//if v is illegal in this Cell, declare failure and return. 	
	return(0);
}

int canContain(Grid g, int i, int j, int v){
	// Tests whether Cell(i,j) can contain v. 
	// returns 1 if True. 0 if False.
	for(int k=0; k<GSIZE; k++){
		if(g.Choice[i][j][k] == v) return(1);
	}
	printf("canContain():Cell(%d,%d) cannot contain %d\n", i,j,v);
	return(0);
}
int lowerBlockBound(int i){
	//Calculates the lower block boundary containing index i
	int mod = (i)%GBASE;
	return(i-mod);
}
int upperBlockBound(int i){
	//Calculates the upper block boundary containing index i
	return(lowerBlockBound(i) + GBASE);
}
void printG(Grid* const gp){
	gp->Status[0][0]=1;
	//This does not raise any alarms when modifying contents of g using a pointer.
	//This basically means taht gp is a constant. But the contents to which it points to, are not read-only. they can be written to.
}

int readGridStr(char* str, Grid* gp){
	//readGridStr will read a Grid from a string. 
	// There are asumptions about the structure of string, which must be respected when passing string to this function.
	// Function itself will not perform any validation checks and will assume that the user has passed the correct string.
	int currentPosition=0;
	int readInt=-1;
	int i=0, j=0;
	int total=0;
	printf("readGridStr(): Starting to read string to grid\n");
	while(str[currentPosition] != '\0'){
		//For each iteration of loop, if i,j exceed limits, bring them back.
		if(i >= GSIZE){
			i=0;
			j=j+1;
		}
		//Do not read more than GSIZE*GSIZE ints
		if(total >= GSIZE*GSIZE)
			return(1);
		//discard non-digit values in the input str.
		//printf("readStrGrid(): Loop i=%d, j=%d, total=%d \n",i,j,total);
		if (str[currentPosition] < 48 || str[currentPosition] > 57){
		       	printf("readStrGrid(): Discarding %c\n", str[currentPosition]);
			currentPosition++;
			continue;
		}
		if(sscanf(&str[currentPosition++],"%d", &readInt)){
		       	total++;	
			if(readInt<0 || readInt>(GSIZE-1)){
				//Successfully scanned an int, but it is not valid.
				//leave this grid cell unchanged. skip to next grid cell.
				i++;
			}else{
				setCellValue(gp, j, i, readInt);
				i++;
				
			}

		}else{
			printf("readStrGrid():sscanf failed: i=%d, j=%d, total=%d",i,j,total);
		}

	}
	return(0); //reading failed.
}
int isSolved( Grid* gp){
	for(int i=0; i<GSIZE; i++)
		for(int j=0; j<GSIZE; j++){
			if(gp -> Status[i][j] == 0) 
				return(0);
		}
	return(1);	
}
int getNumChoices(Grid* gp, int i, int j){
	int n=0;
	for(int k=0; k<GSIZE; k++){
		if(gp->Choice[i][j][k] != -1)
			n++;
	}
	return(n);
}
int getAChoice(Grid* gp, int i, int j){
	int v = -1;
	for(int k=0; k<GSIZE; k++){
		v = gp->Choice[i][j][k];
		if( v != -1) 
			return(v);
	}
	return(v);

}
#endif
	
