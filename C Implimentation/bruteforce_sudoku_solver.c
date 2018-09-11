#include<stdio.h>
#include<stdlib.h>
int file_handler();
int chr_to_int();

int main(int argc, char **argv){
	int sudoku[9][9]; //Initialize a 9x9 array
	file_handler(&sudoku,argv);
	for (int i=0;i<9;i++){
		printf("\n");
		for (int j = 0;j<9;j++){
			printf("%d",sudoku[i][j]);
		}
	}
	return(0);

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

int file_handler(int *arr[9][9] , char **argv){
	FILE *sudoku_ptr;
	sudoku_ptr = fopen (argv[1], "r");
  	if (sudoku_ptr == NULL)
    {
      exit (EXIT_FAILURE);
    }
    int counter = 90; //81 Elements + 9 Newline characters.
    int i = 1;

    for (int i = 0; i<9; i++) {
    	for (int j = 0; j<9; j++){
    		char ch = getc(sudoku_ptr);
    		if (ch != '\n'){
    		int num = (int)ch;
    		int *n = chr_to_int(num);
    		arr[i][j] = *n;
    	}
    	}
    }
    /*
    while (i <= counter){
    	if (i%10==0){
    		printf("\n");
    	}
    	char ch = getc(sudoku_ptr);
    	int num = (int)ch;
    	if (ch != '\n'){
    		printf("%d",chr_to_int(num));
    	}
    	
    	i++;
    }*/

	return(0);
}
