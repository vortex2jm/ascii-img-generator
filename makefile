all:
	@gcc -c *.c
	@gcc -o prog *.o -lpng

clean:
	@rm -rf *.o prog
