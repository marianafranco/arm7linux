/************************************************************************************
	KinOS - Microkernel for ARM Evaluator 7-T
	Seniors project - Computer Engineering
	Escola Politecnica da USP, 2009
	
	Felipe Giunte Yoshida
	Mariana Ramos Franco
	Vinicius Tosta Ribeiro
*/

/* 
	The program was based on the mutex program by ARM - Strategic Support Group,
	contained on the ARM Evaluator 7-T example CD, under the folder /Evaluator7-T/
	source/examples/mutex/ 
*************************************************************************************/


/****************************************************************
 * IMPORT
 ****************************************************************/

#include "tictactoe.h"


/****************************************************************
 * MACROS
 ****************************************************************/
 
#define	ISDIGIT(c) ((c >= 48 && c <= 57))
#define MAX 3

/****************************************************************
 * GLOBAL VARIABLES
 ****************************************************************/
 
// global variable
char grid[3][3];


/****************************************************************
 * ROUTINES
 ****************************************************************/

// prints the game grid
// Example:
//
//  X |   |   
// ---+---+---
//  O | X |   
// ---+---+---
//  O | O | X 
//
void printgrid(void) {
    
    char str[MAX];
    
    str[1] = 0;
    
    print("\r\n\n   0   1   2\r\n\n");
    
    print("0  ");
    str[0] = grid[0][0];
    print(str);
    print(" | ");
    str[0] = grid[0][1];
    print(str);
    print(" | ");
    str[0] = grid[0][2];
    print(str);
    print("\r\n");
    
    print("  ---+---+---\r\n");
    
    print("1  ");
    str[0] = grid[1][0];
    print(str);
    print(" | ");
    str[0] = grid[1][1];
    print(str);
    print(" | ");
    str[0] = grid[1][2];
    print(str);
    print("\r\n");
    
    print("  ---+---+---\r\n");
    
    print("2  ");
    str[0] = grid[2][0];
    print(str);
    print(" | ");
    str[0] = grid[2][1];
    print(str);
    print(" | ");
    str[0] = grid[2][2];
    print(str);
    print("\r\n\n");
    
}

// Puts a game token in the grid at the position specified by the player
int placetoken(char token, int i, int j) {
    
    if ((grid[i][j] == 0 || grid[i][j] == 32) && (i >= 0 || i < 3 || j >= 0 || j < 3)) {
        grid[i][j] = token;
        return 1;
    }
    else {
        print("\r\nInvalid move!\r\n\n");
        return 0;
    }
    
}

// Checks if one of the players has won
int isgameover(void) {
    
    int i;
    
    for (i = 0; i < 3; i++) {
        
        if (
           (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && (grid[i][0] != 32 && grid[i][0] != 0)) || // lines
           (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && (grid[0][i] != 32 && grid[0][i] != 0))    // columns
           ) {
            return 1;
        }
    }
    
    // diagonals
    if (((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) ||
         (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])) &&
        (grid[1][1] != 32 && grid[1][1] != 0)) {
        return 1;
    }
    else {
        return 0;
    }
    
}

// Returns the game symbol for each player
char getplayertoken(int player) {
    
    if (player == '0') return 'X';
    else return 'O';
    
}

// Alternates between Player 1 and Player 2
char changeplayer(char player) {
	
	if(player == '0')
		return '1';
	else
		return '0';
	
}

void banner() {
	
	print("Tic Tac Toe for KinOS v0.1 (December 2009)\r\n\n");
	print("Type 'q' in both Row and Column fields anytime to quit\r\n\n");
	
}

// Entry point of the game
// (The commented-out sections regarding random numbers are for automatic playing)
void tictactoe(void) {
    
    int i, j, victory, okmove = 0;
    int freespaces;
    char playerstr[2], rowstr[MAX], columnstr[MAX], player;
    
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            grid[i][j] = 32;
        }
    }
    
    banner();
    
    //srand(time(NULL));
    
    printgrid();
    
    freespaces = 9;
    victory = 0;
    player = '0';
    
    // Gets moves from both players until a win condition or tied game is found
    while(victory == 0 && freespaces > 0) {
        
        playerstr[0] = player+1;
        playerstr[1] = 0;
        okmove = 0;
        
        
        while (okmove != 1) {
            print("Player ");
        	print(playerstr);
        	print("\'s move:\r\n\n");
            
            
            print("   Row: ");
            getcommand(rowstr, MAX);
            
            i = (int)(rowstr[0] - 48);
            //i = rand()%3;
            
            print("\n   Column: ");
            getcommand(columnstr, MAX);
            j = (int)(columnstr[0] - 48);
            //j = rand()%3;
            
            if(rowstr[0] == 'q' && columnstr[0] == 'q') {
            	print("\n\nQuitting Tic Tac Toe\r\n\n");
            	return;
            }
            
            okmove = placetoken(getplayertoken(player), i, j);
        }
        
        
        print("\r\n");
        
        freespaces--;
        
        victory = isgameover();
        
        printgrid();
        
        player = changeplayer(player);
        
    }
    
    
    if (victory == 1) {
    	playerstr[0] = changeplayer(player)+1;
        print("A winner is Player ");
        print(playerstr);
        print(" !\r\n\n");
    }
    else {
        print("Tied game!\r\n\n");
    }
    
}

