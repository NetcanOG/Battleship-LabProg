#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
#include "game.h" 

//função que recebe a board de um jogador e retorna um int com o valor de peças de barcos não destruídas (HP, Health Points)
int getHP(BOARD* player){
	int hp = 0, size = player->size;
	size *= size;

	for(int i = 0; i < size; i++){
		if(player->map[i].posinfo == '1') 
			hp++;
	}
	return hp;
}

//Função que imprime certas informações sobre a board inimiga. Se na posição estiver um barco ou água, imprime 0 em ambos os casos. 2 se algum tiro tiver acertado, 3 se foi um tiro falhado
void printEnemyBoard(BOARD* player){
	int size = player->size;
	printf("    ");
	for(int i = 0; i < size; i++){
		if(i < 10)
			printf(" %d ", i);
		else
			printf("%d ", i); 
	}
	printf("\n\n");

	for(int y = 0; y < size; y++){
		if(y < 10)
			printf("  %d  ", y);
		else
			printf(" %d  ", y);  

		for(int x = 0; x < size; x++){
		  switch (player->map[y*size+x].posinfo){
		    case '0': //Blue
			        printf("\033[0;34m");
			        printf("0  ");
			        printf("\033[0m");
		    		break;
		    case '1': //Blue
			        printf("\033[0;34m");
			        printf("0  ");
			        printf("\033[0m");
			        break;
		    case '2': //Bold Red
			        printf("\033[1;31m");
			        printf("2  ");
			        printf("\033[0m");
		    		break;
		    case '3': //Green
			        printf("\033[0;32m");
			        printf("3  ");
			        printf("\033[0m");
			        break;
		    default: //Branco (sem definições)
			        printf("%c  ", player->map[y*size + x].posinfo);
			        break;
		  }
		}
		printf("\n");
	}
	printf("\n");
}

//Função que verifica se uma coordenada (x,y) é válida para um determinado size de uma board. Retorna 0 se sim, 1 se não.
int checkValidPosition(int size, int x, int y){ 
  	if(x < size && x >= 0 && y < size && y >= 0){
    	return 0;
	}
	return 1;
}

//Função que ao receber um tabuleiro inimigo (BOARD* enemy), pede ao jogador para o atacar. Em caso de escolher coordenadas já utilizadas antes ou fora do mapa, repete a função. 
//0 = water, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
void shootEnemy(BOARD* enemy){
	int x, y;
  	printf("\nColoque em  x e y as coordenadas que quer atacar!\n");
	printf("X: ");	scanf("%d", &x); for(int c=0; (c=getchar()) != '\n' && c!= EOF;);
  	printf("Y: ");	scanf("%d", &y); for(int c=0; (c=getchar()) != '\n' && c!= EOF;);
	printf("\n\n\n");


	if(checkValidPosition(enemy->size, x, y) == 0){
		switch (enemy->map[y*enemy->size + x].posinfo){
		case '0':
			printf("\033[1;34m");
			printf("Água atingida!\n\n");
			enemy->map[y*enemy->size + x].posinfo = '3';
			printf("\033[0m");
			break;

		case '1':
			printf("\033[1;31m");
			printf("Peça atingida!\n\n");
			enemy->map[y*enemy->size + x].posinfo = '2';
			printf("\033[0m");
			break;

		case '2':
			printf("\033[1;33m");
			printf("Já atingiu está peça! Tente novamente.\n\n");
			printf("\033[0m");
			shootEnemy(enemy);
			break;
			
		case '3':
			printf("\033[1;33m");
			printf("Você já atirou lá e errou ... Tente novamente.\n\n");
			printf("\033[0m");
			shootEnemy(enemy);
			break;		
		}
		
	}
	else{
		printf("\033[1;33m");
		printf("\nEntrada inválida! Tente novamente!\n");
		printf("\033[0m");
		shootEnemy(enemy);
	}
	
}

//Função que mostra a informação necessária ao jogador no seu turno, como por exemplo o seu tabuleiro e os tiros falhados e acertados.
void playerTurn(BOARD* player, BOARD* enemy, int playernumber){
	//mostrar qual o jogador

  	printf("\033[1;32m");
	printf("\t\t\t  JOGADOR %d: \n\n", playernumber);
	printf("\033[0m");

	//----------------------------
	PrintBoard(player, player->size);
	printEnemyBoard(enemy);
	shootEnemy(enemy);
}
