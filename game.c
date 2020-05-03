#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"

//Titulo do jogo
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

//Apresentação para o inicio do jogo depois de recolhidas as informações pretendidas
void Layout(){
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
	printf("          \\                                                       / \n");
	printf("           \\                   ");
	
	printf("\033[1;32m");
	printf("PRONTO PARA JOGAR?");
	printf("\033[0m");

	printf("                /\n");
	printf("            \\                                                   /\n");
	printf("             \\                                                 /\n");
	printf("              \\                                         M&P   /\n");
	printf("               \\_____________________________________________/\n\n");

	

	printf("\nPara começar o jogo digite qualquer tecla! (Tecla e aseguir ENTER)\n\n");
	char* anything = (char*) malloc(1000);
	scanf("%s", anything);
	free(anything);

	system("clear");
}

//Apresentação do jogador vencedor depois de ter destruido tudo os barcos do adversário
void Win(int jog){
	Title();
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
	printf("          \\                          ");
	printf("\033[1;34m");
	printf("GANHOU");
	printf("\033[0m");

	printf("                       / \n");
	printf("           \\                        ");
	
	printf("\033[1;32m");
	printf("JOGADOR %d", jog);
	printf("\033[0m");
	
	printf("                    /\n");
	printf("            \\                                                   /\n");
	printf("             \\                 ");

	printf("\033[1;34m");
	printf("Muitos Parabéns!!");
	printf("\033[0m");
	
	
	printf("               /\n");
	printf("              \\                                         M&P   /\n");
	printf("               \\_____________________________________________/\n\n");

}
//Peças disponiveis no jogo
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
//Menu inicial do jogo
void MainMenu(){
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

//Troca para o próximo jogador, para que o adversário possa ver o tabuleiro
void WaitForPlayer(int jogador){
  	Title();

	printf("Por favor, aguarde pelo");
	printf("\033[1;32m");
	printf(" jogador %d",jogador);
	printf("\033[0m");
	printf("! \nDigite qualquer tecla para continuar o jogo. (Tecla e aseguir ENTER)\n\n");
	char* anything = (char*) malloc(1000);
	scanf("%s", anything);
	free(anything);

	system("clear");
}

//Depois de inserir as coordenadas para atacar o jogador vê o que acertou e depois de ler da seguimento ao jogo
void ChangePlayer(){  
	printf("\nDigite qualquer tecla para limpar o seu ecrã e continuar o jogo! (Tecla e aseguir ENTER)\n\n");
	char* anything = (char*) malloc(1000);
	scanf("%s", anything);
	free(anything);

	system("clear");
}

 
//funçao para selecionar o numero de barcos que vão ser utilizados no jogo
//o nºbarcos nao pode ser superior ao limitado e c/tipo de barco tem de ter valor superior ou igual a 1
void NPieces(int *nptpieces, int tabu){
	int nb = (tabu*tabu)/25;
	int erro=0;  //0-sem erro     1- nºbarcos<1   2- limite de barcos
	int cn=0;
	do{
		Title();

		printf("\033[1;34m");
		printf ("\n\t       TEMOS OS SEGUINTES BARCOS A SUA DISPOSIÇÃO\n");
		printf("\033[0m");

		Pieces(); //Mostrar Tipos de Barcos

		if(erro==1){ 
			printf("\033[1;31m");
    		printf("Valores incorretos tente novamente!(ERRO: nªbarcos < 1)\n");
			printf("\033[0m");
		}

		if(erro==2){
			printf("\033[1;31m");
    		printf("Valores incorretos tente novamente! (ERRO: nº total de barcos)\n");
			printf("\033[0m");
		}

		erro=0;
		cn=0;
		printf("\t     Selecione o nº de barcos para os dois jogadores!\n");
		printf("\n");
		printf("   _____________________________ \t");      printf("\033[1;33m");printf("AVISO!\n");printf("\033[0m");
		printf("  |                             |\t");	    printf(" - Para cada tipo de barco\n");
		printf("  |  Selecione o nº de barcos   |\t");		printf("deve colocar"); printf("\033[1;34m"); printf(" 1 ou mais");printf("\033[0m"); printf(" barcos.\n");
		printf("  |_____________________________|\n");     
		printf("  |       |                      \t");      printf(" - Máximo de");printf("\033[1;34m"); printf(" %d ",nb); printf("\033[0m"); printf("barcos.\n");		
		printf("  |   C   | ");scanf("%d",&nptpieces[0]); for(int c; (c=getchar()) != '\n' && c!= EOF;);
		printf("  |   B   | ");scanf("%d",&nptpieces[1]); for(int c; (c=getchar()) != '\n' && c!= EOF;);
		printf("  |   R   | ");scanf("%d",&nptpieces[2]); for(int c; (c=getchar()) != '\n' && c!= EOF;);
		printf("  |   S   | ");scanf("%d",&nptpieces[3]); for(int c; (c=getchar()) != '\n' && c!= EOF;);
		printf("  |   D   | ");scanf("%d",&nptpieces[4]); for(int c; (c=getchar()) != '\n' && c!= EOF;);
		printf("  |_______|\n");

		for(int i=0;i<5;i++){
			cn=cn+nptpieces[i];

			if(nptpieces[i]<1){
				erro=1;
			}
			if(erro==0 && cn>nb){
				erro=2;
			}
		}
	}while(erro!=0);
}

//Validação do Tamanho do Tabuleiro sabendo que o tabuleiro tem de ser >=20 e <=40
int ValTab(){
	int erro=1;
	int num;

	do{	
		Title();
		
		if(erro==0){
			printf("\033[1;31m");
    		printf("ERRO: Opção incorreta tente novamente!\n\n");
			printf("\033[0m");
		}

		printf("\033[1;34m");
		printf("Qual é o tamanho do tabuleiro? \t");
		printf("\033[0m");
		printf("(minímo 20, máximo 40)\n");
		
		scanf("%d", &num);
		for(int c; (c=getchar()) != '\n' && c!= EOF;);
		
		if (!(num>=20 && num<=40)){
		    erro=0;
    	}else{
    		erro=1;
    	}
	}while(erro!=1);

	return num;
}

//Validação do modo par o jogo
//automatico as peças escolhida serão colocadas pelo computador aleatoriamente
//manual o utilizador coloca as coordenadas e a orientação
char ValModo(){
	char modo=' ';
	int erro=1;
	do{	
		Title();
		if(erro==0){
			printf("\033[1;31m");
			
    		printf("ERRO: Opção incorreta tente novamente!\n\n");
			
			printf("\033[0m");
		}
		printf("\033[1;34m");
		printf("Colocação das Peças para os dois jogadores:  Automatico(A) ou Manual(M)?\n");
		printf("\033[0m");
		printf("A- as peças são colocadas aleatoriamente    M-cada jogador escolhe as coordenadas e a orientação \n\n");
		printf("Coloque a letra correspondente: \n");

		scanf("%s", &modo);
		modo=tolower(modo);

		switch (modo){
    		case 'a':case 'm': erro=1;
    				          break;
    		default:erro=0;
  		}
	}while(erro!=1);

	return modo;
}

//2_Inserçao Manual dos Barcos
//esta função dde acordo com o nºpeças por tipo faz a colocação manual das peças, o jogador correspondente escolhe as corrdenadas e orientação para cada peça
void InsertBoatM(int np, int npTipos[], BOARD *player, int size,SHIP *ships){
	//Barcos-----------------------------------------------------------------
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
	   		printf ("\n\t   VAMOS COLOCAR OS BARCOS NO SEU TABULEIRO\n\n");
	      	printf("\033[0m");

	      	Pieces();

	      	//AVISO
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
	      	//Caixa de Inserção-------------------------------
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
			printf(" Coord. X  | "); scanf("%d", &x); for(int c; (c=getchar()) != '\n' && c!= EOF;);
			printf(" Coord. Y  | "); scanf("%d", &y); for(int c; (c=getchar()) != '\n' && c!= EOF;);
			printf("Orientação | "); scanf("%d", &or); for(int c; (c=getchar()) != '\n' && c!= EOF;);
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
	//Mostrar resultado--------------------
  	Title();

	printf("\033[1;32m");
	printf("\t\t\t  JOGADOR %d: \n\n", np);
	printf("\033[0m");
	PrintBoard(player, size);
}

//1_Modo Manual
//esta funçao gere a colocação manual das peças e verifica se cada jogador quer ou nao alterar o tabuleiro que realizou
BOARD** ManualCoord(int npTipos[], int size){
	system("clear");

	//nºde barcos---------------------------
	int boatnumber=0;
  	for(int i = 0; i <5; i++){
    	for(int j = 0; j < npTipos[i]; j++){
      		boatnumber++;
    	}
  	}

  	//Dados do Jogador 1-----------------------------------
  	BOARD *player1;
	player1 = BuildBoard(size);
  	SHIP *ships1 = (SHIP*) malloc(sizeof(SHIP) * boatnumber);
  	//Dados do Jogador 2-----------------------------------
  	BOARD *player2;
	player2 = BuildBoard(size);
  	SHIP *ships2 = (SHIP*) malloc(sizeof(SHIP) * boatnumber);
  	
  	//Colocação das Peças----------------------------------------------------------------------------
  	//Jogador 1
	int loop=1;
	while(loop!=0){
		//Inserção das Peças
		InsertBoatM(1,npTipos,player1,size,ships1);

		printf("\nPretende alterar o seu mapa:\n \n");
		printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("-> Não pretendo alterar 	 ");
		printf("\033[1;34m"); printf("Outra tecla"); printf("\033[0m"); printf("-> Pretendo alterar\n");
		scanf("%d", &loop);
		for(int c; (c=getchar()) != '\n' && c!= EOF;){
			if(loop!=0){ //Limpar a board e recomeçar a inserção
				loop=1;
				player1 = EraseBoardData(player1, size);
			}
		}
	}

	//Não deixar ver o conteúdo anterior e espera pelo proximo jogador
	WaitForPlayer(2);

	//Jogador 2
	loop=1;
	while(loop!=0){
		//Inserção das Peças
		InsertBoatM(2,npTipos,player2,size,ships2);

		//Confirmação do tabuleiro--------------------------------------------------------------------
		printf("\nPretende alterar o seu mapa:\n \n");
		printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("-> Não pretendo alterar 	 ");
		printf("\033[1;34m"); printf("Outra tecla"); printf("\033[0m"); printf("-> Pretendo alterar\n");
		scanf("%d", &loop);
		for(int c; (c=getchar()) != '\n' && c!= EOF;){
			if(loop!=0){ //Limpar a board e recomeçar a inserção
				loop=1;
				player2 = EraseBoardData(player2, size);
			}
		}
	}

	static BOARD *players[3];
	players[1] = player1;
	players[2] = player2;
	return players;
	
}


//2_Inserçao Automática dos Barcos
//esta função dde acordo com o nºpeças por tipo faz a colocação automatica das peças (aleatoriamente)
void InsertBoatA(int np, int npTipos[], BOARD *player, int size,SHIP *ships){
	//Barcos-----------------------------------------------------------------
	SHIP Destroyer; strcpy(Destroyer.bitmap, "0000000000001000010000000");
	SHIP Submarine; strcpy(Submarine.bitmap, "0000000000001000010000100");
	SHIP Cruiser; strcpy(Cruiser.bitmap, "0000000000001100010000100");
	SHIP Battleship; strcpy(Battleship.bitmap, "0000000100001000010000100");
	SHIP Carrier; strcpy(Carrier.bitmap, "0000000110001100010000100");
	
	int x, y, or, boatsinserted = 0;
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
	//Mostrar Resultado-------------------
  	Title();

	printf("\033[1;32m");
	printf("\t\t\t  JOGADOR %d: \n\n", np);
	printf("\033[0m");

	PrintBoard(player, size);
}

//1_Modo Automático
//esta funçao gere a colocação automatica das peças e verifica se cada jogador quer ou nao alterar o tabuleiro que realizou
BOARD** AutoCoord(int npTipos[], int size){   
	system("clear");

	int boatnumber=0;
  	for(int i = 0; i <5; i++){
    	for(int j = 0; j < npTipos[i]; j++){
      		boatnumber++;
    	}
  	}
  	
  	//Dados do Jogador 1-----------------------------------
  	BOARD *player1;
	player1 = BuildBoard(size);
  	SHIP *ships1 = (SHIP*) malloc(sizeof(SHIP) * boatnumber);
  	//Dados do Jogador 2-----------------------------------
	BOARD *player2;
	player2 = BuildBoard(size);
  	SHIP *ships2 = (SHIP*) malloc(sizeof(SHIP) * boatnumber);
  	
  	WaitForPlayer(1);
	//Colocação das Peças----------------------------------------------------------------------------
  	//Jogador 1
	int loop=1;
	while(loop!=0){
		InsertBoatA(1,npTipos,player1,size,ships1); //ALTERAR

		//Confirmação do tabuleiro--------------------------------------------------------------------
		printf("\nPretende alterar o seu mapa:\n \n");
		printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("-> Não pretendo alterar 	 ");
		printf("\033[1;34m"); printf("Outra tecla"); printf("\033[0m"); printf("-> Pretendo alterar\n");
		scanf("%d", &loop);
		for(int c; (c=getchar()) != '\n' && c!= EOF;);

		if(loop!=0){ //Limpar a board e recomeçar a inserção
			loop=1;
			player1 = EraseBoardData(player1, size);
		}
	}

	//Não deixar ver o conteúdo anterior
	WaitForPlayer(2);

	loop=1;
	while(loop!=0){
		InsertBoatA(2,npTipos,player2,size,ships2);

		//Confirmação do tabuleiro--------------------------------------------------------------------
		printf("\nPretende alterar o seu mapa:\n \n");
		printf("\033[1;34m"); printf("0"); printf("\033[0m"); printf("-> Não pretendo alterar 	 ");
		printf("\033[1;34m"); printf("Outra tecla"); printf("\033[0m"); printf("-> Pretendo alterar\n");
		scanf("%d", &loop);
		for(int c; (c=getchar()) != '\n' && c!= EOF;);

		if(loop!=0){ //Limpar a board e recomeçar a inserção
			loop=1;
			player2 = EraseBoardData(player2, size);
		}
	}
	
	static BOARD *players[3];
	players[1] = player1;
	players[2] = player2;
	return players;
	
}

//esta funçao gere todas as informações necessárias para o incio do jogo
//Tamanho do tabuleiro, o modo, as peças e onde vão estar colocadas as peças
BOARD** Game(){	
	Title();		
	int tal=ValTab(); //Tamanho do Tabuleiro

	char mod=ValModo(); //Modo escolhido

	int npTipos[5]={0,0,0,0,0};

	NPieces(npTipos, tal); //Numero de Peças do Jogo

	if (mod=='m'){
		return ManualCoord(npTipos,tal); //Modo Manual
	}else{
		return AutoCoord(npTipos,tal);  //Modo Automatico
	}		
}

//Menu->Regras
//esta função pretende mostrar aos jogadores as regras para o jogo
void Rules(){
	Title();

	printf("\033[1;34m");
	printf ("\nREGRAS DO JOGO:\n \n");	
	printf("\033[0m");
	
	printf ("1. Este é um jogo de 2 jogadores num só computador.\n\n");
	printf ("2. Os jogadores devem decidir qual será o tamanho do tabuleiro, sabendo que não pode ser inferior a 20 nem superior a 40.\n");
	printf ("3. Os jogadores terão duas opções para inserir os barcos:\n");
		printf("\t Manualmente - as coordenadas e orientação são escolhidas por cada jogador\n");
		printf("\t Aleatoriamente - o computador gera aleatoriamente um tabuleiro de jogo.\n\n");
	printf ("4. Existem cinco tipos de navios a serem colocados pelo maior comprimento até o menor; \n");
	printf ("   [C] Carrier possui 6 células,\n");
	printf ("   [B] Battleship possui 3 células,\n");
	printf ("   [R] Cruiser possui 3 células, \n");
	printf ("   [S] Submarine possui 3 células, \n");
	printf ("   [D] Destroyer possui 2 células.\n \n");
	printf ("5. O computador seleciona aleatoriamente qual o jogador será o primeiro.\n \n");
	printf ("6. O jogo começa e cada jogador deve tentar adivinhar a localização dos navios do tabuleiro do adversário.\n\n");
	printf ("7. Primeiro jogador a adivinhar a localização de todos os navios ganha.\n\n\n");
	printf("    /            \\             /            \\ \n");
	printf("   |   J-JOGAR    |           |    S-SAIR    |\n");
	printf("    \\            /             \\            / \n");
}

//Validação das Opções da Regras
void OpRules(){
	char op;
    printf("\nEscolha uma opção: \n");
    scanf("%s", &op);
    op=tolower(op);
    switch (op){
    	case 'j':Game();
    				break;
    	case 's':system("clear");
    			exit(0);
    			break;
    	default:Rules();
    			printf("\033[1;31m");
    			printf("\n Opção incorreta tente novamente!\n");
				printf("\033[0m");
    			OpRules();
    }
}

//Validação do Menu Principal
BOARD** OpMainMenu(){
	int op=0;
    printf("\nEscolha uma opção: \n");
    scanf("%d", &op);
    
    if(op==1){
    	return Game();
	}else{
	    if(op==2){
	    		Rules();
	    		OpRules();
	    }else{
	    		if(op>2){
	    			MainMenu();
		    		printf("\033[1;31m");
		    		printf("\nOpção incorreta tente novamente!\n");
		    		printf("\033[0m");
		    		OpMainMenu();
	    		}else{
	    			for(int c; (c=getchar()) != '\n' && c!= EOF;){
	    				MainMenu();
			    		printf("\033[1;31m");
			    		printf("\nOpção incorreta tente novamente! (Somente números)\n");
			    		printf("\033[0m");
			    		OpMainMenu();
	    			}
	    		}
	    	}
    }

    return 0;
}
