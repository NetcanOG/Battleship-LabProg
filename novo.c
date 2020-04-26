#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct Ship{   //bitmap em que cada posição tem um valor, 0 = empty, 1 = piece without being hit, 2 = piece hit, 3 = missed shot
	char bitmap[26];
} SHIP;

typedef struct Cell{
	SHIP *shippointer;   //apontador para o navio, pode ser NULL
	char posinfo;	   //variável position_information (pos_info), 0 = no shot, 1 = shot that didn't hit, 2 = shot that hit an enemy piece
} CELL;

typedef struct Board{
	int player;
	CELL *map;
} BOARD;


BOARD *BuildBoard(int size, BOARD *player){
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

BOARD* erase_board_data(BOARD* player, int size){

  size *= size;

	for(int i = 0; i < size; i++){
		if(player->map[i].posinfo != '0'){
			player->map[i].posinfo = '0';
			player->map[i].shippointer = NULL;
		}
	} 
	
	return player;
}

//recebe e imprime uma peça 5x5
void PrintPiece(SHIP piece){
	for(int y = 0; y < 5; y++){
	    for(int x = 0; x < 5; x++){
	    	printf("%c ", piece.bitmap[y*5 + x]);
	    }
    	printf("\n");
  	}
  	printf("\n");
}

//recebe uma peça 5x5, roda-a 90 graus e copia a rotação para uma nova peça, que será retornada
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

//recebe uma peça 5x5, roda-a 180 graus e copia a rotação para uma nova peça, que será retornada
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

//recebe uma peça 5x5, roda-a 270 graus e copia a rotação para uma nova peça, que será retornada
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

//recebe o mapa do jogador que está a inserir, a peça que quer inserir e o tamanho do mapa. Retorna 0 se for inserida com sucesso, 1 se alguma parte do barco for inválida.
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



//TITULO DO JOGO
void Title(){
	system("clear");
	printf("\033[1;34m");
	printf ("   _____     ___    _____   _____   _       ____   ____   _   _   _   _____ \n");
	printf ("  |  __ |   | _ |  |_   _| |_   _| | |     |  __| |  __| | | | | | | |  _  |\n");
	printf ("  | |__| | | | | |   | |     | |   | |     | |_   | |__  | |_| | | | | |_| |\n");
	printf ("  |  __ |  | |_| |   | |     | |   | |     |  _|  |__  | |  _  | | | |  ___|\n"); 
	printf ("  | |__| | |  _  |   | |     | |   | |___  | |__   __| | | | | | | | | |    \n");
	printf ("  |_____|  |_| |_|   |_|     |_|   |_____| |____| |____| |_| |_| |_| |_| M&P\n");
	printf("\033[0m");
	printf("\n");
}
//TIPOS DE PECAS DISPONIVEIS
void Pieces(){
	printf("        ___________________________________________________________\n");
	printf("  ID   |     C     |     B     |     R     |     S     |     D     |\n");
	printf(" Nome  |  Carrier  |Battleship |  Cruiser  | Submarine | Destroyer |\n");
	printf("Tamanho|     6     |     4     |     4     |     3     |     2     |\n");
	printf("       |-----------|-----------|-----------|-----------|-----------|\n");
	printf("       | _ _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ |\n");
	printf("       | _ _ X X _ | _ _ X _ _ | _ _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ |\n");
	printf("       | _ _ X X _ | _ _ X _ _ | _ _ X X _ | _ _ X _ _ | _ _ X _ _ |\n");
	printf("       | _ _ X _ _ | _ _ X _ _ | _ _ X _ _ | _ _ X _ _ | _ _ X _ _ |\n");
	printf("       | _ _ X _ _ | _ _ X _ _ | _ _ X _ _ | _ _ X _ _ | _ _ _ _ _ |\n");
	printf("       |___________|___________|___________|___________|___________|\n");
	printf("\n\n");
}
//MENU PRINCIPAL
void Menu(){
	Title(); //TITULO
	printf("\033[1;34m");
	printf("\t\t\t        DCC BATTESHIP\n \n");	
	printf("\033[0m");
	printf("                                        /|\n");
    printf("                                      _| |\n");
    printf("                                    _|   |\n");
    printf("                                /|  |    |\n");
	printf("                               / |  |    |           _____\n");
	printf("                             /|  |  |    |___       |     |\n");
	printf("                            / |  |  |        |      | DCC |\n");
	printf("                           /  |  |__|        |      |_____|\n");
	printf("                     _____/                   |_____|____           __\n");
	printf("                    (                                    )_________(  )\n");
	printf("          ___________)                                               /\n");
	printf("         (                                                          / \n");
	printf("          \\                     1 - NOVO JOGO                      / \n");
	printf("           \\                                                      /\n");
	printf("            \\                2 - REGRAS DO JOGO                  /\n");
	printf("             \\                                                  /\n");
	printf("              \\                                          M&P   /\n");
	printf("               \\______________________________________________/\n\n");
}

void WaitForPlayer(){
  system("clear");
  Title();
	printf("Please wait for the next player! Enter any input to continue playing.\n\n");
	char* anything = (char*) malloc(1000);
	scanf("%s", anything);
	free(anything);
	system("clear");
}


//NTotal de Barcos para cada tipo
int NPieces(int *nptpieces, int tabu){
	int nb = (tabu*tabu)/25;
	int vv=1; 
	int cn=0;
	do{
		Title();
		printf("\033[1;34m");
		printf ("\n\t       TEMOS OS SEGUINTES BARCOS A SUA DISPOSIÇÃO\n");
		printf("\033[0m");
		Pieces();
		if(vv==0){
			printf("\033[1;31m");
    		printf("Valores incorretos tente novamente!(ERRO: nªbarcos < 1)\n");
			printf("\033[0m");
		}
		if(vv==2){
			printf("\033[1;31m");
    		printf("Valores incorretos tente novamente! (ERRO: nº total de barcos)\n");
			printf("\033[0m");
		}
		vv=1;
		cn=0;
		printf("\n");
		printf("   _____________________________ \t");      printf("\033[1;33m");printf("AVISO!\n");printf("\033[0m");
		printf("  |                             |\t");	    printf(" - Para cada tipo de barco\n");
		printf("  |  Selecione o nº de barcos   |\t");		printf("deve colocar"); printf("\033[1;34m"); printf(" 1 ou mais");printf("\033[0m"); printf(" barcos.\n");
		printf("  |_____________________________|\n");     
		printf("  |       |                      \t");      printf(" - Máximo de");printf("\033[1;34m"); printf(" %d ",nb); printf("\033[0m"); printf("barcos.\n");		
		printf("  |   C   | ");scanf("%d",&nptpieces[0]);
		printf("  |   B   | ");scanf("%d",&nptpieces[1]);
		printf("  |   R   | ");scanf("%d",&nptpieces[2]);
		printf("  |   S   | ");scanf("%d",&nptpieces[3]);
		printf("  |   D   | ");scanf("%d",&nptpieces[4]);
		printf("  |_______|\n");

		for(int i=0;i<5;i++){
			cn=cn+nptpieces[i];
			if(nptpieces[i]<1){
				vv=0;
			}
			if(vv==1 && cn>nb){
				vv=2;
			}
		}
	}while(vv!=1);
	return cn;
}
//VALIDAÇAO DO TAMANHO DO TABULEIRO
int ValTab(){
	int vv=1;
	int num;
	do{	
		system("clear");
		Title();
		if(vv==0){
			printf("\033[1;31m");
			
    		printf("ERRO: Opção incorreta tente novamente!\n\n");
			
			printf("\033[0m");
		}
		printf("\033[1;34m");
		printf("Qual é o tamanho do tabuleiro? \t");
		printf("\033[0m");
		printf("(minímo 20, máximo 40)\n");
		scanf("%d", &num);
		if (!(num>=20 && num<=40)){
		    vv=0;
    	}else{
    		vv=1;
    	}
	}while(vv!=1);
	return num;
}
//VALIDAÇAO DO MODO
char ValModo(){
	char modo=' ';
	int vv=1;
	do{	
		system("clear");
		Title();
		if(vv==0){
			printf("\033[1;31m");
			
    		printf("ERRO: Opção incorreta tente novamente!\n\n");
			
			printf("\033[0m");
		}
		printf("\033[1;34m");
		printf("Colocação das Peças:  Automatico(A) ou Manual(M)?\n");
		printf("\033[0m");
		printf("Coloque a letra correspondente: ");
		scanf("%s", &modo);
		modo=tolower(modo);
		switch (modo){
    		case 'a':case 'm': vv=1;
    				          break;
    		default:vv=0;
  		}
	}while(vv!=1);
	return modo;
}

//2-INSERÇAO AUTOMATICO
void InsertBoatM(int np, int npTipos[], BOARD *player, int size,SHIP *ships){
	SHIP Destroyer; strcpy(Destroyer.bitmap, "0000000000001000010000000");
  	SHIP Submarine; strcpy(Submarine.bitmap, "0000000000001000010000100");
  	SHIP Cruiser; strcpy(Cruiser.bitmap, "0000000000001100010000100");
  	SHIP Battleship; strcpy(Battleship.bitmap, "0000000100001000010000100");
  	SHIP Carrier; strcpy(Carrier.bitmap, "0000000110001100010000100");
	int x, y, or, boatsinserted = 0, errorflag = -1;
	for(int i=0;i<5;i++){
		for (int j = 0; j < npTipos[i]; j++){
			system("clear");
			printf("\033[1;32m");
			printf("\t\t\t  JOGADOR %d: \n", np);
			printf("\033[0m");
			printf("\033[1;34m");
	   		printf ("\n\t   VAMOS COLOCAR OS SEUS BARCOS NO TABULEIRO\n\n");
	      	printf("\033[0m");
	      	Pieces();
	      	printf("\033[1;33m");printf("AVISO! ");printf("\033[0m"); printf("Na 'Orientação' deve colocar a seguinte indicação! (Rotações para a esquerda)\n \t");
	      	printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("->0º   ");
	      	printf("\033[1;34m"); printf("1"); printf("\033[0m"); printf("->90º   ");
	      	printf("\033[1;34m"); printf("2"); printf("\033[0m"); printf("->180º   ");
	      	printf("\033[1;34m"); printf("3"); printf("\033[0m"); printf("->270º   \n\n");
	      
	      	PrintBoard(player, size);
	      	
	      	if(errorflag == 0)
	      		printf("Inserido com Sucesso!\n\n");
	      	if(errorflag == 1){
	        	printf("Erro a inserir!\n\n");
	        	errorflag = 0;
	      	}
	      	//----------------------------------------------------
			printf("  NºBarco  | %d \n", boatsinserted + 1);
			printf("   Nome    | ");
			printf("\033[1;34m");
			switch(i){
				case 0: printf("Carrier\n");
						ships[boatsinserted] = Carrier;
						break;
				case 1: printf("Battleship\n");
						ships[boatsinserted] = Battleship;
						break;
				case 2: printf("Cruiser\n");
						ships[boatsinserted] = Cruiser;
						break;
				case 3: printf("Submarine\n");
						ships[boatsinserted] = Submarine;
						break; 
				case 4: printf("Destroyer\n");
						ships[boatsinserted] = Destroyer;
						break; 
			}			
			printf("\033[0m");	
			printf(" Coord. X  | "); scanf("%d", &x);
			printf(" Coord. Y  | "); scanf("%d", &y);
			printf("Orientação | "); scanf("%d", &or);
			printf("\n");
				
			if(InsertPiece(player, ships[boatsinserted], size, x, y, or) == 0){    
	        	boatsinserted++;
	        	errorflag = 0;
	      	}else{                                                            
	        	j--;
	        	errorflag = 1;
	    	}
		}
	}
  	Title();
	printf("\033[1;32m");
	printf("\t\t\t  JOGADOR %d: \n\n", np);
	printf("\033[0m");
	PrintBoard(player, size);
}
//1-MODO MANUAL DE INSERÇÂO DE BARCOS
void ManualCoord(int npTipos[], int size){
	system("clear");

	BOARD *player1;
	player1 = BuildBoard(size, player1);

	BOARD *player2;
	player2 = BuildBoard(size, player2);

	int boatnumber=0;
  	for(int i = 0; i <5; i++){
    	for(int j = 0; j < npTipos[i]; j++){
      		boatnumber++;
    	}
  	}
  	SHIP *ships1 = (SHIP*) malloc(sizeof(SHIP) * boatnumber);
  	SHIP *ships2 = (SHIP*) malloc(sizeof(SHIP) * boatnumber);
  	
  	//-----------------------------------------------------------------------------------
	//COLOCAÇAO DAS PEÇAS
	int loop=1;
	while(loop!=0){
		InsertBoatM(1,npTipos,player1,size,ships1);

		printf("\nPretende alterar o seu mapa:\n \n");
		printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("-> Não pretendo alterar 	 ");
		printf("\033[1;34m"); printf("1"); printf("\033[0m"); printf("-> Pretendo alterar\n");
		scanf("%d", &loop);
		if(loop!=0){ //Limpar a board e recomeçar a inserção
			loop=1;
			player1 = erase_board_data(player1, size);
		}
	}

	//NAO DEIXAR VER O CONTEUDO ANTERIOR
	WaitForPlayer();

	system("clear");
	
	loop=1;
	while(loop!=0){
		InsertBoatM(2,npTipos,player2,size,ships2);

		printf("\nPretende alterar o seu mapa:\n \n");
		printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("-> Não pretendo alterar 	 ");
		printf("\033[1;34m"); printf("1"); printf("\033[0m"); printf("-> Pretendo alterar\n");
		scanf("%d", &loop);
		if(loop!=0){ //Limpar a board e recomeçar a inserção
			loop=1;
			player2 = erase_board_data(player2, size);
		}
	}


	
	//---------------------------------------------
}
//2-INSERÇAO AUTOMATICO
void InsertBoatA(int np, int npTipos[], BOARD *player, int size,SHIP *ships){
	SHIP Destroyer; strcpy(Destroyer.bitmap, "0000000000001000010000000");
	SHIP Submarine; strcpy(Submarine.bitmap, "0000000000001000010000100");
	SHIP Cruiser; strcpy(Cruiser.bitmap, "0000000000001100010000100");
	SHIP Battleship; strcpy(Battleship.bitmap, "0000000100001000010000100");
	SHIP Carrier; strcpy(Carrier.bitmap, "0000000110001100010000100");
	
	int x, y, or, boatsinserted = 0, errorflag = -1;
	for(int i=0;i<5;i++){
		for (int j = 0; j < npTipos[i]; j++){
			switch(i){
				case 0: ships[boatsinserted] = Carrier;
						break;
				case 1: ships[boatsinserted] = Battleship;
						break;
				case 2: ships[boatsinserted] = Cruiser;
						break;
				case 3: ships[boatsinserted] = Submarine;
						break; 
				case 4: ships[boatsinserted] = Destroyer;
						break; 
			}			
			x=rand() % size;
			y=rand() % size;
			or=rand() % 3;		
			if(InsertPiece(player, ships[boatsinserted], size, x, y, or) == 0){    
	        	boatsinserted++;
	      	}else{                                                            
	        	j--;
	    	}
		}
	}
  	Title();
	printf("\033[1;32m");
	printf("\t\t\t  JOGADOR %d: \n\n", np);
	printf("\033[0m");
	PrintBoard(player, size);
}

//1-MODO AUTOMATICO DE INSERÇÂO DE BARCOS
void AutoCoord(int npTipos[], int size){   
	system("clear");
	BOARD *player1;
	player1 = BuildBoard(size, player1);

	BOARD *player2;
	player2 = BuildBoard(size, player2);

	int boatnumber=0;
  	for(int i = 0; i <5; i++){
    	for(int j = 0; j < npTipos[i]; j++){
      		boatnumber++;
    	}
  	}
  	SHIP *ships1 = (SHIP*) malloc(sizeof(SHIP) * boatnumber);
  	SHIP *ships2 = (SHIP*) malloc(sizeof(SHIP) * boatnumber);
  	
  	//-----------------------------------------------------------------------------------
	//COLOCAÇAO DAS PEÇAS
	int loop=1;
	while(loop!=0){
		InsertBoatA(1,npTipos,player1,size,ships1); //ALTERAR

		printf("\nPretende alterar o seu mapa:\n \n");
		printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("-> Não pretendo alterar 	 ");
		printf("\033[1;34m"); printf("1"); printf("\033[0m"); printf("-> Pretendo alterar\n");
		scanf("%d", &loop);
		if(loop!=0){ //Limpar a board e recomeçar a inserção
			loop=1;
			player1 = erase_board_data(player1, size);
		}
	}

	//NAO DEIXAR VER O CONTEUDO ANTERIOR
	WaitForPlayer();

	system("clear");

	loop=1;
	while(loop!=0){
		InsertBoatA(2,npTipos,player2,size,ships2);
		printf("\nPretende alterar o seu mapa:\n \n");
		printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("-> Não pretendo alterar 	 ");
		printf("\033[1;34m"); printf("1"); printf("\033[0m"); printf("-> Pretendo alterar\n");
		scanf("%d", &loop);
		if(loop!=0){ //Limpar a board e recomeçar a inserção
			loop=1;
			player2 = erase_board_data(player2, size);
		}
	}
	//---------------------------------------------
}

void Jogo(){			
	int tal=ValTab();
	char mod=ValModo();

	int piecesspj=0;
	int npTipos[5]={0,0,0,0,0};

	piecesspj=NPieces(npTipos, tal);

	if (mod=='m'){
		ManualCoord(npTipos,tal);
	}else{
		AutoCoord(npTipos,tal);
	}		
}

//MENU-> REGRAS
void Regras(){
	system("clear");
	printf("\033[1;34m");
	printf ("\nREGRAS DO JOGO:\n \n");	
	printf("\033[0m");
	printf ("1. Este é um jogo de 2 jogadores.\n\n");
	printf ("2. Os jogadores terão a opção de inserir manualmente as coordenadas para o tabuleiro de jogo ou o computador gera aleatoriamente um tabuleiro de jogo.\n\n");
	printf ("3. Existem cinco tipos de navios a serem colocados pelo maior comprimento até o menor; \n");
	printf ("   [c] Carrier possui 5 células,\n");
	printf ("   [b] Battleship possui 4 células,\n");
	printf ("   [r] Cruiser possui 3 células, \n");
	printf ("   [s] Submarine possui 3 células, \n");
	printf ("   [d] Destroyer possui 2 células.\n \n");
	printf ("4. O computador seleciona aleatoriamente qual player será o primeiro.\n \n");
	printf ("5. O jogo começa quando cada jogador tenta adivinhar a localização dos navios do tabuleiro do adversário.\n\n");
	printf ("6. Primeiro jogador a adivinhar a localização de todos os navios ganha.\n\n");
	printf(" /            \\ 		 /            \\ \n");
	printf("|   J-JOGAR    |		|    S-SAIR    |\n");
	printf(" \\            /			 \\            / \n");
}

//VALIDAÇAO DA OPÇAO REGRAS
void OpRegras(){
	char op;
    printf("\nEscolha uma opção: \n");
    scanf("%s", &op);
    op=tolower(op);
    switch (op){
    	case 'j':	system("clear");  
    				Jogo();
    				break;
    	case 's':
    			system("clear");
    			exit(0);
    			break;
    	default:system("clear");
    			Regras();
    			printf("\033[1;31m");
    			printf("\n Opção incorreta tente novamente!\n");
				printf("\033[0m");
    			OpRegras();
    }
}

//VALIDAÇAO DA OPÇAO MENU
void OpMenu(){
	int op=0;
    printf("\nEscolha uma opção: \n");
    scanf("%d", &op);
    if(op==1){
    	Jogo();
    }else{
    	if(op==2){
    		system("clear"); 
    		Regras();
    		OpRegras();
    	}else{
    		Menu();
    		printf("\033[1;31m");
    		printf("\nOpção incorreta tente novamente!\n");
			printf("\033[0m");
    		OpMenu();
    	}
    }
}

int main(){
	Menu();
	OpMenu();
}
