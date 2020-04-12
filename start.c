#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


int main(){ //RADIO 3/4
	system("clear");
	//TITULO DO JOGO
	void Title(){
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

	//MENU PRINCIPAL
	void Menu(){
		printf("\033[1;34m");
		printf("\n\t\t\t      DCC BATTESHIP\n");	
		
		printf("\033[0m");
		Title();
		printf("                                    /|                           \n");
	    printf("                                  _| |                           \n");
	    printf("                                _|   |                           \n");
	    printf("                            /|  |    |                           \n");
	    printf("                           / |  |    |           _____                \n");
	    printf("                         /|  |  |    |___       |     |         \n");
	    printf("                        / |  |  |        |      | DCC |           \n");
	    printf("                       /  |  |__|        |      |_____|            \n");
	    printf("                 _____/                   |_____|____           __ \n");
	    printf("                (                                    )_________(  )\n");
	    printf("      ___________)                                               /          \n");
	    printf("     (                                                          / \n");
	    printf("      \\                     1 - NOVO JOGO                      / \n");
	    printf("       \\                                                      /  \n");
	    printf("        \\                2 - REGRAS DO JOGO                  / \n");
	    printf("         \\                                                  /  \n");
	    printf("          \\                                          M&P   /   \n");
	    printf("           \\______________________________________________/  \n\n");
	}

	//VALIDAÇAO DE NUMERO DE BARCOS
	int NBarcos(int *nbarcos, int tabu){
		int nb = (tabu*tabu)/25;
		int vv=1; 
		int cn=0;
		do{
			system("clear");
			Title();
			printf("\033[1;34m");
			printf ("\n\t       TEMOS OS SEGUINTES BARCOS A SUA DISPOSIÇÃO\n");
			printf("\033[0m");
			printf("        ___________________________________________________________\n");
			printf("  ID   |     C     |     B     |     R     |     S     |     D     |\n");
			printf(" Nome  |  Carrier  |Battleship |  Cruiser  | Submarine | Destroyer |\n");
			printf("Tamanho|     6     |     5     |     4     |     3     |     2     |\n");
			printf("       |-----------|-----------|-----------|-----------|-----------|\n");
			printf("       | X X _ _ _ | X _ _ _ _ | X X _ _ _ | X _ _ _ _ | X _ _ _ _ |\n");
			printf("       | X X _ _ _ | X _ _ _ _ | X _ _ _ _ | X _ _ _ _ | X _ _ _ _ |\n");
			printf("       | X _ _ _ _ | X _ _ _ _ | X _ _ _ _ | X _ _ _ _ | _ _ _ _ _ |\n");
			printf("       | X _ _ _ _ | X _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ |\n");
			printf("       | _ _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ | _ _ _ _ _ |\n");
			printf("       |___________|___________|___________|___________|___________|\n");
			printf("\n\n");
			if(vv==0){
				printf("\033[1;31m");
	    		printf("Valores incorretos tente novamente!(erro: nªbarcos < 1)\n");
				printf("\033[0m");
			}
			if(vv==2){
				printf("\033[1;31m");
	    		printf("Valores incorretos tente novamente! (erro: nº total de barcos)\n");
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
			printf("  |   C   | ");scanf("%d",&nbarcos[0]);
			printf("  |   B   | ");scanf("%d",&nbarcos[1]);
			printf("  |   R   | ");scanf("%d",&nbarcos[2]);
			printf("  |   S   | ");scanf("%d",&nbarcos[3]);
			printf("  |   D   | ");scanf("%d",&nbarcos[4]);
			printf("  |_______|\n");

			for(int i=0;i<5;i++){
				cn=cn+nbarcos[i];
				if(nbarcos[i]<1){
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
		int opcao;
		do{	
			system("clear");
			Title();
			if(vv==0){
				printf("\033[1;31m");
				
	    		printf("\nOpção incorreta tente novamente!\n\n");
				
				printf("\033[0m");
			}
			printf("\033[1;34m");
			printf("Qual é o tamanho do tabuleiro? \t");
			printf("\033[0m");
			printf("(minímo 20, máximo 40)\n");
			scanf("%d", &opcao);
			if (!(opcao>=20 && opcao<=40)){
			    vv=0;
	    	}else{
	    		vv=1;
	    	}
		}while(vv!=1);
		return opcao;
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
				
	    		printf("\nOpção incorreta tente novamente!\n\n");
				
				printf("\033[0m");
			}
			printf("\033[1;34m");
			printf("Colocação das Peças:  Automatico(A) ou Manual(M)?\n");
			printf("\033[0m");
			printf("Coloque a letra correspoandente:");
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
	//OPÇAO JOGO INTRODUÇAO DE DADOS
	//MENU-> JOG0 OU MENU->REGRAS->JOGO

	void Coord(int nbtotais[]){
		//FAZER COORDENADAS
		printf("  NºBarco  |\n");
		printf("   Nome    |\n");
		printf(" Coord. X  |\n");
		printf(" Coord. Y  |\n");
		printf("Orientação |\n");
	}
	void Jogo(){			
		int tal=ValTab();
		char mod=ValModo();
		int nbarcosporjogo=0;
		int NporTipos[5]={0,0,0,0,0};
		nbarcosporjogo=NBarcos(NporTipos, tal);
		
		/*printf("\nDADOS:\n");
		printf("Tamanho:%d\n",tal );
		printf("Modo:%c\n",mod );
		printf("Nº Barcos no jogo: %d\n",nbarcosporjogo );
		for(int i=0; i<5;i++){
			printf("%d\n",NporTipos[i]);
		}
	*/
		//Coord();
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
	    	system("clear");  
	    			Jogo();
	    }else{
	    	if(op==2){
	    		system("clear"); 
	    		Regras();
	    		OpRegras();
	    	}else{
	    		printf("Ola %d\n", op);
				system("clear");
	    		Menu();
	    		printf("\033[1;31m");
				
	    		printf("\nOpção incorreta tente novamente!\n");
				
				printf("\033[0m");
	    		OpMenu();
	    	}
	    }
	}
	

	Menu();
	OpMenu();
  return 0;
}
