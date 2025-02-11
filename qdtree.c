#include <stdio.h>
#include <stdlib.h>
#include "qdtree.h"

//cria um objeto POINT de coordenadas (x,y) e retorna-o 
POINT createPoint(float x, float y){
  POINT coord;
  coord.x = x;
  coord.y = y;
  coord.info = '0';
  return coord;
}

//Compara as coordenadas de dois objetos Point, se iguais retorna 1, diferentes 0
int comparePoints(POINT p1, POINT p2){
  if (p1.x == p2.x && p1.y == p2.y)
    return 1;
  return 0;
}

//cria e retorna um apontador do tipo NODE
NODE *createNode(float size, POINT center, NODE *father){
  NODE *node = (NODE *)malloc(sizeof(NODE));
  node->type = QDLEAF;
  node->node.leaf.piece = (SHIP *)malloc(sizeof(SHIP));
  node->node.leaf.piece = NULL;
  node->node.leaf.flag = 0;
  node->half = size / 2;
  node->center = center;
  node->node.quadrant[4] = father;
  node->nsons = 0;

  return node;
}

//recebe um quadrant int e um float x e devolve a coordenada x correta para o ponto central do quadrante
float returnQuadrantX(int quadrant, float x) {
  switch(quadrant) {
    case 0: case 2: return  x / 2;
                  break;
    case 1: case 3: return x / 2 + x;
                  break;
    default: return -1;
            break;
  }
}

//recebe um quadrant int e um float y e devolve a coordenada y correta para o ponto central do quadrante
float returnQuadrantY(int quadrant, float y) {
  switch(quadrant) {
    case 0: case 1: return  y / 2;
          break;
    case 2: case 3: return y / 2 + y;
          break;
    default: return -1;
          break;
  }
}

//recebe um apontador NODE, um objeto POINT, xhalf e yhalf que representam o ponto central da ráiz da QuadTree
//recebe também um char info que queremos guardar no ponto que vamos inserir na árvore
void insert(NODE *node, POINT coord, float xhalf, float yhalf, char info){
  if (node->type == QDLEAF) {
    //se for folha e estiver vazia
    if (node->node.leaf.flag == 0) {
      node->node.leaf.flag = 1;
      node->node.leaf.p = coord;
      node->node.leaf.p.info = info;
      if (node->node.quadrant[4] != NULL) {
        node->node.quadrant[4]->nsons++;
      }
    }else{ //se for folha e estiver preenchida
      POINT temp = node->node.leaf.p;
      node->type = QDNODE;

      node->node.quadrant[0] = createNode(xhalf * 2, createPoint(returnQuadrantX(0, xhalf), returnQuadrantY(0, yhalf)), node);
      node->node.quadrant[1] = createNode(xhalf * 2, createPoint(returnQuadrantX(1, xhalf), returnQuadrantY(1, yhalf)), node);
      node->node.quadrant[2] = createNode(xhalf * 2, createPoint(returnQuadrantX(2, xhalf), returnQuadrantY(2, yhalf)), node);
      node->node.quadrant[3] = createNode(xhalf * 2, createPoint(returnQuadrantX(3, xhalf), returnQuadrantY(3, yhalf)), node);

      if (temp.x <= xhalf && temp.y <= yhalf){
        insert(node->node.quadrant[0], temp, returnQuadrantX(0, xhalf), returnQuadrantY(0, yhalf), info);
      }else if (temp.x > xhalf && temp.y <= yhalf){
        insert(node->node.quadrant[1], temp, returnQuadrantX(1, xhalf) , returnQuadrantY(1, yhalf), info);
      }else if (temp.x <= xhalf && temp.y > yhalf){
        insert(node->node.quadrant[2], temp, returnQuadrantX(2, xhalf), returnQuadrantY(2, yhalf), info);
      }else if (temp.x > xhalf && temp.y > yhalf){
        insert(node->node.quadrant[3], temp, returnQuadrantX(3, xhalf) , returnQuadrantY(3, yhalf), info);
      }

      if (coord.x <= xhalf && coord.y <= yhalf){
        insert(node->node.quadrant[0], coord, returnQuadrantX(0, xhalf), returnQuadrantY(0, yhalf), info);
      }else if (coord.x > xhalf && coord.y <= yhalf){
        insert(node->node.quadrant[1], coord, returnQuadrantX(1, xhalf) , returnQuadrantY(1, yhalf), info);
      }else if (coord.x <= xhalf && coord.y > yhalf){
        insert(node->node.quadrant[2], coord, returnQuadrantX(2, xhalf), returnQuadrantY(2, yhalf), info);
      }else if (coord.x > xhalf && coord.y > yhalf){
        insert(node->node.quadrant[3], coord, returnQuadrantX(3, xhalf) , returnQuadrantY(3, yhalf), info);
      }
    }
  }

  //caso seja um nó
  else if (node->type == QDNODE){
    if (coord.x <= xhalf && coord.y <= yhalf){
      insert(node->node.quadrant[0], coord, returnQuadrantX(0, xhalf), returnQuadrantY(0, yhalf), info);
    }else if (coord.x > xhalf && coord.y <= yhalf){
      insert(node->node.quadrant[1], coord, returnQuadrantX(1, xhalf) , returnQuadrantY(1, yhalf), info);
    }else if (coord.x <= xhalf && coord.y > yhalf){
      insert(node->node.quadrant[2], coord, returnQuadrantX(2, xhalf), returnQuadrantY(2, yhalf), info);
    }else if (coord.x > xhalf && coord.y > yhalf){
      insert(node->node.quadrant[3], coord, returnQuadrantX(3, xhalf) , returnQuadrantY(3, yhalf), info);
    }
  }
}

