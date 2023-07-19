#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* partners: maxh3, jacobak3, nikhilt4
    The following code solves a maze using DFS, meaning that it recursively extends into a maze and backtracks if it hits a dead end. 
    
    The createmaze method dynamically allocates memory for the maze and reads information in from a given file, it then parses that information and stores it as a 
    maze struct.  It also saves the start and end location 
    
    The destroyMaze method frees all allocated data 

    the printMaze method prints the maze (not that deep)

    and the solveMazeDFS method performs the recursive maze search as described above. 
*/
/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    maze_t * myMaze = malloc(sizeof(maze_t)); 
    int w,h;
    FILE * file = fopen(fileName, "r");
    fscanf(file, "%d %d", &w, &h); // gets first 2 ints (width and height)

    myMaze->height = h;
    myMaze->width =w;

    myMaze->cells = malloc(sizeof(myMaze->cells)*myMaze->height);

    for(int i=0; i<myMaze->height; i++) {
        myMaze->cells[i] = malloc(sizeof(myMaze->cells[i])*myMaze->width); //cells is a char** so a multistep pointer system is used, - this saves as an array of rows
    }
    char temp;
    fscanf(file, "%c", &temp); // gets rid of \n

    for(int i=0; i<myMaze->height; i++) {
        for(int j=0; j<myMaze->width; j++) {
            fscanf(file, "%c", &temp); //might start at the width/height info
            myMaze->cells[i][j] = temp; //populates array
            if(myMaze->cells[i][j] == START) { //saves start location
                myMaze->startRow = i;
                myMaze->startColumn = j;
            }
            if(myMaze->cells[i][j] == END) { //saves end location
                myMaze->endRow = i;
                myMaze->endColumn = j;
                
            }
        }
        fscanf(file, "%c", &temp); //gets rid of new line
        
    }
    fclose(file);
    return myMaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    for(int i=0; i<maze->height; i++) { //free each row pointer
        free(maze->cells[i]);
    }
    free(maze->cells); //free row array pointer
    free(maze); // free maze pointer
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    for(int i=0; i<maze->height; i++) {  // this is a print statement
        for(int j=0; j<maze->width; j++) {
            printf("%c", maze->cells[i][j]);
        }
        printf("\n");
    }
}

/*solveMazeDFS
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    int width = maze->width;
    int height = maze->height;
    if( col <0 || col >= width || row <0 || row >= height ){ //if row or col is out of maze, unsolvable
        return 0;
    }
    if(maze->cells[row][col] == END){
        maze->cells[maze->startRow][maze->startColumn]=START;
        return 1;
    }
    if(maze->cells[row][col] != EMPTY && maze->cells[row][col] != START){ //if cell is NOT a space, unsolvable
        return 0;
    }
    //yay this step isnt illegal (yet)
    maze->cells[row][col] ='*';

    //check directions next to current spot
     if(solveMazeDFS(maze, col+1, row)==1) {
        return 1;
    }
     if(solveMazeDFS(maze, col-1, row)==1) {
        return 1;
    }
     if(solveMazeDFS(maze, col, row+1)==1) {
        return 1;
    }
     if(solveMazeDFS(maze, col, row-1)==1) {
        return 1;
    }
    //if nowhere to go -> gg restart
    maze->cells[row][col] = '~';

    return 0;

}
