/*partners: maxh3, jacobak3, nikhilt4*/

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.

/*
INTRO PARAGRAPH:
- The following code are functions which recursively solve sudoku puzzles. The functions: is_val_in_row, is_val_in_col and is_val_in_3x3_zone check whether the input
  value is a potentially valid index. Finally, the solve_sudoku function recursively checks every value. If it fails, it backtracks to the starting value placed.
*/


int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int c=0; c<9; c++) {          //Loops through each column in a given row to check if a value is already in that row
    if(sudoku[i][c] == val) {
      return 1;
    }
  }
  return 0;                         //Returns 0 if not true
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int r=0; r<9; r++) {           //Loops through each row in a given row to check if a value is already in that column
    if(sudoku[r][j] == val) {
      return 1;
    }
  }
  return 0;                          //Returns 0 if not in the column
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int start_col, start_row;                     //Declare variables
  int end_col, end_row;

  start_col = (j/3) * 3;                        //Assigns the 3x3 zone to check for
  start_row = (i/3) * 3;
  end_col = start_col + 3;                      //End case for the 3x3 zone
  end_row = start_row + 3;

  for(int r=start_row; r<end_row; r++) {        //Loops through every value to check every 3x3 zone
    for(int c=start_col; c<end_col; c++) {
      if(sudoku[r][c]==val) {
        return 1;
      }
    }
  }
  return 0;                                     //Returns 0 if not a valid 3x3 zone
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if (is_val_in_3x3_zone(val, i,j, sudoku)== 1 || is_val_in_col(val, j, sudoku) == 1 || is_val_in_row(val, i, sudoku)==1) { //If any are true, it i not a valid value for that index
    return 0;
  }
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i, j;                       //Declare variables and full condition
  int full = 1;
  for(int r=0; r<9; r++) {        //Checks every value to see if its 0
    for(int c=0; c<9; c++) {
      if(sudoku[r][c] == 0) {     //If 0, the first 0 has been found which means the sudoku is not full
        full=0;           
        i = r;                    //Assigns the row and column values to indicate the first 0
        j = c;
        break;
      }
    }
  }

  if(full==1)                    //If full, the sudoku is complete
    return 1;

  for (int num = 1; num <= 9; num++) {      //Loop to check for each valid number
    if (is_val_valid(num, i, j, sudoku)) {  //If valid, assume the number is correct at that index
      sudoku[i][j] = num;
      if (solve_sudoku(sudoku)) {           //Recursively checks if the next 0 is now solved
        return 1;
      }
      sudoku[i][j] = 0;                     //If not, backtrack and try a new number
    }
  }
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





