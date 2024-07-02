all:
	gcc exercises.c -o run -lm -Wall

clean:
	rm run	
	clear