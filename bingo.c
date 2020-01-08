#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* BINGO! 
 * Developed by:
 * Igor Rocha
 * Lucas Arthur
 * Matheus Fireman
 */

#define joker 0 //definição do coringa e da marcação das cartelas igual a 0

typedef struct //dados dos jogadores
{
  char nome[500]; //nome do jogador
  int cartela[4][5]; //cartela do jogador
}jogadores;

void welcome() //apresenta o programa
{
  printf("*********************************************************************\n");
  printf("*                                                                   *\n");
  printf("*                                                                   *\n");
  printf("*            ****     *    * *    *    ******     *******           *\n");
  printf("*            *   *    *    *  *   *    *          *     *           *\n");
  printf("*            ****     *    *    * *    *    **    *     *           *\n");
  printf("*            *   *    *    *      *    *     *    *     *           *\n");
  printf("*            ****     *    *      *    *******    *******           *\n");
  printf("*                                                                   *\n");
  printf("*                                                                   *\n");
  printf("*********************************************************************\n");
}

void insertionSort(int *sorteados, int tamanho)
{
  int j, aux;
  aux = sorteados[tamanho];
  for(j = tamanho; (j > 0) && (aux < sorteados[j - 1]); j--)
  {
    sorteados[j] = sorteados[j - 1];
  }    
  sorteados[j] = aux;
}

/* função de ordenação das cartelas */
void ordenaCartela(jogadores *jogador, int i, int linha, int coluna)
{
  int j, k, menor, cont = 0;
  int v[linha * coluna];

  for(j = 0; j < linha; j++)
  {
    for(k = 0; k < coluna; k++)
    {
      v[cont] = jogador[i].cartela[j][k];
      cont++;
    }
  }

  for(j =0 ; j <linha*coluna; j++)
  {
    menor=v[j];
    for(k = 0; k < linha*coluna; k++)
    {
        if(v[k]<menor)
        {
            menor=v[k];
            int aux = v[j];
            v[j] = menor;
            v[k] = aux;
        }
    }
  }
  for(j = 0, cont = 0; j < linha; j++)
  {
    for(k = 0; k < coluna; k++)
    {
      jogador[i].cartela[j][k] = v[cont];
      cont++;
    }
  }
}

/* função que confere se já existe certo número já existe na cartela */
int existeNum(jogadores *jogador, int chave)
{
  int v = rand() % 99;
  for(int j = 0; j < 4; j++)
  {
    for(int k = 0; k < 5; k++)
    {
      if(jogador->cartela[j][k] == chave)
        return existeNum(jogador, v);
    }
  }
  return chave;
}

/*função que gera as cartelas dos jogadores */ 
void geraCartela(jogadores *jogador, int i)
{
  int valor, existe /* variável de conferencia */;
  for(int j = 0; j < 4; j++)
  {
    for(int k = 0; k < 5; k++)
    {
      valor = 1 + (rand() % 99); /* geração dos valores de 1 a 99 */
      existe = existeNum(&jogador[i], valor);
      jogador[i].cartela[j][k] = existe; 
    }
  }
}

/* Função que confere a existencia de um coringa na cartela */
int existeCoringa(jogadores *jogador, int i, int linha, int coluna)
{
  for(int k = 0; k < 5; k++)
  {
    if(jogador[i].cartela[linha][k] == joker)
      return 1; //retorna 1 caso exista o coringa na linha
  }

  for(int j = 0; j < 4; j++)
  {
    if(jogador[i].cartela[j][coluna] == joker)
      return 2; //retorna 2 caso exista o coringa na coluna
  }

  return 3; //retorna 3 caso o coringa não exista na posição
}

void coringa(jogadores *jogador, int i)
{
  int linha, coluna;
  int existe;
  for(int q = 0; q < 3; q++)
  {
    linha = rand() % 4; //gera uma posição de linha aleatoria
    coluna = rand() % 5; //gera uma posição de coluna aleatoria

    existe = existeCoringa(jogador, i, linha, coluna);

    if(existe != 3)
    {
      do
      {
        if(existe == 1)
        {
          linha = rand() % 4; //gera uma nova posição de linha
          existe = existeCoringa(jogador, i, linha, coluna);
        }
        else if(existe == 2)
        {
          coluna = rand() % 5; //gera uma nova posição de coluna
          existe = existeCoringa(jogador, i, linha, coluna);
        }
      }while(existe != 3);

      jogador[i].cartela[linha][coluna] = joker;
    }
    
    else
      jogador[i].cartela[linha][coluna] = joker;
  }  
  
}

