ticTacToe : ticTacToe.o modes.o ticTacToeFunc.o
	gcc -Wall -g -o ticTacToe ticTacToe.o modes.o ticTacToeFunc.o
ticTacToe.o : ticTacToe.c modes.h
	gcc -Wall -g -c ticTacToe.c
modes.o : modes.c ticTacToeFunc.h common.h
	gcc -Wall -g -c modes.c
ticTacToeFunc.o : ticTacToeFunc.c common.h
	gcc -Wall -g -c ticTacToeFunc.c

clean:
	rm -f *.o
