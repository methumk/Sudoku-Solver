#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

//checks to see if the entire board is filled with numbers besides 0
bool filled(int board[][9]) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (board[i][j] == 0)
				return false;
		}
	}
	return true;
}

//print a board in a format that is easy on the eyes
void print(int board[][9]) {

	//printing index 
	for (int i = 1; i < 10; ++i) {
		if (i == 3 || i == 6)
			cout << i << "   ";
		else
			cout << i << " ";
	}
	cout << endl;
	for (int i = 1; i < 10; ++i) {
		if (i == 3 || i == 6)
			cout << "_" << "   ";
		else
			cout << "_" << " ";
	}
	cout << endl;

	for (int i = 0; i < 9; ++i) {
		//newline if row 3 or row 6
		if (i == 3 || i == 6)
			cout << endl;
	
		for (int j = 0; j < 9; ++j) {
			//create extra spacing between subgrids
			if (j == 3 || j == 6)
				cout << "  ";
			if (j == 8)
				cout << board[i][j];
			else
				cout << board[i][j] << " ";

			//prints rows index at the end
			if (j == 8)
				cout << "| " << i+1;
		}
		cout << endl;
	}

	cout << endl << "============END============" << endl;
}

//checking if number we are trying can be placed into board
bool can_place(int board[][9], int check, int row, int col) {
//check row
	for (int i = 0; i < 9; ++i) {
		if (check == board[row][i]) {
			//cout << "failed: checking row" << endl;
			return false;
		}
	}

//check col
	for (int i = 0; i < 9; ++i) {
		if (check == board[i][col]) {
			//cout << "failed: checking col" << endl;
			return false;
		}
	}

//check sub-grid
	//start at the top left hand corner to check sub grid
	int x = (row / 3) * 3; 
	int y = (col / 3) * 3;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[x + i][y + j] == check) {
				//cout << "failed: checking sub-grid" << endl;
				return false;
			}
		}
	}

//check # not contained in row, col or in it's own grid then try it
	//cout << "possible" << endl;
	return true;
}

//copies a board from source to destination
void copy_boards(int src[][9], int dst[][9]) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			dst[i][j] = src[i][j];
		}
	}
}

//sets all cells in a board to 0
void clear_board(int board[][9]) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			board[i][j] = 0;
		}
	}
}

//solves the entire board by checking each value
void solve(int board[][9]) {
	if (!filled(board)) {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				//if the cell is not filled, try filling it with a value
				if (board[i][j] == 0) {

					for (int check = 1; check <= 9; ++check) {
						//cout << "row: " << i << ", col: " << j << ", checking: " << check << endl;
							//if you can place a number in the cell, place it and recurse to the next number
						if (can_place(board, check, i, j)) {

							board[i][j] = check;
							//print(board);
							//cout << endl;
							solve(board);
							board[i][j] = 0;
						}
					}

					//cout << "failed all: returning" << endl;
					return;

				}


			}

		}
	}
	else {
		cout << "============ANS============" << endl;
		print(board);

	}
	
	
	
	
}

//solving a sudoku that was given to the sudokuBoard.txt file
void solve_from_file() {
	ifstream input;
	int board[9][9];

	input.open("sudokuBoard.txt");

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			input >> board[i][j];
		}
	}

	solve(board);
}

//erases given index of vector
void exclude_num(vector<int>& possible, int idx) {
	possible.erase(possible.begin() + idx);
}

//sets vector to have #s 1 - 9
void set_vec(vector<int>& vec) {
	for (int i = 1; i <= 9; ++i)
		vec.push_back(i);
}

//checks to see if board contains at least 1 non zero num
bool contain_nums(int board[][9]) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (board[i][j] != 0)
				return true;
		}
	}
	return false;
}

//shuffles contents of vec
void shuffle_vec(vector<int>& vec) {
	srand(time(NULL));
	int idx, hold;
	for (int j = 0; j < 2 * vec.size(); ++j) {
		for (int i = 0; i < vec.size(); ++i) {
			idx = rand() % 9;
			hold = vec[i];
			vec[i] = vec[idx];
			vec[idx] = hold;
			
		}
	}
	
}

//develop a valid sudoku puzzle from scratch
void develop_sudoku(int board[][9], int board2[][9], vector<int>& vec) {
	if (!filled(board)) {
			for (int i = 0; i < 9; ++i) {
				for (int j = 0; j < 9; ++j) {
					//if the cell is not filled, try filling it with a value
					if (board[i][j] == 0) {
							for (int k = 0; k < vec.size(); ++k) {
								int check = vec[k];
								if (can_place(board, check, i, j) && contain_nums(board)) {
									board[i][j] = check;
									//print(board);
									//cout << endl;
									develop_sudoku(board, board2, vec);
									board[i][j] = 0;
								}
							}
							return;
					}
				}

			}
	}
	else {
			copy_boards(board, board2);
			clear_board(board);
	}

}

//makes some cell numbers invisible
void mystify(int board[][9]) {
	srand(time(NULL));
	int num_hidden = rand() % 5 + 54;
	int x, y;

	for (int i = 0; i < 40; ++i) {
		x = rand() % 9;
		y = rand() % 9;
		while (board[x][y] == 0) {
			x = rand() % 9;
			y = rand() % 9;
		}
		board[x][y] = 0;


	}
}

