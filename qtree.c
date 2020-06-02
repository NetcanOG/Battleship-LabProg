#include <stdio.h>
#include <stdlib.h>

typedef struct Ship
{ //bitmap em que cada posição tem um valor, 0 = empty, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
  char bitmap[26];
} SHIP;

typedef struct POINT
{
  float x, y;
  int info; //0 = empty, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
} POINT;

typedef enum
{
  QDNODE,
  QDLEAF
} QD_TNODE;

typedef struct NODE
{
  QD_TNODE type; // defines the type of node (internal node or leaf)
  POINT center;
  float half; //half of the size of the board/square
  int nsons;  //número de filhos (folhas preenchidas ou nós)

  union {

    struct NODE *quadrant[5]; //quadrant[4] não é um quadrante, é o nó pai
                              /* struct NODE *NW;    // internal node    
    struct NODE *NE;
    struct NODE *SW;
    struct NODE *SE; */
    //struct NODE *father;

    struct
    {

      SHIP *piece; // pointer to piece, if there is any

      POINT p; // coords of the board cell

      int flag; //0 se a folha estiver vazia, 1 se estiver preenchida

    } leaf; //  almost a board cell together with its coordinates

  } node;

} NODE;

POINT createPoint(float x, float y)
{
  POINT coord;
  coord.x = x;
  coord.y = y;
  coord.info = 0;
  return coord;
}

//se igual retorna 1, diferente 0
int comparePoints(POINT p1, POINT p2)
{
  if (p1.x == p2.x && p1.y == p2.y)
    return 1;
  return 0;
}

