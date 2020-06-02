#include <stdio.h>
#include <stdlib.h>

typedef struct Ship
{ //bitmap em que cada posição tem um valor, 0 = empty, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
  char bitmap[26];
} SHIP;

typedef struct POINT
{
  float x, y;
  char info; //0 = empty, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
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

    // quadrant[0] = NW
    // quadrant[1] = SW
    // quadrant[2] = NE
    // quadrant[3] = SE

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
  coord.info = '0';
  return coord;
}

POINT createPoint(float x, float y);
int comparePoints(POINT p1, POINT p2);
NODE *createNode(float size, POINT center, NODE *father);
void insert(NODE *node, POINT coord, float xhalf, float yhalf);
int searchCoord(NODE *root, POINT coord);
NODE *getNode(NODE *node, POINT coord);
void prune(NODE* current);
int removeCoord(NODE *node, POINT coord);
void PrintBoard(NODE *player, int size);
void printTree(NODE *root, int level);
