#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "qdtree.h"
#include "qdgame.h"  
#include "qdbattle.h"

//função que recebe a board de um jogador e retorna um int com o valor de peças de barcos não destruídas 
//(HP, Health Points)
int getHP(NODE* player){
	int hp = 0;

	switch (player->type){
		case QDLEAF:
			switch (player->node.leaf.p.info){
				case 'C': case 'B':case 'R':case 'S':case 'D':
					return 1;
					break;
				
				default:
				return 0;
					break;
				}
			break;
		case QDNODE:
			return hp + getHP(player->node.quadrant[0]) + getHP(player->node.quadrant[1]) + getHP(player->node.quadrant[2]) + getHP(player->node.quadrant[3]);
		default:
			break;
	}
	return 0;
}

//Função que imprime certas informações sobre a board inimiga. Se na posição estiver um barco ou água, imprime 0 em ambos os casos. 2 se algum tiro tiver acertado, 3 se foi um tiro falhado
void printEnemyBoard(NODE* player){  
  POINT tempPoint;
  int size = player->half*2;

  printf("   x");
  for (int i = 0; i < size; i++){
    if (i < 10)
    printf(" %d ", i);
    else
    printf("%d ", i);
  }
  printf("\n  y\n");
  for (int y = 0; y < size; y++){
    if (y < 10)
    printf("  %d  ", y);
    else
    printf(" %d  ", y);
    for (int x = 0; x < size; x++){
      tempPoint = createPoint(x, y);
      
      if (searchCoord(player, tempPoint) == 1){
        NODE* tempNode = getNode(player, tempPoint);
        switch(tempNode->node.leaf.p.info){
          
          case 'C': case 'B': case 'R': case 'S': case 'D': //Blue
			printf("\033[0;34m");
			printf("0  ");
			printf("\033[0m");
			break;
          case 1: //Blue
			printf("\033[0;34m");
			printf("0  ");
			printf("\033[0m");
			break;
          case '0': //Blue
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
			printf("%c  ", tempNode->node.leaf.p.info);
			break;
        }
      }else{
        printf("\033[0;34m");
        printf("0  ");
        printf("\033[0m");
      }
    }
    printf("\n");
  }
  printf("\n");
}

//Função que verifica se uma coordenada (x,y) é válida para um determinado size de uma board. Retorna 1 se sim, 0 se não.
int checkValidPosition(int size, int x, int y){  
  	if(x < size && x >= 0 && y < size && y >= 0){
    	return 1;
	}
	return 0;
}
 
//Função que ao receber um tabuleiro inimigo (NODE* enemy), pede ao jogador para o atacar. Em caso de escolher coordenadas já utilizadas antes ou fora do mapa, repete a função. 
//0 = water, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
void shootEnemy(NODE* enemy, int HP){
	int x, y;
	printf("----------------------------------------------------------------------------------------------------------------------------\n");
	printf("   Ainda lhe falta");
	printf("\033[1;31m"); printf(" %d ",HP); printf("\033[0m");
	printf("peças de barcos para destruir!\n");

  	printf("\nColoque em  x e y as coordenadas que quer atacar!\n");
	printf("X: ");	scanf("%d", &x); for(int c=0; (c=getchar()) != '\n' && c!= EOF;);
  	printf("Y: ");	scanf("%d", &y); for(int c=0; (c=getchar()) != '\n' && c!= EOF;);
	printf("\n\n\n");

	POINT target= createPoint(x,y);

	if(checkValidPosition(enemy->half*2, x, y) == 1){
		if(searchCoord(enemy,target)==1){
			NODE* tempnode=getNode(enemy,target);
			char info=tempnode->node.leaf.p.info;
			switch (info){
				case 'C': case 'B': case 'R': case 'S': case 'D':
					printf("\033[1;31m");
					printf("Peça atingida!\n\n");
					tempnode->node.leaf.p.info = '2';
					printf("\033[0m");
					break;
				case '2':
					printf("\033[1;33m");
					printf("Já atingiu esta peça! Tente novamente.\n\n");
					printf("\033[0m");
					shootEnemy(enemy,HP);
					break;
				case '3':
					printf("\033[1;33m");
					printf("Você já atirou lá e errou ... Tente novamente.\n\n");
					printf("\033[0m");
					shootEnemy(enemy,HP);
					break;		
			}
		}else{
			printf("\033[1;34m");
			printf("Água atingida!\n\n");
			insert(enemy,target,enemy->half,enemy->half, '3');
			printf("\033[0m");
		}		
	}else{
		printf("\033[1;33m");
		printf("\nEntrada inválida! Tente novamente!\n");
		printf("\033[0m");
		shootEnemy(enemy,HP);
	}
	printf("----------------------------------------------------------------------------------------------------------------------------\n");
}

//Função que mostra a informação necessária ao jogador no seu turno, como por exemplo o seu tabuleiro e os tiros falhados e acertados.
void playerTurn(NODE* player, NODE* enemy, int playernumber, int HP){
	//mostrar qual o jogador
  	printf("\033[1;32m");
	printf("\t\t\t  JOGADOR %d: \n\n", playernumber);
	printf("\033[0m");

	//----------------------------
	PrintBoard(player, player->half*2);
	printEnemyBoard(enemy);
	shootEnemy(enemy, HP);
}
