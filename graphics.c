#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <time.h>


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