int existeBola(int *sorteados, int tam, int bola)
{
  int i, inicio = 0, meio, fim = tam - 1, ball;

  while(inicio <= fim)
  {
    meio = (inicio + fim)/2;
    if(bola < sorteados[meio])
      fim = meio - 1; //procura na metade esquerda
    else
    {
      if(bola > sorteados[meio])
        inicio = meio + 1; //procura na metade direita
      else //caso a bola seja achada no vetor
      {
        ball = 1 + (rand() % 99);
        return ball; // retorna uma nova bola
      }
    }
  }
  return -1; //caso a bola não seja encontrada em nenhuma posição do vetor
}

void marcaCartela(jogadores *jogador, int i, int bola)
{
  for(int j = 0; j < 4; j++) //linhas
  {
    for(int k = 0; k < 5; k++) //colunas
    {
      if(jogador[i].cartela[j][k] == bola) // troca o valor que está na posição por 0 caso o valor for igual a bola sorteada
        jogador[i].cartela[j][k] = joker;
    }
  }
}

void printaCartela(jogadores *jogador, int i)
{
  for(int j = 0; j < 4; j++)
  {
    printf("|");
    for(int k = 0; k < 5; k++)
    {
      if(jogador[i].cartela[j][k] < 10)
        printf("|  %d   |", jogador[i].cartela[j][k]);
      else
        printf("|  %d  |", jogador[i].cartela[j][k]);
    }
    printf("|");
    printf("\n");
  }
}

/*confere a vitória dos jogadores pela marcação das linhas*/
int confereLinha(jogadores *jogador, int qt)
{
  int linha;
  for(int i = 0; i < qt; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      linha = 0; //define a variavel de contagem de linha começando em 0
      switch(j)
      {
        case 0: //verifica se a linha 0 está toda marcada
          for(int k = 0; k < 5; k++)
          {
            if(jogador[i].cartela[j][k] == joker)
              linha++;
          }
          if(linha == 5)
            return i; // caso esteja toda marcada, retorna o indice do jogador vencedor
          break;
        case 1: //verifica se a linha 1 está toda marcada
          for(int k = 0; k < 5; k++)
          {
            if(jogador[i].cartela[j][k] == joker)
              linha++;
          }
          if(linha == 5)
            return i;// caso esteja toda marcada, retorna o indice do jogador vencedor
          break;
        case 2: //verifica se a linha 2 está toda marcada
          for(int k = 0; k < 5; k++)
          {
            if(jogador[i].cartela[j][k] == joker)
              linha++;
          }
          if(linha == 5)
            return i;// caso esteja toda marcada, retorna o indice do jogador vencedor
          break;
        case 3: //verifica se a linha 3 está toda marcada
          for(int k = 0; k < 5; k++)
          {
            if(jogador[i].cartela[j][k] == joker)
              linha++;
          }
          if(linha == 5)
            return i;// caso esteja toda marcada, retorna o indice do jogador vencedor
          break;
      }
    }
  }
  return -1;
}

/*confere a vitória dos jogadores pela marcação das colunas */
int confereColuna(jogadores *jogador, int qt)
{
  int coluna;
  for(int i = 0; i < qt; i++)
  {
    for(int k = 0; k < 5; k++)
    {
      coluna = 0; //define a variavel de contagem de coluna como 0
      switch(k)
      {
        case 0: //confere se a coluna 0 está toda marcada
          for(int j = 0; j < 4; j++)
          {
            if(jogador[i].cartela[j][k] == joker)
              coluna++;
          }
          if(coluna == 4)
            return i; //retorna o indice do jogador vencedor
          break;
        case 1: //confere se a coluna 1 está toda marcada
          for(int j = 0; j < 4; j++)
          {
            if(jogador[i].cartela[j][k] == joker)
              coluna++;
          }
          if(coluna == 4)
            return i; //retorna o indice do jogador vencedor
          break;
        case 2: //confere se a coluna 2 está toda marcada
          for(int j = 0; j < 4; j++)
          {
            if(jogador[i].cartela[j][k] == joker)
              coluna++;
          }
          if(coluna == 4)
            return i; //retorna o indice do jogador vencedor
          break;
        case 3: //confere se a coluna 3 está toda marcada
          for(int j = 0; j < 4; j++)
          {
            if(jogador[i].cartela[j][k] == joker)
              coluna++;
          }
          if(coluna == 4)
            return i; //retorna o indice do jogador vencedor
          break;
        case 4: //confere se a coluna 4 está toda marcada
          for(int j = 0; j < 4; j++)
          {
            if(jogador[i].cartela[j][k] == joker)
              coluna++;
          }
          if(coluna == 4)
            return i; //retorna o indice do jogador vencedor
          break;
      }
    }
  }
  return -1;
}
void apresentaCartela(jogadores *jogador, int qt, int bola)
{
  for(int i = 0; i < qt; i++)
    {
      marcaCartela(jogador, i, bola); //marca a bola sorteada na cartela dos jogadores
      printf("\nEssa é sua cartela, %s", jogador[i].nome); //apresenta as cartelas dos jogadores
      printaCartela(jogador, i);
    }
}

