lunch_pay_sim : main.o pNodeFunc.o
	gcc -Wall -g -o lunch_pay_sim pNodeFunc.o main.o 
main.o : main.c pNodeFunc.h
	gcc -Wall -g -c main.c
pNodeFunc.o : pNodeFunc.c pNode.h
	gcc -Wall -g -c pNodeFunc.c
clean:
	rm -f *.o
	rm -f lunch_pay_sim
