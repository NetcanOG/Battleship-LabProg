#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
/*
typedef struct Ship{   //bitmap em que cada posição tem um valor, 0 = empty, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
	char bitmap[26];
} SHIP;
typedef struct Cell{
	SHIP *shippointer;   //apontador para o navio, pode ser NULL
	char posinfo;	   //variável position_information (pos_info), 0 = no shot, 1 = shot that didn't hit, 2 = shot that hit an enemy piece
} CELL;
typedef struct Board{
	int size; 
	CELL *map;
} BOARD;
*/

BOARD *BuildBoard(int size){
  BOARD* player;
	player = (BOARD*) malloc(sizeof(BOARD));
	player->size = size;
	size = size*size;
	player->map = (CELL*) malloc(size * sizeof(CELL));
	for(int i = 0; i < size; i++){
		player->map[i].posinfo = '0';
		player->map[i].shippointer = NULL;
	}
	return player;
}

//Expressão matemática para a board: posição = y * comprimento + x
void PrintBoard(BOARD *player, int size){
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
					      printf("%c  ", player->map[y*size + x].posinfo);
					      printf("\033[0m");
					      break;
			      case '1': //Bold Yellow
					      printf("\033[1;33m");
					      printf("%c  ", player->map[y*size + x].posinfo);
					      printf("\033[0m");
					      break;
			      case '2': //Bold Red
					      printf("\033[1;31m");
					      printf("%c  ", player->map[y*size + x].posinfo);
					      printf("\033[0m");
					      break;
			      case '3': //Green
					      printf("\033[0;32m");
					      printf("%c  ", player->map[y*size + x].posinfo);
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

BOARD* EraseBoardData(BOARD* player, int size){

  size *= size;

	for(int i = 0; i < size; i++){
		if(player->map[i].posinfo != '0'){
			player->map[i].posinfo = '0';
			player->map[i].shippointer = NULL;
		}
	} 
	
	return player;
}

//Recebe e imprime uma peça 5x5
void PrintPiece(SHIP piece){
	for(int y = 0; y < 5; y++){
	    for(int x = 0; x < 5; x++){
	    	printf("%c ", piece.bitmap[y*5 + x]);
	    }
    	printf("\n");
  	}
  	printf("\n");
}

//Recebe uma peça 5x5, roda-a 90 graus e copia a rotação para uma nova peça, que será retornada
SHIP RotatePiece90(SHIP piece){
  	int i = 0;
  	SHIP newpiece;
  	for(int y = 0; y < 5; y++){
    	for(int x = 0; x < 5; x++){
      		newpiece.bitmap[i] = piece.bitmap[20 + y - (x*5)];
      		i++;
    	}
  	}
  	return newpiece;
}

//Recebe uma peça 5x5, roda-a 180 graus e copia a rotação para uma nova peça, que será retornada
SHIP RotatePiece180(SHIP piece){
	int i = 0;
  	SHIP newpiece;
  	for(int y = 0; y < 5; y++){
    	for(int x = 0; x < 5; x++){
     		newpiece.bitmap[i] = piece.bitmap[24 - (y*5) - x];
      		i++;
    	}
  	}
  return newpiece;
}

//Recebe uma peça 5x5, roda-a 270 graus e copia a rotação para uma nova peça, que será retornada
SHIP RotatePiece270(SHIP piece){
	int i = 0;
	SHIP newpiece;
	for(int y = 0; y < 5; y++){
		for(int x = 0; x < 5; x++){
	  		newpiece.bitmap[i] = piece.bitmap[4 - y + (x*5)];
	  		i++;
		}
	}
	return newpiece;
}

//Recebe o mapa do jogador que está a inserir, a peça que quer inserir e o tamanho do mapa. Retorna 0 se for inserida com sucesso, 1 se alguma parte do barco for inválida.
//px e py: coordenadas da peça
//mx e my: coordenadas da matriz
//nx e ny: coordenadas novas
//O pivô da peça é o ponto central, equivalente à coordenada (2,2)
int InsertPiece(BOARD *player, SHIP piece, int size, int mx, int my, int orientation){
	if(orientation < 0 || orientation > 3) return 1;

  	SHIP original = piece;

 	switch (orientation){
	   	case 0:break;
	   	case 1:piece = RotatePiece90(piece);
	   			break;
	   	case 2:piece = RotatePiece180(piece);
				break;
	   	case 3:piece = RotatePiece270(piece);
	   			break;
	}
  //Primeiro verificamos se todos os pontos onde queremos inserir a peça são válidos, basta um não ser para retornar erro
  int nx,ny;
	for(int py = 0; py < 5; py++){
		for(int px = 0; px < 5; px++){
		  	nx = mx + px - 2;
		  	ny = my + py - 2; 
		  	if((player->map[ny * size + nx].posinfo == '1' && piece.bitmap[py * 5 + px] == '1') || (piece.bitmap[py * 5 + px] == '1' && (nx < 0 || nx >= size || ny < 0 || ny >= size))){
		    	piece = original;
		    	return 1;
		  	}
		}
	}

 // y * comp + x
 //Sabendo que todas as posições são válidas, falta apenas inserir
  	for(int py = 0; py < 5; py++){
    	for(int px = 0; px < 5; px++){
      		nx = mx + px - 2;
      		ny = my + py - 2;
			if(piece.bitmap[py * 5 + px] == '1')
      			player->map[ny * size + nx].posinfo = '1';        
    	}
  	}
  	return 0; 
}

/*
Ships:
Destroyer:
   0 1 2 3 4
0  0 0 0 0 0
1  0 0 0 0 0
2  0 0 1 0 0
3  0 0 1 0 0
4  0 0 0 0 0 
0000000000001000010000000 
Submarine:
   0 1 2 3 4
0  0 0 0 0 0
1  0 0 0 0 0
2  0 0 1 0 0
3  0 0 1 0 0
4  0 0 1 0 0 
0000000000001000010000100 
Cruiser:
   0 1 2 3 4
0  0 0 0 0 0
1  0 0 0 0 0
2  0 0 1 1 0
3  0 0 1 0 0
4  0 0 1 0 0 
0000000000001100010000100 
Battleship:
   0 1 2 3 4
0  0 0 0 0 0
1  0 0 1 0 0
2  0 0 1 0 0
3  0 0 1 0 0
4  0 0 1 0 0 
0000000100001000010000100
Carrier:
   0 1 2 3 4
0  0 0 0 0 0
1  0 0 1 1 0
2  0 0 1 1 0
3  0 0 1 0 0
4  0 0 1 0 0 
0000000110001100010000100 
*/
