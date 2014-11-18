// Frederick Lee
// modes.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"
#include "ticTacToeFunc.h"

// main categories
void printHelp(void);
void singlePlayer(void);
void multiPlayer(void);

void printHelp(void)
{
    printf("---- HELP DOCUMENTATION ----\n");
    printf("This is a command line game of the\n");
    printf("classic Tic Tac Toe. Here's how to play:\n");

    printf("\n");

    printf("To run the game, one must select an option:\n");
    printf("ticTacToe [option]\n");
    printf("-h - Bring up this help documentation. Congrats!\n");
    printf("         You found it!\n");
    printf("-s - Enter single player mode. Man vs. Machine!\n");
    printf("-m - Enter multiplayer mode. Is it man against man?!\n");
    printf("         Can any nation staaand alooooooone!?\n");
    printf("         Yes and probably not.\n");

    printf("\n");

    printf("Once the game is started, just follow these easy steps\n");
    printf("on the path to victory! Or defeat, probably.\n");

    printf("\n");

    printf("Single player mode:\n");
    printf("You, the player, and the computer take turns placing Xs or\n");
    printf("Os. Who is who is determined at random once the game starts.\n");
    printf("You will be prompted for a row and column for each placement.\n");
    printf("Make sure you place the right thing, though, or you'll have\n");
    printf("to try again!\n");

    printf("\n");

    printf("Multi player mode:\n");
    printf("Same as Single player mode, except you'll be prompted for\n");
    printf("every move on the tic tac toe board. Presumably you'll let\n");
    printf("your friend play instead of screwing up his or her moves while\n");
    printf("he or she is in the bathroom!\n");

    printf("\n");

    printf("Now happy hunting!\n");
}

void singlePlayer(void){
    // declarations
    unsigned char keepGoing, nextRow, nextCol, playerTurn;
    char nextMove[BUF_SIZE];

    unsigned char win = 0; // 1 for player got three in a row, 0 otherwise
    unsigned char turnNum = 0; // 1 to n^2 for total turns
    
    unsigned char ticTacToeTable[N][N];
    
    // intialize and display ticTacToe array
    clearTwoDimArray(ticTacToeTable);
    printTwoDimArray(ticTacToeTable);
    
    // first, randomly decide who is going first, human or player
    srand(time(NULL));
    playerTurn = rand() % 2;

    // loop until a player wins or maximum amount of turns reached
    while(!win && turnNum++ < N*N)
    {
        // alternate between players
        switch(playerTurn)
        {
            case 0: // computer turn
                printf("Computer's Turn %d\n", turnNum);

                // calculate next best position to move
                AIplace(ticTacToeTable, nextMove);
 
             // set to player's turn
                playerTurn = 1;
                break;
            case 1:
                printf("Player's Turn %d\n", turnNum);
	do{
                    // accept user input for row and column
                    printf("Enter a row and column (1 to 3) to place, in that\n");
                    printf("order, with a dash in between the two numbers.\n");

                    scanf("%s", nextMove);
                    
                    // validate input
                    keepGoing = !validInput(nextMove, ticTacToeTable, turnNum);
                } while(keepGoing);


                // set to computer's turn
                playerTurn = 0;
                break;
            default:
                break;
        }

        nextRow = nextMove[0] - '1';
        nextCol = nextMove[2] - '1';

        // update tic tac toe table
        ticTacToeTable[nextRow][nextCol] = turnNum;

        // check for win
        win = detectWin(ticTacToeTable);
        // print tic tac toe table
        printTwoDimArray(ticTacToeTable);
    }

    if(win)
        printf("WINNER WINNER CHICKEN DINNER!!\n");
    else
        printf("NO WINNER!!\n"); 
}

void multiPlayer(void){
    // declarations
    unsigned char keepGoing, nextRow, nextCol;
    char nextMove[BUF_SIZE];

    unsigned char playerTurn = 0; // keeps track of player turn
    unsigned char win = 0; // 1 for player got three in a row, 0 otherwise
    unsigned char turnNum = 0; // 1 to n^2 for total turns
    
    unsigned char ticTacToeTable[N][N];
    
    // intialize and display ticTacToe array
    clearTwoDimArray(ticTacToeTable);
    printTwoDimArray(ticTacToeTable);
    
    // loop until a player wins or maximum amount of turns reached
    while(!win && turnNum++ < N*N)
    {
        // alternate between players
        switch(playerTurn)
        {
            case 0: // computer turn
                printf("Player 1's Turn %d\n", turnNum);

                playerTurn = 1;
                break;
            case 1:
                printf("Player 2's Turn %d\n", turnNum);

                // set to player 1's turn
                playerTurn = 0;
                break;
            default:
                break;
        }

        do{
            // accept user input for row and column
            printf("Enter a row and column (1 to 3) to place, in that\n");
            printf("order, with a dash in between the two numbers.\n");

            scanf("%s", nextMove);
                    
            // validate input
            keepGoing = !validInput(nextMove, ticTacToeTable, turnNum);
        } while(keepGoing);

        nextRow = nextMove[0] - '1';
        nextCol = nextMove[2] - '1';

        // update tic tac toe table
        ticTacToeTable[nextRow][nextCol] = turnNum;

        // check for win
        win = detectWin(ticTacToeTable);

        // print tic tac toe table
        printTwoDimArray(ticTacToeTable);
    }

    if(win)
        printf("WINNER WINNER CHICKEN DINNER!!\n");
    else
        printf("NO WINNER!!\n"); 
}
