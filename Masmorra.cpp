#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

/* Cores */
#define RESETAR   "\x1b[0m"
#define VERMELHO  "\x1b[31m"
#define VERDE     "\x1b[32m"
#define AMARELO   "\x1b[33m"
#define AZUL      "\x1b[34m"
#define CIANO     "\x1b[36m"

/* Configura��o do mapa  */
#define LINHAS 3
#define COLUNAS 3
#define MAX_TEXTO 80

/*  Posi��o inicial e posi��o da rel�quia */
#define INICIO_X 0
#define INICIO_Y 0
#define RELIQUIA_X 1
#define RELIQUIA_Y 1

/* Vetores de nomes e descri��es */
char nomes[LINHAS][COLUNAS][MAX_TEXTO] = {
    { "Entrada Principal", "P�tio Coberto", "Jardim Musgoso" },
    { "Galeria Estreita",  "Sal�o Antigo",  "Sala do Guardi�o" },
    { "Escadaria Ru�da",   "Biblioteca Velha", "Santu�rio Perdido" }
};

char descricoes[LINHAS][COLUNAS][MAX_TEXTO] = {
    { "Um port�o antigo, quebrado e todo enferrujado. Este � o ponto inicial.",
      "Colunas gastas cercam o p�tio.",
      "Um jardim �mido e coberto de musgo." },

    { "Um corredor estreito com tochas apagadas e um escuro total.",
      "Um sal�o antigo com vidros quebrados e um sil�ncio profundo.",
      "Um espa�o sombrio com marcas de garras e marcas de sangue nas paredes." },

    { "Degraus gastos que n�o levam a lugar algum.",
      "Prateleiras ca�das com livros empoeirados.",
      "Um altar em ru�nas tomado por plantas." }
};

void mostrarAjuda() {
    printf(CIANO "Comandos: norte(n), sul(s), leste(l), oeste(o), verificar, ajuda, sair\n" RESETAR);
}

void mostrarLocal(int x, int y) {
    printf(AZUL "\nVoc� est� em: %s" RESETAR "\n", nomes[x][y]);
    printf("%s\n", descricoes[x][y]);
}

int main() {
    int x = INICIO_X, y = INICIO_Y;
    bool temReliquia = false;
    char comando[30];

    setlocale(LC_ALL, "Portuguese");

    printf(VERDE "	****** A Ca�ada � Rel�quia Antiga ******" RESETAR "\n\n");
    printf("Encontre a Rel�quia Antiga e leve-a de volta para a Entrada Principal!\n");
    printf("Digite " AMARELO "ajuda" RESETAR " para ver os comandos.\n\n");

    while (true) {
        mostrarLocal(x, y);

        if (x == RELIQUIA_X && y == RELIQUIA_Y && !temReliquia) {
            printf(VERDE "\nVoc� encontrou a Rel�quia Antiga!\n" RESETAR);
            temReliquia = true;
        }

        // Condi��o de vit�ria
        if (x == INICIO_X && y == INICIO_Y && temReliquia) {
            printf(VERDE "\nParab�ns! Voc� trouxe a Rel�quia Antiga de volta.\nVoc� venceu o jogo! \n" RESETAR);
            break;
        }

        printf("\n> ");
        if (!fgets(comando, sizeof(comando), stdin)) break;

        if (comando[strlen(comando) - 1] == '\n') {
            comando[strlen(comando) - 1] = '\0';
        }

        /* === Movimentos === */
        if (strcmp(comando, "norte") == 0 || strcmp(comando, "n") == 0) {
            if (x > 0) x--;
            else printf(VERMELHO "N�o d� para ir ao norte!\n" RESETAR);
        }
        else if (strcmp(comando, "sul") == 0 || strcmp(comando, "s") == 0) {
            if (x < LINHAS-1) x++;
            else printf(VERMELHO "N�o d� para ir ao sul!\n" RESETAR);
        }
        else if (strcmp(comando, "leste") == 0 || strcmp(comando, "l") == 0) {
            if (y < COLUNAS-1) y++;
            else printf(VERMELHO "N�o d� para ir ao leste!\n" RESETAR);
        }
        else if (strcmp(comando, "oeste") == 0 || strcmp(comando, "o") == 0) {
            if (y > 0) y--;
            else printf(VERMELHO "N�o d� para ir ao oeste!\n" RESETAR);
        }
        /* === Outros comandos === */
        else if (strcmp(comando, "verificar") == 0) {
            if (temReliquia)
                printf(VERDE "Voc� carrega a Rel�quia Antiga.\n" RESETAR);
            else
                printf("Seu invent�rio est� vazio.\n");
        }
        else if (strcmp(comando, "ajuda") == 0) {
            mostrarAjuda();
        }
        else if (strcmp(comando, "sair") == 0) {
            printf(AMARELO "Voc� decidiu sair da aventura.\n" RESETAR);
            break;
        }
        else {
            printf(VERMELHO "Comando inv�lido! Digite 'ajuda' para ver os comandos.\n" RESETAR);
        }
    }

    return 0;
}
