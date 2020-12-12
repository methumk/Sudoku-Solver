Sudoku:
	- Sudoku is a puzzle that is played on a 9x9 grid. Sometimes it's 16x16, but the classic case is 9x9. 
		To win the game, you must place a number 1-9 in all empty cells (I represent this with 0) and the rows must have digits 1-9 (not in any order)
		, the cols must have digits 1-9 (not in any order) and each subgrind must have 1-9 (not in any order). There also can't be any
		duplicate numbers in a col, row, or subgrid. 

Running:
	- To run type make, then ./run

The program:
	- There are two options for this program
	- To get option 1 enter 1, for option 2 enter 2, there is error handling for this input.

	option 1:
		You can enter a sudoku puzzle into sudokuBoard.txt (there's already one loaded into the txt file) and the computer will solve the sudoku puzzle.
		Note: If there is more than one solution it will output both solutions.
		Note2: To signify an empty square put in a 0

	options 2:
		You can solve a randomly generated puzzle by the computer. Note: There may be more than one possible board solution.
		Even though there are multiple solutions, the validation process will mark you as correct if the board is correct regardless if it is the same as the ans board.

		-To place a number in a cell:
			Type the row and col together e.g. 67 (row 6, col 7). There is error handling to make sure you input the correct row and col
			Then, if row and col is correct, it will prompt for the number you want to insert. Type a valid number (1-9)

		-To view the solution to the sudoku puzzle:
			Type ans. 

		-To validate the current board:
			When you have submitted a number and you want to check if it's correct, type val.
			Note: This resets the board to the original sudoku puzzle and you will loose all your inputted values, so be careful!

		-To exit the program:
			Type exit or win the game.

		Note: Empty cells are marked with 0
