#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "graphics.h"
#include "qdtree.h"
#include "qdgame.h"
#include "qdbattle.h"


int main(){
	MainMenu(); 
	NODE **players; 
	NODE* player1;
	NODE* player2;

	players = OpMainMenu();

	player1 = players[1];
	player2 = players[2];
	
	//guardamos os valores iniciais da vida de cada jogador (deve ser iguais no primeiro turno)
	int HP1 = getHP(player1);
	int HP2 = getHP(player2);
	
	//flag que nos diz qual é o jogador atual
	int playerFlag = (1 + (rand() % 2));

	//Apresentação do Jogo
	Title();
	Layout();

	WaitForPlayer(playerFlag);

	while(HP1 != 0 && HP2 != 0){ 
	    switch (playerFlag)	{
			case 1:
			playerTurn(player1, player2, playerFlag,HP2);
			HP2 = getHP(player2);
			playerFlag = 2;
			break;
			
			case 2:
			playerTurn(player2, player1, playerFlag,HP1);	
			HP1 = getHP(player1);
			playerFlag = 1;
			break;
		}
		//Mudança de jogador-----
		ChangePlayer();
		WaitForPlayer(playerFlag);
	}

	if(playerFlag == 1)  Win(2);
	if(playerFlag == 2)  Win(1);

	EraseBoardData(player1);
	EraseBoardData(player2);
	
	return 0;
}