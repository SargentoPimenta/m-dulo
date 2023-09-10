#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 5
#define NAVIOS 5
#define AGUA '~'
#define NAVIO 'N'
#define ERRO 'E'
#define ACERTO 'A'

void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
    printf("   ");
    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%d  ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < TAMANHO; j++)
        {
            printf("%c  ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void imprimirTabuleiroEmoji(char tabuleiro[TAMANHO][TAMANHO])
{
    printf("   ");
    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%d  ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++)
    {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < TAMANHO; j++)
        {
            if (tabuleiro[i][j] == AGUA)
            {
                printf("🌊 ");
            }
            else if (tabuleiro[i][j] == ACERTO)
            {
                printf("💥 ");
            }
            else if (tabuleiro[i][j] == ERRO)
            {
                printf("⭕ ");
            }
            else
            {
                printf("🚢 ");
            }
        }
        printf("\n");
    }
}

void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO])
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void posicionarNaviosAleatorios(char tabuleiro[TAMANHO][TAMANHO], int numNavios)
{
    int x, y;
    for (int i = 0; i < numNavios; i++)
    {
        do
        {
            x = rand() % TAMANHO;
            y = rand() % TAMANHO;
        } while (tabuleiro[x][y] == NAVIO);
        tabuleiro[x][y] = NAVIO;
    }
}

int ataqueJogador(char tabuleiro[TAMANHO][TAMANHO])
{
    int linha, coluna;
    char entrada[5];

    do
    {
        printf("Informe a coordenada para o seu ataque (ex: A1): ");
        scanf("%s", entrada);
        linha = entrada[0] - 'A';
        coluna = entrada[1] - '1';
    } while (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO || tabuleiro[linha][coluna] == 'E' || tabuleiro[linha][coluna] == 'A');

    if (tabuleiro[linha][coluna] == NAVIO)
    {
        printf("Você acertou!\n");
        tabuleiro[linha][coluna] = ACERTO;
        return 1;
    }
    else
    {
        printf("Você errou!\n");
        tabuleiro[linha][coluna] = ERRO;
        return 0;
    }
}

int ataqueComputador(char tabuleiro[TAMANHO][TAMANHO])
{
    int linha, coluna;

    do
    {
        linha = rand() % TAMANHO;
        coluna = rand() % TAMANHO;
    } while (tabuleiro[linha][coluna] == 'E' || tabuleiro[linha][coluna] == 'A');

    if (tabuleiro[linha][coluna] == NAVIO)
    {
        printf("A CPU acertou em %c %d!\n", 'A' + linha, coluna + 1);
        tabuleiro[linha][coluna] = ACERTO;
        return 1;
    }
    else
    {
        printf("A CPU errou em %c %d!\n", 'A' + linha, coluna + 1);
        tabuleiro[linha][coluna] = ERRO;
        return 0;
    }
}

int main()
{
    char tabuleiroJogador[TAMANHO][TAMANHO];
    char tabuleiroComputador[TAMANHO][TAMANHO];
    int acertosJogador = 0, acertosComputador = 0;

    srand(time(NULL));

    inicializarTabuleiro(tabuleiroJogador);
    inicializarTabuleiro(tabuleiroComputador);

    posicionarNaviosAleatorios(tabuleiroJogador, NAVIOS);
    posicionarNaviosAleatorios(tabuleiroComputador, NAVIOS);

    while (1)
    {
        printf("Tabuleiro do Jogador:\n");
        imprimirTabuleiroEmoji(tabuleiroJogador);
        printf("\n");
        printf("Tabuleiro da CPU:\n");
        imprimirTabuleiroEmoji(tabuleiroComputador);

        acertosJogador += ataqueJogador(tabuleiroComputador);

        if (acertosJogador == NAVIOS)
        {
            printf("Você venceu! 🎆\n");
            imprimirTabuleiroEmoji(tabuleiroComputador);
            break;
        }

        acertosComputador += ataqueComputador(tabuleiroJogador);

        if (acertosComputador == NAVIOS)
        {
            printf("A CPU venceu! 🎆\n");
            imprimirTabuleiroEmoji(tabuleiroComputador);
            break;
        }
    }

    return 0;
}
