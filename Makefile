all: structs.o game.o battleship

structs.o: structs.c
	gcc -c -Wall -Werror -fpic structs.c

game.o: game.c structs.o
	gcc -c -Wall -fpic game.c 

battleship: structs.o game.o battleship.c
	gcc -Wall -Werror -fpic battleship.c structs.o game.o -o battleship

clean:
	rm -f *.o battleship
