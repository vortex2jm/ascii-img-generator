all:
	@gcc -c *.c
	@gcc -o prog *.o

clean:
	@rm -rf *.o prog
