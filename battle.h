int getHP(BOARD* player); 
void printEnemyBoard(BOARD* player);
int checkValidPosition(int size, int x, int y);
void shootEnemy(BOARD* enemy, int HP);
void playerTurn(BOARD* player, BOARD* enemy, int playernumber, int HP);
