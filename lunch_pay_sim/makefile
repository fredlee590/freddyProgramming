GCC = gcc -Wall -g

lunch_pay_sim : main.o pNodeFunc.o lunchSimFunc.o
	$(GCC) -o lunch_pay_sim pNodeFunc.o main.o lunchSimFunc.o
main.o : main.c pNodeFunc.h lunchSimFunc.h
	$(GCC) -c main.c
pNodeFunc.o : pNodeFunc.c pNode.h
	$(GCC) -c pNodeFunc.c
lunchSimFunc.o : lunchSimFunc.c pNode.h
	$(GCC) -c lunchSimFunc.c
clean:
	rm -f *.o
	rm -f lunch_pay_sim

debug: GCC += -DDEBUG
debug: lunch_pay_sim
