#!/usr/bin/env python3
#9x9 Sudoku Solver in Python3
#07SEP2018
#Author: Mohammed S. Haque <ubdussamad@gmail.com>

#Though default version for this code is 3.x but it's is written in a way that may support 2.x as well.
import sys,time
class loader: #For loading the target sudoku puzzle file
    path_to_sudoku = sys.argv[1] if len(sys.argv) > 1 else "s1"
    sudoku_file_object = None if not(path_to_sudoku) else open(path_to_sudoku,'r')
    sudoku = sudoku_file_object.read() if sudoku_file_object else -1
    sudoku = [i for i in sudoku.split('\n') if i]
    sudoku = [list(i) for i in sudoku] 

class parser(object): #Loads and defines all the methods which can be 
    def __init__(self,sudoku): # used to manipulate or read a sudoku.
        self.sudoku = sudoku
        self.current_index = -1
        self.empty_indices = []
        self.dim = len(sudoku)
        self.parent_list = [ str(i) for i in range(1,self.dim+1)]
        self.prams = []
        self.find_empty_indices()
        print("Hello, Your sudoku grid is:%dx%d and the complexity is: %.2f Percent "%(self.dim,self.dim, (len(self.empty_indices)/(self.dim**2))*100 ) )
        if self.dim != 9:
        	print("This Solver is only designed for solving 9x9 Sudokus.")
        	raise NotImplementedError
    
    def get_subsections(self,pos): #Returns a list of all the numbers present
        quad_members = []        #in the subsection of the given cell (only for 9x9 sudokus).
        #Divides the columns into triplets and then finds all the numbers in subsection
        r = {i:range(j,k+1) for i,j,k in zip(range(1,4),range(0,7,3),range(2,9,3))}
        
        def get_range(coord):
            for i in r:
                if coord in r[i]:
                    return(i)
        row_triplet,column_triplet = get_range(pos[0]),get_range(pos[1])
        for i in r[row_triplet]:
            for j in r[column_triplet]:
                if int(self.sudoku[i][j]):
                	quad_members.append(self.sudoku[i][j])
        return(quad_members)
        #return(list(filter(lambda x:x!="0",quad_members))) #Filter out zeros from the list and return.

    def get_subsections_for_all(self,pos): #Under Construction 
        quad_dim = [3,3] if self.dim==9 else [3,2]
        num_of_quads = (self.dim**2)/(quad_dim[0]*quad_dim[1])
        quad_dict = {i:[j,k] for i,j,k in ra}
        return (quad_list)
        

    def find_empty_indices(self):
        for i,j in enumerate(self.sudoku):
            for k,l in enumerate(j):
                if l == "0":self.empty_indices.append([i,k])

    def set_index(self,pos):
        index = self.empty_indices.index(pos)
        self.current_index = index

    def next(self): # Calling next for the first time starts the counter and returns first position.
        self.current_index += 1
        return self.empty_indices[self.current_index]
    def get_options(self,pos):
        return [ i for i in self.parent_list if i not in set(self.get_neighbours(pos)+self.get_subsections(pos))]

    def previous(self):
        self.current_index -= 1
        return self.empty_indices[self.current_index]
    
    def current(self):
        return( self.empty_indices[self.current_index])

    def get_neighbours(self,pos):
        i,j = pos
        neighbours_list = [ self.sudoku[i][k] for k in range(0,self.dim) if int(self.sudoku[i][k])] #Keeping i Constant
        neighbours_list += [ self.sudoku[k][j] for k in range(0,self.dim) if int(self.sudoku[k][j])]
        return neighbours_list

    def p(self):
        print()
        for i in self.sudoku:
            print("|",end="")
            for j in i:
                print(j,end="|")
            print()
        print()

    def challenge(self):
        return(len(self.empty_indices))



#Solving Logic
def solve(z,v=0):
    try:
        pos = z.next()
    except:
        return(0)

    op = z.get_options(pos) #Get all the available options

    if not(len(op)):
        print("Rolling Back!\n" if v else "",end="")
        z.set_index(z.previous())
        return(-1)

    while 1:
        if v:print("Current Position is:",pos,"and current options are:",op)
        
        if not(len(op)):
            print("Rolling Back!\n" if v else "",end="")
            z.sudoku[pos[0]][pos[1]] =  0
            z.set_index(z.previous())
            return(-1)
        ch = op.pop()
        if v:print("We chose:",ch)
        
        z.sudoku[pos[0]][pos[1]] =  ch#MO
        
        call = solve(z,v)

        if call == 0:
            return(0)
        elif call == -1:
            continue
        else:
            print("An Unexpected Error occurred!")
if __name__ == "__main__":
	z = parser(loader.sudoku) 
	initial  = time.time()
	solve(z,sys.argv[2] if len(sys.argv)>2 else 0)
	print("Time taken to solve:%.2fs"%(time.time()-initial))
	z.p()
