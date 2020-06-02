#include <stdio.h>
#include <stdlib.h>
#include "qdtree.h"

POINT createPoint(float x, float y)
{
  POINT coord;
  coord.x = x;
  coord.y = y;
  coord.info = '0';
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
      node->node.leaf.p.info = '1';
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

      node->node.quadrant[0] = createNode(xhalf * 2, createPoint(xhalf / 2, yhalf / 2), node);
      //printf("Quadrant[0] (%f, %f)\n", xhalf / 2, yhalf / 2);
      node->node.quadrant[1] = createNode(xhalf * 2, createPoint(xhalf / 2 + xhalf, yhalf / 2), node);
      //printf("Quadrant[1] (%f, %f)\n", xhalf / 2, yhalf / 2 + yhalf);
      node->node.quadrant[2] = createNode(xhalf * 2, createPoint(xhalf / 2, yhalf / 2), node);
      //printf("Quadrant[2] (%f, %f)\n", xhalf / 2 + xhalf, yhalf / 2);
      node->node.quadrant[3] = createNode(xhalf * 2, createPoint(xhalf / 2 + xhalf, yhalf / 2 + yhalf), node);
      //printf("Quadrant[3] (%f, %f)\n", xhalf / 2 + xhalf, yhalf / 2 + yhalf);

      if (temp.x <= xhalf && temp.y <= yhalf)
      {
        insert(node->node.quadrant[0], temp, xhalf / 2, yhalf / 2);
      }
      else if (temp.x <= xhalf && temp.y > yhalf)
      {
        insert(node->node.quadrant[1], temp, xhalf / 2 + xhalf, yhalf / 2);
      }
      else if (temp.x > xhalf && temp.y <= yhalf)
      {
        insert(node->node.quadrant[2], temp, xhalf / 2, yhalf / 2 + yhalf);
      }
      else if (temp.x > xhalf && temp.y > yhalf)
      {
        insert(node->node.quadrant[3], temp, xhalf / 2 + xhalf, yhalf / 2 + yhalf);
      }

      if (coord.x <= xhalf && coord.y <= yhalf)
      {
        insert(node->node.quadrant[0], coord, xhalf / 2, yhalf / 2);
      }
      else if (coord.x <= xhalf && coord.y > yhalf)
      {
        insert(node->node.quadrant[1], coord, xhalf / 2 + xhalf, yhalf / 2);
      }
      else if (coord.x > xhalf && coord.y <= yhalf)
      {
        insert(node->node.quadrant[2], coord, xhalf / 2, yhalf / 2 + yhalf);
      }
      else if (coord.x > xhalf && coord.y > yhalf)
      {
        insert(node->node.quadrant[3], coord, xhalf / 2 + xhalf, yhalf / 2 + yhalf);
      }
    }
  }

  //caso seja um nó
  else if (node->type == QDNODE)
  {
    if (coord.x <= xhalf && coord.y <= yhalf)
    {
      insert(node->node.quadrant[0], coord, xhalf / 2, yhalf / 2);
    }
    else if (coord.x <= xhalf && coord.y > yhalf)
    {
      insert(node->node.quadrant[1], coord, xhalf / 2 + xhalf, yhalf / 2);
    }
    else if (coord.x > xhalf && coord.y <= yhalf)
    {
      insert(node->node.quadrant[2], coord, xhalf / 2, yhalf / 2 + yhalf);
    }
    else if (coord.x > xhalf && coord.y > yhalf)
    {
      insert(node->node.quadrant[3], coord, xhalf / 2 + xhalf, yhalf / 2 + yhalf);
    }
  }
}

