// Frederick Lee
// ticTacToe.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "modes.h"

int main(int argc, char** argv)
{
    // declarations
    char** curParam = argv+1;

    // parse out options and arguments
    if(argc == 2) 
    {
        switch(*(*curParam + 1))
        {
            case 'h':
                printHelp();
                break;
            case 's':
                printf("BEGINNING SINGLE PLAYER MODE\n");
                singlePlayer();
                break;
            case 'm':
                printf("BEGINNING MULTIPLAYER MODE\n");
                multiPlayer();
                break;
            default:
                printf("ERROR: UNKNOWN OPTION. see help with -h\n");
                break;
        }
    } else {
        printf("ERROR: improper number of arguments. precisely\n");
        printf("one argument required. see help with -h\n");
        return -1;
    }

    return 0;
}