//Recebe um apontador NODE para a raíz e uma coordenada, retorna 1 se encontrar um ponto associado a essa coordenada na árvore, 0 senão
int searchCoord(NODE *tree, POINT coord){
  switch (tree->type){
  case QDLEAF:
    if ((tree->node.leaf.flag == 1) && (comparePoints(coord, tree->node.leaf.p) == 1)) {
      return 1;
    }
    break;
  case QDNODE:
    if (coord.x <= tree->center.x && coord.y <= tree->center.y) {
      return searchCoord(tree->node.quadrant[0], coord);
    }
    if (coord.x > tree->center.x && coord.y <= tree->center.y) {
      return searchCoord(tree->node.quadrant[1], coord);
    }
    if (coord.x <= tree->center.x && coord.y > tree->center.y) {
      return searchCoord(tree->node.quadrant[2], coord);
    }
    if (coord.x > tree->center.x && coord.y > tree->center.y) {
      return searchCoord(tree->node.quadrant[3], coord);
    };
    break;
    default:
     return 0;
    break;
  }
  return 0;
  }

//sabendo que já existe uma coordenada na árvore, a função retorna o nó onde o ponto se encontra
NODE *getNode(NODE *node, POINT coord){
  switch (node->type) {
  case QDLEAF:
      return node;
    break;
  case QDNODE:
    if (coord.x <= node->center.x && coord.y <= node->center.y){
      return getNode(node->node.quadrant[0], coord);
    }
    if (coord.x > node->center.x && coord.y <= node->center.y){
      return getNode(node->node.quadrant[1], coord);
    }
    if (coord.x <= node->center.x && coord.y > node->center.y){
      return getNode(node->node.quadrant[2], coord);
    }
    if (coord.x > node->center.x && coord.y > node->center.y){
      return getNode(node->node.quadrant[3], coord);
    }
  default:
    return NULL;
    break;
  }
}

