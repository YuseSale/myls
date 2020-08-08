all : myls

myls.o : myls.c
	gcc -c myls.c

clean :
	rm myls *.o
