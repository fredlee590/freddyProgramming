lunch_pay_sim : lunch_pay_sim.o pNodeFunc.o
	gcc -Wall -g -o lunch_pay_sim pNodeFunc.o lunch_pay_sim.o 
lunch_pay_sim.o : lunch_pay_sim.c pNodeFunc.h
	gcc -Wall -g -c lunch_pay_sim.c
pNodeFunc.o : pNodeFunc.c pNode.h
	gcc -Wall -g -c pNodeFunc.c
clean:
	rm -f *.o
