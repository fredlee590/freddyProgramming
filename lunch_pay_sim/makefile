lunch_pay_sim : main.o pNodeFunc.o lunchSimFunc.o
	gcc -Wall -g -o lunch_pay_sim pNodeFunc.o main.o lunchSimFunc.o
main.o : main.c pNodeFunc.h lunchSimFunc.h
	gcc -Wall -g -c main.c
pNodeFunc.o : pNodeFunc.c pNode.h
	gcc -Wall -g -c pNodeFunc.c
lunchSimFunc.o : lunchSimFunc.c pNode.h
	gcc -Wall -g -c lunchSimFunc.c
clean:
	rm -f *.o
	rm -f lunch_pay_sim