/* FUNÇÃO MAIN */
int main(void) 
{
  srand(time(NULL)); 
  
  int qt_jogadores; //quantidade de jogadores
  int bola /*bola sorteada a cada rodada */, tamanho = 0 /*tamanho do vetor de sorteio das bolas */;
  int winlinha, wincoluna; //condições de vitória
  int *sorteados = (int *) malloc(sizeof(int)); //vetor que receberá as bolas sorteadas
  char sort;
  
  welcome(); //apresentação do programa
  printf("Informe a quantidade de jogadores no bingo: ");
  scanf("%d", &qt_jogadores);
  jogadores jogador[qt_jogadores]; //vetor que recebe os dados dos jogadores

  getchar();

  for(int i = 0; i < qt_jogadores; i++) //laço para a leitura dos dados dos jogadores 
  {
    printf("Nome do jogador: ");
    fgets(jogador[i].nome, 500, stdin);
    geraCartela(jogador, i); //gera a cartela dos jogadores
    ordenaCartela(jogador, i, 4, 5); //ordena a cartela dos jogadores
    coringa(jogador, i); //põe o coringa nas cartelas
    printf("\nEssa é sua cartela, %s", jogador[i].nome); //apresenta as cartelas dos jogadores
    printaCartela(jogador, i);
  }

  
  do
  {
    int existe; //variável de verificação das bolas repetidas
    bola = 1 + (rand() % 99); //sorteio de uma bola
      
    sorteados = (int *) realloc(sorteados, (1 + tamanho) * sizeof(int)); //aumenta o tamanho do vetor de bolas sorteadas a cada rodada
    existe = existeBola(sorteados, tamanho, bola); //confere a existencia da bola

    if(existe != -1) //caso a bola já tenha sido sorteada
    {
      do
      {
        bola = existe;
        sorteados[tamanho] = bola;
        existe = existeBola(sorteados, tamanho, bola); //confere se a bola existe de novo
      }while(existe != -1);
    }
    else //caso a bola ainda não tenha sido sorteada
      sorteados[tamanho] = bola; //põe a bola sorteada no vetor das bolas sorteadas
      
    printf("\nBola sorteada na rodada atual: (%d)\n", sorteados[tamanho]);
    printf("Bolas sorteadas até o momento: ");
    insertionSort(sorteados, tamanho); //ordena o vetor das bolas sorteadas
      
    printf("[");                              // irá mostrar todas
    for(int j = 0; j < (tamanho + 1) ; j++)   // as bolas sorteadas
    {                                         // até a rodada em que
      printf("%d | ", sorteados[j]);          // o jogo se encontra 
    }                                         //
    printf("]\n\n");                          //
      
    apresentaCartela(jogador, qt_jogadores, bola); //apresenta a cartela marcada após cada rodada

    winlinha = confereLinha(jogador, qt_jogadores); //confere se alguém venceu pela marcação de linha
    wincoluna = confereColuna(jogador, qt_jogadores); //confere se alguém venceu pela marcação de colunas
    if(winlinha != -1 || wincoluna != -1)
    {
      if(winlinha != -1)
      {
        printf("\nO VENCEDOR DO BINGO É %s", jogador[winlinha].nome);
        printf("Venceu por marcação de linha inteira!\n");
      }
      else
      {
        printf("\nO VENCEDOR DO BINGO É %s", jogador[wincoluna].nome);
        printf("Venceu por marcação de coluna inteira!\n");
      }
      break;
    }
    else
    {
      printf("Sortear nova bola? [s/n]: ");
      scanf("%c", &sort);
      getchar();
      tamanho++; //aumenta o tamanho a variável que cuidará do aumento do vetor das bolas sorteadas
    }
  }while(sort == 's');
    
  if(sort != 's')
    printf("Jogo interrompido!\n");
}