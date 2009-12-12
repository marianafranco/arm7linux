#include "tictactoe.h"

#define	ISDIGIT(c) ((c >= 48 && c <= 57))
#define MAX 2

void printgrid(char grid[3][3]) {
    
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

int placetoken(char grid[3][3], char token, int i, int j) {
    
    if (grid[i][j] != ' ' || i < 0 || i > 2 || j < 0 || j > 2) {
        print("Invalid move!\r\n\n");
        return 0;
    }
    else {
        grid[i][j] = token;
        return 1;
    }
    
}

int isgameover(char grid[3][3]) {
    
    int i;
    
    for (i = 0; i < 3; i++) {
        
        if (
           (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ') || // lines
           (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ')    // columns
           ) {
            return 1;
        }
    }
    
    // diagonals
    if ((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) ||
        (grid[0][2] == grid[1][1] && grid[1][1] == grid[0][2]) &&
        (grid[1][1] != ' ')) {
        return 1;
    }
    else {
        return 0;
    }
    
}

char getplayerchar(int player) {
    
    if (player == 0) return 'X';
    else return 'O';
    
}

void tictactoe() {
    
    int i, j, player = 0, victory, okmove = 0;
    int freespaces;
    char grid[3][3], playerstr[2], rowstr[MAX], columnstr[MAX];
    
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            grid[i][j] = ' ';
        }
    }
    
    printgrid(grid);
    
    freespaces = 9;
    victory = 0;
    
    while(!victory && freespaces > 0) {
        
        playerstr[0] = (char)(player + 48);
        playerstr[1] = 0;
        okmove = 0;
        
        while (!okmove) {
            print("Player ");
        	print(playerstr);
        	print("\'s move:\r\n\n");
            
            print("   Row: \r");
            getcommand(rowstr);
            i = (int)(rowstr[0] - 48);
            
            print("\n   Column: ");
            getcommand(columnstr);
            j = (int)(columnstr[0] - 48);
            
            okmove = placetoken(grid, getplayerchar(player), i, j);
        }
        
        print("\r\n");
        
        freespaces--;
        
        victory = isgameover(grid);
        
        printgrid(grid);
        
        player = !player;
        
    }
    
    if (victory) {
    	playerstr[0] = (char)(player+1);
        print("A winner is ");
        print(playerstr);
        print(" !\r\n\n");
    }
    else {
        print("Tied game!\n\n");
    }
    
}

