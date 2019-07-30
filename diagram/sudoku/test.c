#include <stdio.h>
#include <stdlib.h>
#define GSIZE  9

/********* Function Declarations *************/
void printMatrix(int m[GSIZE][GSIZE]);
int initGrid(int Status[GSIZE][GSIZE], int Output[GSIZE][GSIZE], int Choice[GSIZE][GSIZE][GSIZE]);
void printChoice( int Choice[GSIZE][GSIZE][GSIZE]);
int canContain(int i, int j, int v, int Choice[GSIZE][GSIZE][GSIZE]);
int setCellValue(int i, int j, int v, int Status[GSIZE][GSIZE], int Output[GSIZE][GSIZE], int Choice[GSIZE][GSIZE][GSIZE]);
int lowerBlockBound(int i);
int upperBlockBound(int i);
/**************** Main *************************/

int main (void){
	int Status[GSIZE][GSIZE]; 
	// Status(i,j)=1 of grid indicates that Cell(i,j) has been set to some value. 
	// Status(i,j)=0 means that Cell(i,j) is unknown yet.
	int Output[GSIZE][GSIZE]; 
	// Output[i][j] = value, indicates that Cell[i][j]=value. Only meaningful if Status(i,j)=1.
	// Output[i][j] = 0, indicates that Cell[i][j] is currently unknown and has multiple legal values.
	int Choice[GSIZE][GSIZE][GSIZE];
	// Choice[i][j] points to an array[GSIZE] of ints that contains all legal values allowed in Cell[i][j].
	//for(int i=0; i<GSIZE; i++)
	       	//for(int j=0; j<GSIZE; j++){
	       	//Choice[i][j] = malloc(GSIZE*sizeof(int));
	     //}
	//Allocated memory for all arrays of choices. Could not find a way to allocate it statically in a for loop. Maybe there is a way, don't know. 
	//
	//Initialize Grid with all 0s.
	initGrid(Status, Output, Choice);		
	printf("Current Status is:\n");
	printMatrix(Status);
	printf("Current Output is:\n");
	printMatrix(Output);
	printf("Current Legal Choices are:\n");
	printChoice(Choice);

	//******* Try to set Cell (0,0) to 9.
	if (setCellValue(0,0,8,Status,Output,Choice)){
		printf("Success setting cell(0,0):\n");
		printf("Current Status is:\n");
		printMatrix(Status);
		printf("Current Output is:\n");
		printMatrix(Output);
		printf("Current Legal Choices are:\n");
		printChoice(Choice);
	}else printf("Failed to set Cell(0,0) to 8\n");
		
	if (setCellValue(0,1,3,Status,Output,Choice)){
		printf("Success setting cell(0,0):\n");
		printf("Current Status is:\n");
		printMatrix(Status);
		printf("Current Output is:\n");
		printMatrix(Output);
		printf("Current Legal Choices are:\n");
		printChoice(Choice);
	}else printf("Failed to Set Cell\n");

}
/***************** Helper Functions ***********************/

int initGrid(int Status[GSIZE][GSIZE], int Output[GSIZE][GSIZE], int Choice[GSIZE][GSIZE][GSIZE]){
	int i=0, j=0;
	for(int i=0; i<GSIZE; i++)
	       for(j=0; j<GSIZE; j++){
	       	Status[i][j] = 0;
	      }
	for(i=0; i<GSIZE; i++)
	       for(j=0; j<GSIZE; j++){
	       	Output[i][j] = 0;
	      }
	for(i=0; i<GSIZE; i++)
	       for(j=0; j<GSIZE; j++){
		       for(int k=0; k< GSIZE; k++)
			       Choice[i][j][k] = k; 
	      }
	return(1); // Sucesss

}

void printMatrix(int m[GSIZE][GSIZE]){
	
	for(int i=0; i<GSIZE;i++){
		for(int j=0; j<GSIZE; j++){
	       		printf("%d ", m[i][j]);	
			if( (j+1) %3 == 0) printf("| ");
	      }
		printf("\n");
		if( (i+1)%3 == 0) printf("-----------------------\n");
	}

}

void printChoice( int Choice[GSIZE][GSIZE][GSIZE]){
	
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


int setCellValue(int i, int j, int v, int Status[GSIZE][GSIZE], int Output[GSIZE][GSIZE], int Choice[GSIZE][GSIZE][GSIZE]){
	// will attempt to set cell(i,j) value to v. On Success, returns 1. On failure returns 0. 
	// Failure occurs when the v is illegal in Cell(i,j).
	// Take care not to overwrite i, j, v. Preserve the passed values when using loops.
	if((v<0) || (v >=GSIZE))
		return(0); // invalid v was passed.
	if(canContain(i,j,v, Choice)){
		// If v is legal in Cell(i,j), Then do all of the below
		// 1- set status of Cell(i,j)=1. this indicates that Cell has been occupied.
		Status[i][j] = 1;
		// 2- set output of Cell(i,j)=v+1 (1 added because of C-index starting at 0. This indicates the output user will get. 
		Output[i][j] = v;
		// 3- Set all of Choice[i][j][k] for (0<= k < GSIZE) to -1. This indicates that Cell is occupied. Next attempt to set it to some value will fail.
		for(int kr=0; kr<GSIZE;kr++)
			Choice[i][j][kr] = -1;
		//4- For all Cells in the row i (0<=i<GSIZE), exclude v by setting Choice[i][j][v]=-1, because no further Cell in this row can be set to v.
		for(int ir=0; ir<GSIZE;ir++)
			Choice[ir][j][v] = -1;
		//5- For all Cells in the column j (0<=j<GSIZE), exclude v by setting Choice[i][j][v]=-1, because no further Cell in the column can be set to v.
		for(int jr=0; jr<GSIZE; jr++)
			Choice[i][jr][v] = -1;
		//6- For all Cells in the 9x9 block containing Cell(i,j), exclude v by setting Choice[b][c][v] ==0, because this block cannot contain v in any other Cell.
		// This is 2-D Loop. Calculate lower and upper bounds to contain (i,j) in the 9x9 box containing Cell (i,j)
		int lbbi = lowerBlockBound(i); int ubbi = upperBlockBound(i);
		int lbbj = lowerBlockBound(j); int ubbj = upperBlockBound(j);
		for(int ir=lbbi; ir<ubbi; ir++)
			for(int jr=lbbj; jr<ubbj; jr++)
				Choice[ir][jr][v]=-1;
		// Trying to set any other cell in this block to v will fail in future.

		//ALL DONE. Ready to declare success.
		return(1);

	}
	//if v is illegal in this Cell, declare failure and return. 	
	return(0);
}

int canContain(int i, int j, int v, int Choice[GSIZE][GSIZE][GSIZE]){
	// Tests whether Cell(i,j) can contain v. 
	// returns 1 if True. 0 if False.
	for(int k=0; k<GSIZE; k++){
		if(Choice[i][j][k] == v) return(1);
	}
	return(0);
}
int lowerBlockBound(int i){
	//Calculates the lower block boundary containing index i
	int mod = (i)%3;
	return(i-mod);
}
int upperBlockBound(int i){
	//Calculates the upper block boundary containing index i
	return(lowerBlockBound(i) +3);
}