//recebe um apontador do tipo NODE da raíz da árvore e o tamanho da mesma, e imprime a board de jogo
void PrintBoard(NODE *player, int size)
{
  POINT tempPoint;

  printf("   x");
  for (int i = 0; i < size; i++)
  {
    if (i < 10)
      printf(" %d ", i);
    else
      printf("%d ", i);
  }
  printf("\n  y\n");
  for (int y = 0; y < size; y++)
  {
    if (y < 10)
      printf("  %d  ", y);
    else
      printf(" %d  ", y);
    for (int x = 0; x < size; x++)
    {
      tempPoint = createPoint(x, y);

      if (searchCoord(player, tempPoint) == 1)
      {
        NODE* tempNode = getNode(player, tempPoint);
        switch(tempNode->node.leaf.p.info){
          
          case 'C': case 'B': case 'R': case 'S': case 'D': //Bold Yellow
          printf("\033[1;33m");
          printf("%c  ", tempNode->node.leaf.p.info);
          printf("\033[0m");
          break;

          case 1: //Bold Yellow
          printf("\033[1;33m");
          printf("%d  ", tempNode->node.leaf.p.info);
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
      } else {
        printf("\033[0;34m");
        printf("0  ");
        printf("\033[0m");
      }
    }
    printf("\n");
  }
  printf("\n");
}

//não é usada no programa, mas serve para imprimir todos os níveis da árvore, se um nó é folha ou não, e a sua informação
void printTree(NODE *tree, int level){
  switch (tree->type)
  {
  case QDLEAF:
    printf("%d \t LEAF \t center (%f, %f) \t info: %d \t half: %f \t sons: %d\n", level, tree->center.x, tree->center.y, tree->center.info, tree->half, tree->nsons);
    printf("\t coord (%f, %f) \t flag: %d \t info: %d \n", tree->node.leaf.p.x, tree->node.leaf.p.y, tree->node.leaf.flag, tree->node.leaf.p.info);
    break;
  case QDNODE:
    printf("%d \t NODE \t center (%f, %f) \t info: %d \t half: %f \t sons: %d\n", level, tree->center.x, tree->center.y, tree->center.info, tree->half, tree->nsons);
    level++;
    printTree(tree->node.quadrant[0], level);
    printTree(tree->node.quadrant[1], level);
    printTree(tree->node.quadrant[2], level);
    printTree(tree->node.quadrant[3], level);

  default:
    break;
  }
}

//função recursiva, recebe um apontador do tipo NODE para a raíz da árvore e liberta a memória para todos os seus nós
void EraseBoardData(NODE *player){
  
  switch (player->type){
  
  case QDLEAF:
  free(player);
  break;

  case QDNODE:
  EraseBoardData(player->node.quadrant[0]);
  EraseBoardData(player->node.quadrant[1]);
  EraseBoardData(player->node.quadrant[2]);
  EraseBoardData(player->node.quadrant[3]);
  break;

  default:
  break;
  }
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

//Recebe o mapa do jogador que está a inserir, a peça que quer inserir e o tamanho do mapa. Retorna 1 se for inserida com sucesso, 0 se alguma parte do barco for inválida.
//px e py: coordenadas da peça
//mx e my: coordenadas da matriz
//nx e ny: coordenadas novas
//O pivô da peça é o ponto central, equivalente à coordenada (2,2)
int InsertPiece(NODE *player, SHIP piece, int size, int mx, int my, int orientation, char tipo){
	if(orientation < 0 || orientation > 3) return 0;

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
			POINT coord= createPoint(nx,ny);
			coord.info=piece.bitmap[py*5+px];

      if(searchCoord(player,coord)) {//&& (nx < 0 || nx >= size || ny < 0 || ny >= size)){
        piece = original;
        return 0;
      }
      
      if(coord.info != '0' && (nx < 0 || nx >= size || ny < 0 || ny >= size)) {
        piece = original;
        return 0;
      }
		}
  }
 //Sabendo que todas as posições são válidas, falta apenas inserir
  	for(int py = 0; py < 5; py++){
    	for(int px = 0; px < 5; px++){
      		nx = mx + px - 2;
      		ny = my + py - 2;
        if(piece.bitmap[py*5+px] != '0'){
          POINT coord=createPoint(nx,ny);
          insert(player,coord,size/2,size/2, tipo);
      	}
    	}  
  	}
  	return 1; 
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
