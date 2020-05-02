#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
#include "game.h"

//função que recebe a board de um jogador e retorna um int com o valor de peças de
//barcos não destruídas (HP, Health Points)
int getHP(BOARD* player){
  int hp = 0, size = player->size;
	size *= size;

	for(int i = 0; i < size; i++){
		if(player->map[i].posinfo == '1') hp++;
	}
	return hp;
}

//Se na posição estiver um barco ou água, imprime 0 em ambos os casos. 2 se algum tiro tiver acertado, 3 se foi um tiro falhado
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

int checkValidPosition(int size, int x, int y){ 
  if(x < size && x >= 0 && y < size && y >= 0){
    return 0;
	}
	return 1;
}

//0 = water, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
void shootEnemy(BOARD* enemy){
  int x, y;
  printf("\nInput x and y for coordinates you want to attack!");
	printf("\nx: ");
	scanf("%d", &x);
  printf("\ny: ");
	scanf("%d", &y);
	printf("\n");

	if(checkValidPosition(enemy->size, x, y) == 0){
		switch (enemy->map[y*enemy->size + x].posinfo){
		case '0':
			printf("Water hit!\n");
			enemy->map[y*enemy->size + x].posinfo = '3';
			break;

		case '1':
			printf("Piece hit!\n");
			enemy->map[y*enemy->size + x].posinfo = '2';
			break;

		case '2':
			printf("You already hit a piece there! Try again.\n");
			shootEnemy(enemy);
			break;
			
		case '3':
			printf("You already shot there and missed... Try again.\n");
			shootEnemy(enemy);
			break;		
		}
	}
	else{
		printf("\nInvalid input! Try again!\n");
		shootEnemy(enemy);
	}
}

void playerTurn(BOARD* player, BOARD* enemy, int playernumber){
  Title();
	//mostrar qual o jogador
	printf("\nJOGADOR %d\n", playernumber);
	//----------------------------
	PrintBoard(player, player->size);
	printEnemyBoard(enemy);
	shootEnemy(enemy);
}