NODE *createNode(float size, POINT center, NODE *father)
{
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


float returnQuadrantX(int quadrant, float x) {
  switch(quadrant) {
    case 0:
    case 2:
      return  x / 2;
      break;
    case 1:
    case 3:
      return x / 2 + x;
      break;
    default:
      return -1;
      break;
  }
}

float returnQuadrantY(int quadrant, float y) {
  switch(quadrant) {
    case 0:
    case 1:
      return  y / 2;
      break;
    case 2:
    case 3:
      return y / 2 + y;
      break;
    default:
      return -1;
      break;
  }
}

void insert(NODE *node, POINT coord, float xhalf, float yhalf)
{

  if (node->type == QDLEAF)
  {
    //printf("LEAF\n");
    //se for folha e estiver vazia
    if (node->node.leaf.flag == 0)
    {
      node->node.leaf.flag = 1;
      node->node.leaf.p = coord;
      node->node.leaf.p.info = 1;
      if (node->node.quadrant[4] != NULL)
      {
        node->node.quadrant[4]->nsons++;
      }
    }
    else
    { //se for folha e estiver preenchida
      POINT temp = node->node.leaf.p;
      //printf("coord: %f %f\n", coord.x, coord.y);
      //printf("temp: %f %f\n", node->node.leaf.p.x, node->node.leaf.p.y);
      node->type = QDNODE;

      node->node.quadrant[0] = createNode(xhalf * 2, createPoint(returnQuadrantX(0, xhalf), returnQuadrantY(0, yhalf)), node);
      //printf("Quadrant[0] (%f, %f)\n", returnQuadrantX(Q, xhalf), returnQuadrantY(Q, yhalf));
      node->node.quadrant[1] = createNode(xhalf * 2, createPoint(returnQuadrantX(1, xhalf), returnQuadrantY(1, yhalf)), node);
      //printf("Quadrant[1] (%f, %f)\n", returnQuadrantX(Q, xhalf), returnQuadrantY(Q, yhalf) + yhalf);
      node->node.quadrant[2] = createNode(xhalf * 2, createPoint(returnQuadrantX(2, xhalf), returnQuadrantY(2, yhalf)), node);
      //printf("Quadrant[2] (%f, %f)\n", returnQuadrantX(Q, xhalf) + xhalf, returnQuadrantY(Q, yhalf));
      node->node.quadrant[3] = createNode(xhalf * 2, createPoint(returnQuadrantX(3, xhalf), returnQuadrantY(3, yhalf)), node);
      //printf("Quadrant[3] (%f, %f)\n", returnQuadrantX(Q, xhalf) + xhalf, returnQuadrantY(Q, yhalf) + yhalf);

      if (temp.x <= xhalf && temp.y <= yhalf)
      {
        insert(node->node.quadrant[0], temp, returnQuadrantX(0, xhalf), returnQuadrantY(0, yhalf));
      }
      else if (temp.x > xhalf && temp.y <= yhalf)
      {
        insert(node->node.quadrant[1], temp, returnQuadrantX(1, xhalf) , returnQuadrantY(1, yhalf));
      }
      else if (temp.x <= xhalf && temp.y > yhalf)
      {
        insert(node->node.quadrant[2], temp, returnQuadrantX(2, xhalf), returnQuadrantY(2, yhalf));
      }
      else if (temp.x > xhalf && temp.y > yhalf)
      {
        insert(node->node.quadrant[3], temp, returnQuadrantX(3, xhalf) , returnQuadrantY(3, yhalf));
      }

      if (coord.x <= xhalf && coord.y <= yhalf)
      {
        insert(node->node.quadrant[0], coord, returnQuadrantX(0, xhalf), returnQuadrantY(0, yhalf));
      }
      else if (coord.x > xhalf && coord.y <= yhalf)
      {
        insert(node->node.quadrant[1], coord, returnQuadrantX(1, xhalf) , returnQuadrantY(1, yhalf));
      }
      else if (coord.x <= xhalf && coord.y > yhalf)
      {
        insert(node->node.quadrant[2], coord, returnQuadrantX(2, xhalf), returnQuadrantY(2, yhalf));
      }
      else if (coord.x > xhalf && coord.y > yhalf)
      {
        insert(node->node.quadrant[3], coord, returnQuadrantX(3, xhalf) , returnQuadrantY(3, yhalf));
      }
    }
  }

  //caso seja um nó
  else if (node->type == QDNODE)
  {
    if (coord.x <= xhalf && coord.y <= yhalf)
    {
      insert(node->node.quadrant[0], coord, returnQuadrantX(0, xhalf), returnQuadrantY(0, yhalf));
    }
    else if (coord.x > xhalf && coord.y <= yhalf)
    {
      insert(node->node.quadrant[1], coord, returnQuadrantX(1, xhalf) , returnQuadrantY(1, yhalf));
    }
    else if (coord.x <= xhalf && coord.y > yhalf)
    {
      insert(node->node.quadrant[2], coord, returnQuadrantX(2, xhalf), returnQuadrantY(2, yhalf));
    }
    else if (coord.x > xhalf && coord.y > yhalf)
    {
      insert(node->node.quadrant[3], coord, returnQuadrantX(3, xhalf) , returnQuadrantY(3, yhalf));
    }
  }
}

//retorna 1 se encontrar a coordenada, 0 senão
int searchCoord(NODE *tree, POINT coord)
{
  switch (tree->type)
  {
  case QDLEAF:
    if ((tree->node.leaf.flag == 1) && (comparePoints(coord, tree->node.leaf.p) == 1)) {
      //printf("FLAG=1 (%f, %f) \t COORD (%f, %f)\n",tree->node.leaf.p.x,tree->node.leaf.p.y, coord.x, coord.y);
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

NODE *getNode(NODE *node, POINT coord)
{
  switch (node->type) {
  case QDLEAF:
      return node;
    break;
  case QDNODE:
    if (coord.x <= node->center.x && coord.y <= node->center.y)
    {
      return getNode(node->node.quadrant[0], coord);
    }
    if (coord.x > node->center.x && coord.y <= node->center.y)
    {
      return getNode(node->node.quadrant[1], coord);
    }
    if (coord.x <= node->center.x && coord.y > node->center.y)
    {
      return getNode(node->node.quadrant[2], coord);
    }
    if (coord.x > node->center.x && coord.y > node->center.y)
    {
      return getNode(node->node.quadrant[3], coord);
    }
  default:
    return NULL;
    break;
  }
}

//retorna 0 se removeu com sucesso, 1 se falhou
int removeCoord(NODE *node, POINT coord)
{

  if (searchCoord(node, coord) == 1)
  {
    return 1;
  }
  else
  {

    NODE *target = getNode(node, coord);
    NODE *father = target->node.quadrant[4];
    father->nsons--;

    //free(target->node.quadrant[0]);
    //free(target->node.quadrant[1]);
    //free(target->node.quadrant[2]);
    //free(target->node.quadrant[3]);

    POINT tempPoint;
    SHIP *tempShip;

    if (father->nsons == 1)
    {
      if (father->node.quadrant[0]->node.leaf.flag == 1)
      {
        tempPoint = father->node.quadrant[0]->node.leaf.p;
        tempShip = father->node.quadrant[0]->node.leaf.piece;
      }
      else if (father->node.quadrant[1]->node.leaf.flag == 1)
      {
        tempPoint = father->node.quadrant[1]->node.leaf.p;
        tempShip = father->node.quadrant[1]->node.leaf.piece;
      }
      else if (father->node.quadrant[2]->node.leaf.flag == 1)
      {
        tempPoint = father->node.quadrant[2]->node.leaf.p;
        tempShip = father->node.quadrant[2]->node.leaf.piece;
      }
      else if (father->node.quadrant[3]->node.leaf.flag == 1)
      {
        tempPoint = father->node.quadrant[3]->node.leaf.p;
        tempShip = father->node.quadrant[3]->node.leaf.piece;
      }
      father->type = QDLEAF;
      father->node.leaf.flag = 1;
      father->node.leaf.p = tempPoint;
      father->node.leaf.piece = tempShip;
      father->nsons = 0;
    }
    else if (father->nsons == 0)
    {
      father->type = QDLEAF;
      father->node.leaf.flag = 0;
    }
  }
}

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
        printf("\033[1;33m");
        printf("%d  ", tempNode->node.leaf.p.info);
        printf("\033[0m");
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

void printTree(NODE *tree, int level)
{
  switch (tree->type)
  {
  case QDLEAF:
    printf("%d \t LEAF \t center (%f, %f) \t info: %d \t half: %f \t sons: %d\n", level, tree->center.x, tree->center.y, tree->center.info, tree->half, tree->nsons);
    printf("\t coord (%f, %f) \t flag: %d \t info: %d \n", tree->node.leaf.p.x, tree->node.leaf.p.y, tree->node.leaf.flag, tree->node.leaf.p.info);
    break;
  case QDNODE:
    printf("%d \t NODE \t center (%f, %f) \t info: %d \t half: %f \t sons: %d\n", level, tree->center.x, tree->center.y, tree->center.info, tree->half, tree->nsons);
    //printf("\t coord (%f, %f) \t flag: %d \n", tree->node.leaf.p.x, tree->node.leaf.p.y, tree->node.leaf.flag, tree->node.leaf.p.info);
    level++;
    printTree(tree->node.quadrant[0], level);
    printTree(tree->node.quadrant[1], level);
    printTree(tree->node.quadrant[2], level);
    printTree(tree->node.quadrant[3], level);

  default:
    break;
  }
}

int main()
{

  float size = 20;
  POINT center = createPoint(9.5, 9.5);
  NODE *root = createNode(size, center, NULL);

  POINT numbahone = createPoint(0.0, 0.0);
  POINT numbahtwo = createPoint(1.0, 0.0);
  POINT numbahthree = createPoint(2.0, 0.0);
  POINT numbahfour = createPoint(3.0, 0.0);

  insert(root, numbahone, size / 2, size / 2);
  //printTree(root, 0);
  insert(root, numbahtwo, size / 2, size / 2);
  insert(root, numbahthree, size / 2, size / 2);
  insert(root, numbahfour, size / 2, size / 2);
  //printTree(root, 0);
  PrintBoard(root, size);

  return 0;
}