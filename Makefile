all: graphics.o qdtree.o qdgame.o structs.o game.o battle.o battleship quadbattleship

graphics.o: graphics.c
	gcc -g -c -Wall -Werror -fpic graphics.c

qdtree.o: qdtree.c graphics.o	
	gcc -g -c -Wall -Werror -fpic qdtree.c

qdgame.o: qdgame.c qdtree.o graphics.o	
	gcc -g -c -Wall -Werror -fpic qdgame.c

qdbattle.o: qdbattle.c qdgame.o qdtree.o graphics.o	
	gcc -g -c -Wall -Werror -fpic qdbattle.c

structs.o: structs.c graphics.o
	gcc -g -c -Wall -Werror -fpic structs.c

game.o: game.c structs.o graphics.o
	gcc -g -c -Wall -fpic game.c 

battle.o: battle.c game.o structs.o graphics.o
	gcc -g -c -Wall -fpic battle.c

battleship: battle.o structs.o game.o battleship.c graphics.o
	gcc -g -Wall -Werror -fpic battleship.c graphics.o battle.o structs.o game.o -o battleship

quadbattleship: qdtree.o qdbattle.o qdgame.o quadbattleship.c graphics.o
	gcc -g -Wall -Werror -fpic quadbattleship.c graphics.o qdtree.o qdgame.o qdbattle.o -o quadbattleship	

clean:
	rm -f *.o battleship
	rm -f *.o quadbattleship
