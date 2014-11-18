// Frederick Lee
// ticTacToeFunc.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"

// two dimensional array basic helpers
void clearTwoDimArray(unsigned char[N][N]);
void printTwoDimArray(unsigned char[N][N]);

// game-specific two dimensional array functions
char validInput(char*, unsigned char[N][N], unsigned char);
unsigned char detectWin(unsigned char[N][N]);
void AIplace(unsigned char[N][N], char[BUF_SIZE]);

// sets all elements of two dimensional array to 0
void clearTwoDimArray(unsigned char twoDimArray[N][N])
{
    unsigned char i, j;

    // traverse two dimensional array
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            // set every value to indicate empty space
            twoDimArray[i][j] = 0;
        }
    }
}

// prints contents of two dimensional array in context of Tic Tac Toe
// odd values printed as [O]
// even values printed as [X]
// 0 printed as [ ]
void printTwoDimArray(unsigned char twoDimArray[N][N])
{
    unsigned char i, j;
    for(i = 0; i < N; i++)
    {
        // print row number
        printf("%d ", i + 1);
        for(j = 0; j < N; j++)
        {
            // print according to value in two dimensional array
            // 0 = empty
            // odd = first player (always starts with Xs)
            // even = second player (always 0s)
            if(twoDimArray[i][j] == 0)
            {
                printf("[ ]");
            } else if(twoDimArray[i][j] % 2) {
                printf("[X]");
            } else {
                printf("[O]");
            }
        }
        printf("\n");
    }

    // print column numbers
    printf("   1  2  3\n");
}

// checks to see if input string is valid. Specifically
//     a) Format of string is correct
//     b) Placement information contained in string is open for placement
// returns 1 for valid. 0 for not valid
char validInput(char* inputToTest, unsigned char twoDimArray[N][N], unsigned char n)
{
    unsigned char firNumValid, midCharSpace, secNumValid, emptySpace;

    unsigned char firCharNum = inputToTest[0] - '0';
    unsigned char secCharNum = inputToTest[2] - '0';

    // string that's too long or too short definitely invalid
    if(strlen(inputToTest) != 3)
    {
        printf("Improper input length\n");
        return 0;
    }
    
    // check string format
    firNumValid = (firCharNum < N + 1) && (firCharNum > 0);
    midCharSpace = (inputToTest[1] == '-');
    secNumValid = (secCharNum < N + 1) && (firCharNum > 0);

    // cite invalid if anything's out of place    
    if(!(firNumValid && midCharSpace && secNumValid))
    {
        printf("Improper format. Must be #-#. # must be between 1, 2, or 3\n");
        return 0;
    }

    // check if the properly formated string refers to an unoccupied space
    emptySpace = twoDimArray[firCharNum - 1][secCharNum - 1] == 0;

    if(!emptySpace)
    {
        printf("That space is occupied. Please choose another.\n");
        return 0;
    }

    return 1;
}

// determines if two dimensional array is in a configuration where
// a player has won
// returns 1 for some win detected
//                 0 for no win detected
unsigned char detectWin(unsigned char twoDimArray[N][N])
{
    unsigned char i, j;
    unsigned char rowCount1, rowCount2, colCount1, colCount2, diaCount1, diaCount2;
    
    unsigned char rowWin = 0, colWin = 0, diaWin = 0;

    // check rows and columns
    for(i = 0; i < N; i++)
    {
        rowCount1 = 0;
        rowCount2 = 0;

        colCount1 = 0;
        colCount2 = 0;
        for(j = 0; j < N; j++)
        {
            // check j columns in ith row for 2 Xs or Os
            // keep track of number
            if(twoDimArray[i][j] != 0) 
            {
                if(twoDimArray[i][j] % 2)
                    rowCount1++;
                else
                    rowCount2++;
            }

            // likewise for j rows in i columns
            if(twoDimArray[j][i] != 0)
            { 
                if(twoDimArray[j][i] % 2)
                    colCount1++;
                else
                    colCount2++;
            }
        }

        // if row count detected 3 Xs or 3 Os, mark win and break    
        if(rowCount1 == N || rowCount2 == N)
        {
            rowWin = 1;
            printf("ROW WIN\n");
            break;
        }

        // if column count detected 3 Xs or 3 Os, mark win and break    
        if(colCount1 == N || colCount2 == N)
        {
            colWin = 1;
            printf("COLUMN WIN\n");
            break;
        }
    } 

    // check diagonals only possible if middle is occupied
    if(twoDimArray[N/2][N/2] != 0)
    {
        // remember X or O for matching
        unsigned char midType = twoDimArray[N/2][N/2] % 2;

        diaCount1 = 1;
        diaCount2 = 1;

        // check if diagonals match middle
        for(i = 0; i < N; i += N - 1)
        {
            if(twoDimArray[i][i] != 0 && (twoDimArray[i][i] % 2 == midType))
            {
                diaCount1++; 
            }
            if(twoDimArray[i][N-1-i] != 0 && (twoDimArray[i][N-1-i] % 2 == midType))
            {
                diaCount2++;
            }
        }

        // if N Xs or N Os detected, mark diagonal win and break 
        if(diaCount1 == N || diaCount2 == N)
        {
            diaWin = 1;
            printf("DIAGONAL WIN\n");
        }
    }

    // any kind of win results in 1
    return rowWin || colWin || diaWin;
}

// determines next location to place AI's X or O
// modifies a string with the properly formatted placement string
void AIplace(unsigned char twoDimArray[N][N], char output[BUF_SIZE])
{
    // declarations
    unsigned char nextRow = 4;
    unsigned char nextCol = 4;

    unsigned char tempRow, tempCol, i, j, numXr, numOr, numXc, numOc, zCol, zRow, curVal;

    // find best coordinates for next move
    for(i = 0; i < N; i++)
    {
        // reset counters
        numXr = 0;
        numOr = 0;
        numXc = 0;
        numOc = 0;

        zCol = 0;
        zRow = 0;
        for(j = 0; j < N; j++)
        {
            // check rows and count Xs and Os
            curVal = twoDimArray[i][j];
            switch(curVal % 2)
            {
                case 0:
                    if(!curVal)
                    {
                        zCol = j;
                    } else {
                        numOr++;
                    }
                    break;
                case 1:
                    numXr++;
                    break;
                default:
                    break;
            }

            // check columns and count Xs and Os
            curVal = twoDimArray[j][i];

            switch(curVal % 2)
            {
                case 0:
                    if(!curVal)
                    {
                        zRow = j;
                    } else {
                        numOc++;
                    }
                    break;
                case 1:
                    numXc++;
                    break;
                default:
                    break;
            }
        }

        // if only 2 Xs or Os in a row, mark empty space and break    
        if((numXr == 2 && numOr == 0) || (numXr == 0 && numOr == 2))
        {
            nextRow = i;
            nextCol = zCol;
        }

        // if only 2 Xs or Os in a column, mark empty space and break    
        if((numXc == 2 && numOc == 0) || (numXc == 0 && numOc == 2))
        {
            nextRow = zRow;
            nextCol = i;
        }
    }
    
    // diagonals left unchecked. achilles heel

    // while randomly generated place invalid
    while(nextRow == 4 || nextCol == 4)
    {
        // random place
        tempRow = rand() % N;
        tempCol = rand() % N;

        if(twoDimArray[tempRow][tempCol] == 0)
        {
            // update nextRow and nextCol
            nextRow = tempRow;
            nextCol = tempCol;
        }
    }

    // put in string (same format as user input) and return
    sprintf(output, "%d %d", nextRow + 1, nextCol + 1);
 
    return;
}
