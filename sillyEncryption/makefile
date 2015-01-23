GCC = gcc -Wall -g

sillyEncryption : main.o
	$(GCC) -o sillyEncryption main.o
main.o : main.c
	$(GCC) -c main.c
clean:
	rm -f *.o
	rm -f sillyEncryption

debug: GCC += -DDEBUG
debug: sillyEncryption
