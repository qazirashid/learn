#include <stdio.h>
#include <stdlib.h>
#define GSIZE  9


void printMatrix(int m[GSIZE][GSIZE]);
int initGrid(int Status[GSIZE][GSIZE], int Output[GSIZE][GSIZE], int* Choice[GSIZE][GSIZE]);
void printChoice( int* Choice[GSIZE][GSIZE]);

int main (void){
	int Status[GSIZE][GSIZE]; 
	// Status(i,j)=1 of grid indicates that Cell(i,j) has been set to some value. 
	// Status(i,j)=0 means that Cell(i,j) is unknown yet.
	int Output[GSIZE][GSIZE]; 
	// Output[i][j] = value, indicates that Cell[i][j]=value. Only meaningful if Status(i,j)=1.
	// Output[i][j] = 0, indicates that Cell[i][j] is currently unknown and has multiple legal values.
	int* Choice[GSIZE][GSIZE];
	// Choice[i][j] points to an array[GSIZE] of ints that contains all legal values allowed in Cell[i][j].
	for(int i=0; i<GSIZE; i++)
	       	for(int j=0; j<GSIZE; j++){
	       	Choice[i][j] = malloc(GSIZE*sizeof(int));
	     }
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
		

}
//Helper functions

int initGrid(int Status[GSIZE][GSIZE], int Output[GSIZE][GSIZE], int* Choice[GSIZE][GSIZE]){
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
			       *( (Choice[i][j]) + k) = (k); 
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

void printChoice( int* Choice[GSIZE][GSIZE]){
	
	for(int i=0; i<GSIZE; i++)
	       for(int j=0; j<GSIZE; j++){
		       printf("Cell(%d,%d) can potentially contain: ", i,j);
		       for(int k=0; k< GSIZE; k++){
			       printf("%d ", *( (Choice[i][j]) + k)) ;
		       }
		      printf("\n"); 
	      }	
	
}


int setCellValue(int i, int j, int v){
	// will attempt to set cell(i,j) value to v. On Success, returns 1. On failure returns 0. 
	// Failure occurs when the v is illegal in Cell(i,j).
	return(0);	
}

int canContain(int i, int j, int v, int* Choice[GSIZE][GSIZE]){
	// Tests whether Cell(i,j) can contain v. 
	// returns 1 if True. 0 if False.
	for(int k=0; k<GSIZE; k++){
		if(Choice[i][j][k] == v) return(1);
	}
	return(0);
}
