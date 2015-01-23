GCC = gcc -Wall -g

sillyEncryption : main.o sillyEncryptionFunc.o
	$(GCC) -o sillyEncryption main.o sillyEncryptionFunc.o
main.o : main.c sillyEncryptionFunc.h
	$(GCC) -c main.c
sillyEncryptionFunc.o : sillyEncryptionFunc.c sillyEncryptionFunc.h
	$(GCC) -c sillyEncryptionFunc.c
clean:
	rm -f *.o
	rm -f sillyEncryption

debug: GCC += -DDEBUG
debug: sillyEncryption
