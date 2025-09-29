#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_TERRITORIOS 5

typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
} Territorio;

/* ------------------ MISSOES ------------------ */
char* missoesDisponiveis[] = {
    "Conquistar 3 territorios consecutivos",
    "Eliminar todas as tropas da cor vermelha",
    "Conquistar 4 territorios",
    "Ter mais tropas que qualquer outra cor",
    "Conquistar o territorio azul"
};
int totalMissoes = sizeof(missoesDisponiveis) / sizeof(missoesDisponiveis[0]);

/* ------------------ FUNÇÕES DE APOIO ------------------ */
int equalIgnoreCase(const char* a, const char* b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
        a++; b++;
    }
    return *a == '\0' && *b == '\0';
}

int contarTerritoriosPorCor(Territorio* mapa, int tamanho, const char* cor) {
    int cnt = 0;
    for (int i = 0; i < tamanho; i++) {
        if (equalIgnoreCase(mapa[i].cor, cor)) cnt++;
    }
    return cnt;
}

int somaTropasPorCor(Territorio* mapa, int tamanho, const char* cor) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        if (equalIgnoreCase(mapa[i].cor, cor)) soma += mapa[i].tropas;
    }
    return soma;
}

/* ------------------ FUNÇÕES DE MISSÃO ------------------ */
void atribuirMissao(char** destino, char* missoes[], int totalMissoes, int* missaoIndex) {
    if (totalMissoes <= 0) return;
    int idx = rand() % totalMissoes;
    *missaoIndex = idx;

    *destino = (char*) malloc(strlen(missoes[idx]) + 1);
    if (*destino == NULL) {
        printf("Erro ao alocar memória para a missão!\n");
        exit(1);
    }
    strcpy(*destino, missoes[idx]);
}

void exibirMissao(const char* missao) {
    printf("\n=== SUA MISSÃO SECRETA ===\n%s\n", missao);
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho, const char* corJogador, int missaoIndex) {
    if (missaoIndex == 0) {
        for (int i = 0; i <= tamanho - 3; i++) {
            if (equalIgnoreCase(mapa[i].cor, corJogador) &&
                equalIgnoreCase(mapa[i+1].cor, corJogador) &&
                equalIgnoreCase(mapa[i+2].cor, corJogador)) {
                return 1;
            }
        }
        return 0;
    } else if (missaoIndex == 1) {
        int soma = 0;
        for (int i = 0; i < tamanho; i++) {
            if (equalIgnoreCase(mapa[i].cor, "vermelho")) {
                soma += mapa[i].tropas;
            }
        }
        return soma == 0;
    } else if (missaoIndex == 2) {
        return contarTerritoriosPorCor(mapa, tamanho, corJogador) >= 4;
    } else if (missaoIndex == 3) {
        int minha = somaTropasPorCor(mapa, tamanho, corJogador);
        int maiorOutro = 0;
        for (int i = 0; i < tamanho; i++) {
            if (!equalIgnoreCase(mapa[i].cor, corJogador)) {
                int soma = somaTropasPorCor(mapa, tamanho, mapa[i].cor);
                if (soma > maiorOutro) maiorOutro = soma;
            }
        }
        return minha > maiorOutro && minha > 0;
    } else if (missaoIndex == 4) {
        for (int i = 0; i < tamanho; i++) {
            if (equalIgnoreCase(mapa[i].nome, "azul") && 
                equalIgnoreCase(mapa[i].cor, corJogador)) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

/* ------------------ FUNÇÕES DO JOGO ------------------ */
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\n=== Territórios cadastrados ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas <= 0) {
        printf("Ataque impossível: território atacante sem tropas.\n");
        return;
    }
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- Batalha ---\n");
    printf("%s (Atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;
        if (atacante->tropas < 0) atacante->tropas = 0;
    } else {
        printf("Defensor resistiu! O atacante perde 1 tropa.\n");
        if (atacante->tropas > 0) atacante->tropas -= 1;
    }
}

void liberarMemoria(Territorio* mapa, char* missao) {
    if (mapa) free(mapa);
    if (missao) free(missao);
    printf("\nMemória liberada!\n");
}

/* ------------------ MAIN ------------------ */
int main() {
    srand((unsigned int) time(NULL));

    Territorio* mapa = (Territorio*) malloc(MAX_TERRITORIOS * sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\n--- Território %d ---\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    char corJogador[20];
    printf("\nDigite sua cor (a que representa você): ");
    fgets(corJogador, sizeof(corJogador), stdin);
    corJogador[strcspn(corJogador, "\n")] = '\0';

    char* missaoDoJogador = NULL;
    int missaoIndex = -1;
    atribuirMissao(&missaoDoJogador, missoesDisponiveis, totalMissoes, &missaoIndex);
    exibirMissao(missaoDoJogador);

    int opcao;
    while (1) {
        printf("\n=== MENU ===\n");
        printf("1 - Listar territórios\n");
        printf("2 - Atacar\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            exibirMapa(mapa, MAX_TERRITORIOS);
        } else if (opcao == 2) {
            int atq, def;
            printf("\nEscolha o território atacante (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &atq); getchar();
            printf("Escolha o território defensor (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &def); getchar();

            if (atq < 1 || atq > MAX_TERRITORIOS || def < 1 || def > MAX_TERRITORIOS || atq == def) {
                printf("Escolha inválida!\n");
            } else {
                atacar(&mapa[atq - 1], &mapa[def - 1]);

                // Verificação da missão
                if (verificarMissao(missaoDoJogador, mapa, MAX_TERRITORIOS, corJogador, missaoIndex)) {
                    printf("\n*** PARABÉNS! Você cumpriu sua missão: %s ***\n", missaoDoJogador);
                    break;
                } else {
                    printf("\n(Sua missão secreta ainda não foi cumprida... continue jogando!)\n");
                }
            }
        } else if (opcao == 3) {
            printf("Saindo do jogo...\n");
            break;
        } else {
            printf("Opção inválida!\n");
        }
    }

    liberarMemoria(mapa, missaoDoJogador);
    return 0;
}