//retorna 1 se encontrar a coordenada, 0 senão
int searchCoord(NODE *root, POINT coord)
{
  switch (root->type)
  {
  case QDLEAF:
    if ((root->node.leaf.flag == 1) && (comparePoints(coord, root->node.leaf.p) == 1))
    {
      // printf("FLAG=1 (%f, %f) \t COORD (%f, %f)\n",root->node.leaf.p.x,root->node.leaf.p.y, coord.x, coord.y);
      return 1;
    }
    break;
  case QDNODE:
    if (coord.x <= root->center.x && coord.y <= root->center.y)
    {
      return searchCoord(root->node.quadrant[0], coord);
    }
    if (coord.x <= root->center.x && coord.y > root->center.y)
    {
      return searchCoord(root->node.quadrant[1], coord);
    }
    if (coord.x > root->center.x && coord.y <= root->center.y)
    {
      return searchCoord(root->node.quadrant[2], coord);
    }
    if (coord.x > root->center.x && coord.y > root->center.y)
    {
      return searchCoord(root->node.quadrant[3], coord);
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
  switch (node->type)
  {
  case QDLEAF:
    return node;
    break;
  case QDNODE:
    if (coord.x <= node->center.x && coord.y <= node->center.y)
    {
      return getNode(node->node.quadrant[0], coord);
    }
    if (coord.x <= node->center.x && coord.y > node->center.y)
    {
      return getNode(node->node.quadrant[1], coord);
    }
    if (coord.x > node->center.x && coord.y <= node->center.y)
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

void prune(NODE* current){
  if(current->node.quadrant[4]->nsons == 1){
    NODE* father = current->node.quadrant[4];
    father->type = QDLEAF;
    father->node.leaf.flag = 1;
    father->node.leaf.p = current->node.leaf.p;
    father->node.leaf.piece = current->node.leaf.piece;
    father->nsons = 0;
    prune(father);
  }
}

//retorna 0 se falhar
int removeCoord(NODE *node, POINT coord)
{

  if (searchCoord(node, coord) == 0)
  {
    return 0;
  }
  else
  {
    NODE *target = getNode(node, coord);
    NODE *father = target->node.quadrant[4];

    POINT tempPoint;
    SHIP *tempShip;

    if (father->nsons > 2)
    {
      if (coord.x <= father->center.x && coord.y <= father->center.y)
      {
        target->node.leaf.flag = 0;
        target->node.leaf.p.info = '0';
      }
      else if (coord.x <= father->center.x && coord.y > father->center.y)
      {
        target->node.leaf.flag = 0;
        target->node.leaf.p.info = '0';
      }
      else if (coord.x > father->center.x && coord.y <= father->center.y)
      {
        target->node.leaf.flag = 0;
        target->node.leaf.p.info = '0';
      }
      else if (coord.x > father->center.x && coord.y > father->center.y)
      {
        target->node.leaf.flag = 0;
        target->node.leaf.p.info = '0';
      }
      free(target);
      father->nsons--;
    }

    else if (father->nsons == 2)
    {
      if (coord.x <= father->center.x && coord.y <= father->center.y)
      {
        target->node.leaf.flag = 0;
        target->node.leaf.p.info = '0';
      }
      else if (coord.x <= father->center.x && coord.y > father->center.y)
      {
        target->node.leaf.flag = 0;
        target->node.leaf.p.info = '0';
      }
      else if (coord.x > father->center.x && coord.y <= father->center.y)
      {
        target->node.leaf.flag = 0;
        target->node.leaf.p.info = '0';
      }
      else if (coord.x > father->center.x && coord.y > father->center.y)
      {
        target->node.leaf.flag = 0;
        target->node.leaf.p.info = '0';
      }

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
      free(target);
      prune(father);
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
        NODE *tempNode = getNode(player, tempPoint);
        printf("\033[1;33m");
        printf("%c  ", tempNode->node.leaf.p.info);
        printf("\033[0m");
      }
      else
      {
        printf("\033[0;34m");
        printf("0  ");
        printf("\033[0m");
      }
    }

    printf("\n");
  }
  printf("\n");
}

void printTree(NODE *root, int level)
{
  switch (root->type)
  {
  case QDLEAF:
    //printf("%d \t LEAF \t center (%f, %f) \t info: %c \t half: %f \t sons: %d\n", level, root->center.x, root->center.y, root->center.info, root->half, root->nsons);
    printf("\t coord (%f, %f) \t flag: %d \t info: %c \n", root->node.leaf.p.x, root->node.leaf.p.y, root->node.leaf.flag, root->node.leaf.p.info);
    break;
  case QDNODE:
    //printf("%d \t NODE \t center (%f, %f) \t info: %c \t half: %f \t sons: %d\n", level, root->center.x, root->center.y, root->center.info, root->half, root->nsons);
    //printf("\t coord (%f, %f) \t flag: %d \n", root->node.leaf.p.x, root->node.leaf.p.y, root->node.leaf.flag, root->node.leaf.p.info);
    level++;
    printTree(root->node.quadrant[0], level);
    printTree(root->node.quadrant[1], level);
    printTree(root->node.quadrant[2], level);
    printTree(root->node.quadrant[3], level);

  default:
    break;
  }
}