

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

int InsertPiece(BOARD *player,SHIP piece,int size,int mx,int my,int orientation);
SHIP RotatePiece270(SHIP piece);
SHIP RotatePiece180(SHIP piece);
SHIP RotatePiece90(SHIP piece);
void PrintPiece(SHIP piece);
BOARD *EraseBoardData(BOARD *player,int size);
void PrintBoard(BOARD *player,int size);
BOARD *BuildBoard(int size);
