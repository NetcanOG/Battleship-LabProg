void OpMenu();
void OpRegras();
void Regras();
void Jogo();
void AutoCoord(int npTipos[],int size);
void InsertBoatA(int np,int npTipos[],BOARD *player,int size,SHIP *ships);
void ManualCoord(int npTipos[],int size);
int InsertPiece(BOARD *player,SHIP piece,int size,int mx,int my,int orientation);
void PrintBoard(BOARD *player,int size);
void InsertBoatM(int np,int npTipos[],BOARD *player,int size,SHIP *ships);
char ValModo();
int ValTab();
void NPieces(int *nptpieces,int tabu);
void WaitForPlayer();
void Menu();
void Pieces();
void Title();