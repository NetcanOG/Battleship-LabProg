#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ship{
  //bitmap em que cada posição tem um valor, 0 = empty, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
  char bitmap[26];
} SHIP;

typedef struct Cell{
  //apontador para o navio, pode ser NULL
  SHIP *shippointer;
  //variável position_information (pos_info), 0 = no shot, 1 = shot that didn't hit, 2 = shot that hit an enemy piece
  char posinfo;
} CELL;

typedef struct Board{
  int player;
  CELL *map;
} BOARD;


BOARD *build_board(int size, BOARD *player){
  size = size*size;
  
  player = (BOARD*) malloc(sizeof(BOARD));
  
  player->map = (CELL*) malloc(size * sizeof(CELL));
  for(int i = 0; i < size; i++){
    player->map[i].posinfo = '0';
    player->map[i].shippointer = NULL;
  }
  return player;
}

//expressão matemática para a board: posição = y * comprimento + x
void print_board(BOARD *player, int size){
  
  printf("   ");
  for(int i = 0; i < size; i++){
    if(i < 10)
    printf("0%d ", i);
    else
    printf("%d ", i); 
  }
  printf("\n\n");
  
  for(int y = 0; y < size; y++){
    if(y < 10)
    printf("0%d  ", y);
    else
    printf("%d  ", y);

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
    printf("\n\n");
  }
  printf("\n");
}

//recebe e imprime uma peça 5x5
void print_piece(SHIP piece){
  for(int y = 0; y < 5; y++){
    for(int x = 0; x < 5; x++){
      printf("%c ", piece.bitmap[y*5 + x]);
    }
    printf("\n");
  }
  printf("\n");
}

//recebe uma peça 5x5, roda-a 90 graus e copia a rotação para uma nova peça, que será retornada
SHIP rotate_piece90(SHIP piece){
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

//recebe uma peça 5x5, roda-a 180 graus e copia a rotação para uma nova peça, que será retornada
SHIP rotate_piece180(SHIP piece){
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

//recebe uma peça 5x5, roda-a 270 graus e copia a rotação para uma nova peça, que será retornada
SHIP rotate_piece270(SHIP piece){
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

//recebe o mapa do jogador que está a inserir, a peça que quer inserir e o tamanho do mapa. Retorna 0 se for inserida com sucesso, 1 se alguma parte do barco for inválida.
//px e py: coordenadas da peça
//mx e my: coordenadas da matriz
//nx e ny: coordenadas novas
//O pivô da peça é o ponto central, equivalente à coordenada (2,2)
int insert_piece(BOARD *player, SHIP piece, int size, int mx, int my){
 
  //if(mx < 0 || mx >= size || my < 0 || my >= size) return 1;
  
  //Primeiro verificamos se todos os pontos onde queremos inserir a peça são válidos, basta um não ser para retornar erro
  int nx,ny;
  for(int py = 0; py < 5; py++){
    for(int px = 0; px < 5; px++){
      nx = mx + px - 2;
      ny = my + py - 2;
      
      if((player->map[ny * size + nx].posinfo == '1' && piece.bitmap[py * 5 + px] == '1') || (piece.bitmap[py * 5 + px] == '1' && (nx < 0 || nx >= size || ny < 0 || ny >= size))){
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
0  1 0 0 0 0
1  1 0 0 0 0
2  0 0 0 0 0
3  0 0 0 0 0
4  0 0 0 0 0 
Submarine:
   0 1 2 3 4
0  1 0 0 0 0
1  1 0 0 0 0
2  1 0 0 0 0
3  0 0 0 0 0
4  0 0 0 0 0 
Cruiser:
   0 1 2 3 4
0  1 1 0 0 0
1  1 0 0 0 0
2  1 0 0 0 0
3  0 0 0 0 0
4  0 0 0 0 0 
Battleship:
   0 1 2 3 4
0  1 0 0 0 0
1  1 0 0 0 0
2  1 0 0 0 0
3  1 0 0 0 0
4  0 0 0 0 0 
Carrier:
   0 1 2 3 4
0  1 1 0 0 0
1  1 1 0 0 0
2  1 0 0 0 0
3  1 0 0 0 0
4  0 0 0 0 0 
*/

int main(){

  SHIP Destroyer; strcpy(Destroyer.bitmap, "1000010000000000000000000");
  SHIP Submarine; strcpy(Submarine.bitmap, "1000010000100000000000000");
  SHIP Cruiser; strcpy(Cruiser.bitmap, "1100010000100000000000000");
  SHIP Battleship; strcpy(Battleship.bitmap, "1000010000100001000000000");
  SHIP Carrier; strcpy(Carrier.bitmap, "1100011000100001000000000");

  int size;
  printf("Map size: ");
  scanf("%d", &size);
  printf("\n");
  BOARD *player1;
  
  player1 = build_board(size, player1);

  print_board(player1, size);

  SHIP testpiece = Carrier;

  int x, y;
  printf("X coord: "); scanf("%d", &x);
  printf("Y coord: "); scanf("%d", &y);
  printf("\n");

  //testpiece = rotate_piece90(testpiece);
  //testpiece = rotate_piece180(testpiece);
  //testpiece = rotate_piece270(testpiece);

  if(insert_piece(player1, testpiece, size, x, y) == 0) 
  print_board(player1, size);
  else
  printf("Erro!\n");
  return 0;
}
