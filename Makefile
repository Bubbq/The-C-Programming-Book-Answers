all:
	gcc CH5/main.c -o run -lm -Wall

clean:
	rm run	
	clear