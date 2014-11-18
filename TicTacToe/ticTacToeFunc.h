#ifndef TICTACTOEFUNC_H
#define TICTACTOEFUNC_H

// two dimensional array basic helpers
void clearTwoDimArray(unsigned char[N][N]);
void printTwoDimArray(unsigned char[N][N]);

// game-specific two dimensional array functions
char validInput(char*, unsigned char[N][N], unsigned char);
unsigned char detectWin(unsigned char[N][N]);
void AIplace(unsigned char[N][N], char[BUF_SIZE]);

#endif
