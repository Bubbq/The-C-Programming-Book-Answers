all:
	gcc CH4/main.c -o run -lm -Wall

clean:
	rm run	
	clear