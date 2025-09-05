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

/* Configuração do mapa  */
#define LINHAS 3
#define COLUNAS 3
#define MAX_TEXTO 80

/*  Posição inicial e posição da relíquia */
#define INICIO_X 0
#define INICIO_Y 0
#define RELIQUIA_X 1
#define RELIQUIA_Y 1

/* Vetores de nomes e descrições */
char nomes[LINHAS][COLUNAS][MAX_TEXTO] = {
    { "Entrada Principal", "Pátio Coberto", "Jardim Musgoso" },
    { "Galeria Estreita",  "Salão Antigo",  "Sala do Guardião" },
    { "Escadaria Ruída",   "Biblioteca Velha", "Santuário Perdido" }
};

char descricoes[LINHAS][COLUNAS][MAX_TEXTO] = {
    { "Um portão antigo, quebrado e todo enferrujado. Este é o ponto inicial.",
      "Colunas gastas cercam o pátio.",
      "Um jardim úmido e coberto de musgo." },

    { "Um corredor estreito com tochas apagadas e um escuro total.",
      "Um salão antigo com vidros quebrados e um silêncio profundo.",
      "Um espaço sombrio com marcas de garras e marcas de sangue nas paredes." },

    { "Degraus gastos que não levam a lugar algum.",
      "Prateleiras caídas com livros empoeirados.",
      "Um altar em ruínas tomado por plantas." }
};

void mostrarAjuda() {
    printf(CIANO "Comandos: norte(n), sul(s), leste(l), oeste(o), verificar, ajuda, sair\n" RESETAR);
}

void mostrarLocal(int x, int y) {
    printf(AZUL "\nVocê está em: %s" RESETAR "\n", nomes[x][y]);
    printf("%s\n", descricoes[x][y]);
}

int main() {
    int x = INICIO_X, y = INICIO_Y;
    bool temReliquia = false;
    char comando[30];

    setlocale(LC_ALL, "Portuguese");

    printf(VERDE "	****** A Caçada à Relíquia Antiga ******" RESETAR "\n\n");
    printf("Encontre a Relíquia Antiga e leve-a de volta para a Entrada Principal!\n");
    printf("Digite " AMARELO "ajuda" RESETAR " para ver os comandos.\n\n");

    while (true) {
        mostrarLocal(x, y);

        if (x == RELIQUIA_X && y == RELIQUIA_Y && !temReliquia) {
            printf(VERDE "\nVocê encontrou a Relíquia Antiga!\n" RESETAR);
            temReliquia = true;
        }

        // Condição de vitória
        if (x == INICIO_X && y == INICIO_Y && temReliquia) {
            printf(VERDE "\nParabéns! Você trouxe a Relíquia Antiga de volta.\nVocê venceu o jogo! \n" RESETAR);
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
            else printf(VERMELHO "Não dá para ir ao norte!\n" RESETAR);
        }
        else if (strcmp(comando, "sul") == 0 || strcmp(comando, "s") == 0) {
            if (x < LINHAS-1) x++;
            else printf(VERMELHO "Não dá para ir ao sul!\n" RESETAR);
        }
        else if (strcmp(comando, "leste") == 0 || strcmp(comando, "l") == 0) {
            if (y < COLUNAS-1) y++;
            else printf(VERMELHO "Não dá para ir ao leste!\n" RESETAR);
        }
        else if (strcmp(comando, "oeste") == 0 || strcmp(comando, "o") == 0) {
            if (y > 0) y--;
            else printf(VERMELHO "Não dá para ir ao oeste!\n" RESETAR);
        }
        /* === Outros comandos === */
        else if (strcmp(comando, "verificar") == 0) {
            if (temReliquia)
                printf(VERDE "Você carrega a Relíquia Antiga.\n" RESETAR);
            else
                printf("Seu inventário está vazio.\n");
        }
        else if (strcmp(comando, "ajuda") == 0) {
            mostrarAjuda();
        }
        else if (strcmp(comando, "sair") == 0) {
            printf(AMARELO "Você decidiu sair da aventura.\n" RESETAR);
            break;
        }
        else {
            printf(VERMELHO "Comando inválido! Digite 'ajuda' para ver os comandos.\n" RESETAR);
        }
    }

    return 0;
}