//holistic function to create a board, print, and then solve it for generated board
void create_sudoku(int board[][9], int generated[][9]) {
	int copied_board[9][9];


	//clear both boards (every cell set to 0)
	clear_board(board);
	clear_board(copied_board);

	//vector containing all posibilities for a cell
	vector<int> pos_num;
	set_vec(pos_num);

	
	//first cell gets a random # from pos num vec
	srand(time(NULL));

	//set values for top left sub grid
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			int idx = rand() % pos_num.size();
			int num = pos_num[idx];
			board[i][j] = num;
			exclude_num(pos_num, idx);
		}
	}

	set_vec(pos_num);
	shuffle_vec(pos_num);

	develop_sudoku(board, copied_board, pos_num);


	cout << "===========Generated Board===========" << endl;
	//save actual answer into generated array
	copy_boards(copied_board, generated);
	print(generated);

	cout << endl << "===========SUDOKU===========" << endl;
	mystify(copied_board);
	print(copied_board);

	//board becomes the mystified board
	copy_boards(copied_board, board);

}

//checks if all numbers in board are validate (not checking empty cells)
bool validate(int board[][9]) {
//checking all rows
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			int row = i, col = j, val = board[i][j];

			//exclude cells with 0 for validation
			if (val != 0) {
				for (int k = 0; k < 9; ++k) {
					//check if current val is found in the same row and we aren't looking at the same 
					if (val == board[i][k] && col != k) {
						cout << "row: False @: val: " << val << " board[i][k]: " << board[i][k] << endl;
						return false;
					}
				}
				
			}
		}
	}

//checking all cols
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			int row = i, col = j, val = board[i][j];

			//exclude cells with 0 for validation
			if (val != 0) {
				for (int k = 0; k < 9; ++k) {
					//check if current val is found in the same row and we aren't looking at the same 
					if (val == board[k][j] && row != k) {
						cout << "col: False @: val: " << val << " board[i][k]: " << board[i][k] << endl;
						return false;
					}
				}

			}
		}
	}


//checking sub grid
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			//row is start position of sub grid, val is current board value
			int row = (i / 3) * 3, col = (j / 3) * 3, val = board[i][j];

			//start subgrid at top left corner
			for (int k = 0; k < 3; ++k) {
				for (int l = 0; l < 3; ++l) {
					if (val != 0) {
						//if val is same in subgrind and val is not itself
						if (val == board[row + k][col + l] && (i != row + k && j != col + l))
							return false;
					}
				}
			}

		}
	}


	return true;
	
}

//gives options for the user to play the computer generated board
void play_sudoku(int board[][9], int generated[][9]) {
	int row, col, val;
	string input = "";
	int mystified[9][9];
	
	//copies original sudoku (board) into mystified in case user makes an error and we have to reset board
	copy_boards(board, mystified);

	while (true) {
		cout << endl << "Enter a row and col (e.g. 12 means row: 1, col: 2 )" << endl;
		cout << "Type ans to see possible valid solutions" << endl;
		cout << "Type val to validate currently filled board (if incorrect will reset board)" << endl;
		cout << "Type exit to exit the program: ";
		cin >> input;

		if (input == "ans") {
			cout << endl << "Solved board (there maybe more than 1 valid board): " << endl << endl;
			print(generated);
		}
		else if (input == "val") {
			if (validate(board)) {
				cout << endl << "Looks good so far!" << endl;
			}
			else {
				cout << endl << "There's an error some where! Resetting board" << endl << endl;
				copy_boards(mystified, board);
				print(board);
			}
		}
		else if (input == "exit") {
			break;
		}
		else if (input.size() == 2 && (input[0]-48 > 0 && input[0]-48 < 10) && (input[1]-48 > 0 && input[1]-48 < 10)) {
			//ascii value - 49 to get index value of row and col
			row = input[0]-49;
			col = input[1]-49;

			// allow to place value if cell is empty
			if (board[row][col] == 0) {
				cout << endl << "Input # (1-9) you want to put into given row and col cell: ";
				cin >> val;
				cout << endl;

				//validate cell value
				while (val > 9 || val < 1) {
					cout << endl << "Input # (1-9) you want to put into given row and col cell: " << endl;
					cin >> val;
				}

				//if board is not filled, enter valid user input
				if (!filled(board)) {
					board[row][col] = val;
					print(board);
				}

				//check if everything is correct and board is filled
				if (filled(board) && validate(board)) {
					cout << endl << "You've solved the puzzle!" << endl;
					break;
				}
			}
			else {
				cout << endl << "Unable to place: cell already taken!" << endl;
			}
		}
		
	}
}

//generates the computer generated board and allows the user to play
void solve_generated_board() {
	int board[9][9], generated[9][9];

	create_sudoku(board, generated);


	//gives options to play the computer generated board
	play_sudoku(board, generated);


}

//asks the user what option they want to choose and executes that option
void sudoku_option() {
	string option = "";
	cout << "Enter 1 to solve board stored in sudokuBoard.txt.";
	cout << endl << "Enter 2 to manually solve computer generated board: ";
	cin >> option;

	while (option != "1" && option != "2") {
		cout << "Enter 1 to solve board stored in sudokuBoard.txt.";
		cout << endl << "Enter 2 to manually solve computer generated board: ";
		cin >> option;
	}

	if (option == "1") {
		solve_from_file();
	}
	else {
		solve_generated_board();
	}
}

int main() {

	sudoku_option();
	
}



