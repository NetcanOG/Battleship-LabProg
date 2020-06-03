TP2_groupF - Miguel Ramos e Patrícia Vieira

Requisitos para compilação do jogo original: graphics.c, graphics.h, battle.c, battle.h, game.c, game.h, structs.c, structs.h, battleship.c.
Requisitos para compilação do jogo utilizando a QuadTree: graphics.c, graphics.h, qdbattle.c, qdbattle.h, qdgame.c, qdgame.h, qdtree.c, qdtree.h, quadbattleship.c

Como compilar o jogo original: make battleship
Como compilar o jogo utilizando a quadtree: make quadbattleship

Como remover os .o's e executáveis: make clean

Lista de bibliotecas criadas: structs(.c e .h), game(.c e .h) battle(.c e .h), graphics(.c e .h), qdbattle(.c e .h), qdgame(.c e .h), qdtree(.c e .h).
Bibliotecas standard utilizadas: stdio.h, stdlib, string.h, ctype.h, time.h.

graphics:
  Tem grande parte das funções que têm como propósito apresentar alguma componente gráfica que se repita várias vezes e.g. o título Battleship (função Title()).

structs:
  Depende de graphics. Contém as definições básicas das estruturas usadas. As definições de board, bitmap e cell estão aqui presentes, bem como função para apagar boards, rodar peças, etc. Os detalhes sobre cada função estão presentes na documentação.

game:
  Depende de graphics e de structs. Contém todas as funções necessárias para a parte inicial do jogo, em que os jogadores escolhem o número de peças, como as colocar, e a inserção em si. Os detalhes sobre cada função estão presentes na documentação.

battle:
  Depende de graphics, structs e de game. Aqui estão definidas as funções necessárias à segunda parte do jogo, onde depois de as peças estarem colocadas, cada jogador irá atacar o outro por turnos. Contém formas de descobrir quantas peças de jogo ainda são válidas, como apresentar uma versão alterada do tabuleiro do adversário para saber os tiros já atirados, etc.

battleship:
  Depende de graphics, structs, game e de battle. Onde se encontra o main do projeto, é aqui que são utilizadas as funções definidas nas bibliotecas anteriores. A parte mais importante será o loop que define a lógica jogo; cada iteração será correspondente a um turno de um jogador, alternando através de uma flag. Antes de o turno começar, é verificado quantas peças ainda estão intactas, e assim que um dos tabuleiros não tiver mais peças válidas, o jogo termina e é declarado o vencedor.

qdtree:
  Depende de graphics. É o equivalente à biblioteca structs, mas para a versão de jogo da quadtree. Contém para criação da mesma, inserção de peças e coordenadas, etc. Os detalhes sobre cada função estão presentes na documentação.

qdgame:
  Depende de graphics e de qdtree. É o equivalente à biblioteca game para o jogo baseado na quadtree.

qdbattle:
  Depende de graphics, qdtree e de qdgame. É o equivalente à biblioteca battle para o jogo baseado na quadtree.

quadbattleship:
  Depende de graphics, qdtree, qdgame e de qdbattle. É o equivalente ao battleship para o jogo baseado na quadtree.


  Regras para a nossa versão de battleship:
- O jogo tem 2 jogadores que irão jogar um contra o outro.
- Existem 5 tipos de barcos disponíveis, dos quais pelo menos 1 de cada tem que estar presente em todos os jogos.
- O número de barcos e quais é definido no início do jogo, e é igual para ambos de forma a garantir um máximo de justiça entre os dois tabuleiros (um jogador com metade dos barcos do outro estará sempre a uma maior vantagem). O modo de inserção (manual ou automático) é também comum aos dois jogadores, e escolhido antes da inserção.
- Os barcos podem estar uns aos lados dos outros, mas a interseção de peças não é permitida.