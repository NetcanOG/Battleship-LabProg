BOARD** OpMainMenu();
void OpRules();
void Rules(); 
BOARD** Game();
BOARD** AutoCoord(int npTipos[],int size);
void InsertBoatA(int np,int npTipos[],BOARD *player,int size,SHIP *ships);
BOARD** ManualCoord(int npTipos[],int size);
int InsertPiece(BOARD *player,BOARD *apresent,SHIP piece,int size,int mx,int my,int orientation, char tipo);
void PrintBoard(BOARD *player,int size);
void InsertBoatM(int np,int npTipos[],BOARD *player,int size,SHIP *ships);
char ValModo(); 
int ValTab();
void NPieces(int *nptpieces,int tabu);

 