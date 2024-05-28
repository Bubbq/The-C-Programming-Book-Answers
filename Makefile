all:
	gcc CH2/main.c -o run -lm -Wall

clean:
	rm run	
	clear