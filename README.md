# Sudoku-solver
Different types of Sudoku solving algorithms and their implimentations in Python3.x.

Currently supports only 9x9 and 6x6 Sudokus but in future other diamentional compatibility
will be added.

More Implimentaions comnig as soon as i write them.

# Data
You'll need to provide it with a **9x9** or **6x6** grid of sudoku written in plain text file with any encoding.

A **zero** is placed inplace of a vacant cell to make things easier.

The format can be futher understood by reading **s1** sudoku file.

# Running
* Navigate to the cloned/downloaded directory by using:
* `cd ~/where_ever/sudoku-solver/`
* Make the program executable by: *(Assuming your default python3 path is: `#!/usr/bin/env python3`)*
* `chmod +x sudoku_bruteforce.py`
* Then the program can be run by the terminal command: *(Assuming you have Python3 available in the terminal.)*
* `./sudoku_bruteforce.py [path to sudoku file] [1 if you want verbose output else 0]`
* For example to solve **s1** with verbose output:
* `./sudoku_bruteforce.py s1 1`

# Feedback
Please notify me of any improvements or flaws at ubdussamad + at the rate email service by google.
