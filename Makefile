all: structs.o game.o battle.o battleship

structs.o: structs.c
	gcc -c -Wall -Werror -fpic structs.c

game.o: game.c structs.o
	gcc -c -Wall -fpic game.c 

battle.o: battle.c game.o structs.o
	gcc -c -Wall -fpic battle.c

battleship: battle.o structs.o game.o battleship.c
	gcc -Wall -Werror -fpic battleship.c battle.o structs.o game.o -o battleship

clean:
	rm -f *.o battleship
