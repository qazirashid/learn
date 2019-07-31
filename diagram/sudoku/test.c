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
//Just for tests
void printG(Grid * const g);

/**************** Main *************************/

int main (void){
	Grid g;
	Grid* gp = &g;
	//Initialize Grid with all 0s.
	initGrid(gp);		
	printGrid(gp);
	setCellValue(gp,0,0,1);
	setCellValue(gp,3,1,1) ;
	setCellValue(gp,7,2,1);
	setCellValue(gp,1,3,1);
	setCellValue(gp,2,7,1);
	setCellAndPrint(gp, 3,2,2);
	printGrid(gp);
}
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
