TP2_groupF - Miguel Ramos e Patrícia Vieira

Requisitos para compilação: battle.c, battle.h, game.c, game.h, structs.c, structs.h, battleship.c.
Como compilar: make battleship

Lista de bibliotecas criadas: structs(.c e .h), game(.c e .h) battle(.c e .h).
Bibliotecas standard utilizadas: stdio.h, stdlib, string.h, ctype.h, time.h.

structs:
  Contém as definições básicas das estruturas usadas. As definições de board, bitmap e cell estão aqui presentes, bem como função para apagar boards, rodar peças, etc. Os detalhes sobre cada função estão presentes na documentação.

game:
  Depende de structs. Contém todas as funções necessárias para a parte inicial do jogo, em que os jogadores escolhem o número de peças, como as colocar, e a inserção em si. Tem ainda grande parte de funções que têm como propósito apresentar alguma parte gráfica que se repita várias vezes e.g. o título Battleship (função Title()). Os detalhes sobre cada função estão presentes na documentação.

battle:
  Depende de structs e de game. Aqui estão definidas as funções necessárias à segunda parte do jogo, onde depois de as peças estarem colocadas, cada jogador irá atacar o outro por turnos. Contém formas de descobrir quantas peças de jogo ainda são válidas, como apresentar uma versão alterada do tabuleiro do adversário para saber os tiros já atirados, etc. Os detalhes sobre cada função estão presentes na documentação.

battleship:
  Depende de structs, game e de battle. Onde se encontra o main do projeto, é aqui que são utilizadas as funções definidas nas bibliotecas anteriores. A parte mais importante será o loop que define a lógica jogo; cada iteração será correspondente a um turno de um jogador, alternando através de uma flag. Antes de o turno começar, é verificado quantas peças ainda estão intactas, e assim que um dos tabuleiros não tiver mais peças válidas, o jogo termina e é declarado o vencedor.


  Regras para a nossa versão de battleship:
- O jogo tem 2 jogadores que irão jogar um contra o outro.
- Existem 5 tipos de barcos disponíveis, dos quais pelo menos 1 de cada tem que estar presente em todos os jogos.
- O número de barcos e quais é definido no início do jogo, e é igual para ambos de forma a garantir um máximo de justiça entre os dois tabuleiros (um jogador com metade dos barcos do outro estará sempre a uma maior vantagem). O modo de inserção (manual ou automático) é também comum aos dois jogadores, e escolhido antes da inserção.
- Os barcos podem estar uns aos lados dos outros, mas a interseção de peças não é permitida.
