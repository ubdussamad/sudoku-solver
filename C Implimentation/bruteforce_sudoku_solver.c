#include<stdio.h>
#include<stdlib.h>
#include <string.h>

void file_handler();
int chr_to_int();
void print_sudoku();
int find_empty_indices();
void print_sudoku_ref();

struct indices {
	int r;
	int c;
};

int main(int argc, char **argv){
	int dim = 9;
	int sudoku[dim][dim]; //Initialize a 9x9 array
	file_handler(&sudoku,dim,argv);
	print_sudoku_ref(&sudoku,dim);
    int empty_indices = find_empty_indices(0,&sudoku,dim,8,1);
    struct indices pos [empty_indices];
    find_empty_indices(&pos,&sudoku,dim,8,0);
    printf("\n");
    for (int i = 0; i < (empty_indices+1);i++)
    {
    	printf("Positions:%d,%d\n",pos[i].r,pos[i].c);
    }
	return(0);
}



int find_empty_indices(struct *intial_array_ptr [], int *sudoku_start_ptr,int dim,size_t len,int count){
	long unsigned int dref_ptr = (long unsigned int) sudoku_start_ptr;
	//long unsigned int pos_dref_ptr = (long unsigned int) intial_array_ptr;

	printf("\n");
	int counter = 0;
	int pos_counter = 0;
	
	for (int i=0;i<dim;i++) {
		printf("\n");

		for (int j = 0;j<dim;j++){

			int * ref_ptr = (int *)dref_ptr;
			int value = (int)*ref_ptr;
			if (!value){
				
				if (count){
					//printf("Increasing count:%d\n",count);
					counter++; //Counts the array size needed for storing positions
				}
				else {
					//struct * kl= (struct *)intial_array_ptr[pos_counter];
					//*kl.r = *i;
					//*kl.c = *j;
					//pos_counter++;
					//int *ref_pos_ptr = (int *) pos_dref_ptr;
					//memcpy(ref_pos_ptr,&i,4);
					//pos_dref_ptr = pos_dref_ptr + 4;
					//ref_pos_ptr = (int *) pos_dref_ptr;
					//memcpy(ref_pos_ptr,&j,4);
				}
			}
			//pos_dref_ptr = pos_dref_ptr + 4;
		}
	}
	if (count>0){
		return(counter);
	}
	else{
		return(0);
	}
}


void print_sudoku_ref(int *sudoku_ptr,int dim){
	long unsigned int dref_ptr = (long unsigned int)sudoku_ptr;
	for (int i=0;i<(dim*dim);i++){
		if (i%9==0){printf("\n");}
		int * ref_ptr = (int *)dref_ptr;
		printf("%d|",*ref_ptr);
		dref_ptr = dref_ptr  + 4;
	}
}
int chr_to_int(int ch){
	/* Maps integer character bytes to actual
	   integers values using ASCII standard.*/ 
	int list[10] = {48,49,50,51,52,53,54,55,56,57};
	
	int get_index(int sch,int * arr){

		int counter = 0;
		while (counter < 10){

			if (arr[counter] == sch) {
				return(counter);
			}
			counter++;
		}
		return(-1); // Returns -1 if the given input doesn't corresponds to any ASCII integer mapping.
	}
	return(get_index(ch,list));
}
void file_handler(int * arr,int dim, char **argv){
	long unsigned int start_ptr = (long unsigned int)arr;
    FILE *sudoku_ptr;
	sudoku_ptr = fopen (argv[1], "r");
  	if (sudoku_ptr == NULL) {
  		exit (EXIT_FAILURE);
  	}

    for (int i = 0; i<dim; i++) {
    	for (int j = 0; j<(dim+1); j++){
    		char ch = getc(sudoku_ptr);
    		if (ch != '\n') {
    		  int num = (int)ch;
    		  int n = chr_to_int(num);
    		  int * ptr = (int *)start_ptr;
    		  memcpy(ptr,&n,sizeof(int));
              start_ptr = start_ptr + sizeof(int);
            }

    	}
    }
}
