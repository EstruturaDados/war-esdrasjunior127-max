#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TERRITORIOS 5

// Definição da estrutura
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- Batalha ---\n");
    printf("%s (Atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Atacante venceu!\n");

        // transfere cor e metade das tropas para o defensor
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

    } else {
        printf("Defensor resistiu! O atacante perde 1 tropa.\n");
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }
    }
}

// Liberação de memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemória liberada!\n");
}


int main() {
   srand(time(NULL)); // inicializa rand()

    // alocação fixa de 5 territórios
    Territorio* mapa = (Territorio*) malloc(MAX_TERRITORIOS * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // cadastro dos territórios
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

    int opcao;
    do {
        printf("\n=== MENU ===\n");
        printf("1 - Listar territórios\n");
        printf("2 - Atacar\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            printf("\n=== Territórios cadastrados ===\n");
            for (int i = 0; i < MAX_TERRITORIOS; i++) {
                printf("\nTerritório %d:\n", i + 1);
                printf("Nome: %s\n", mapa[i].nome);
                printf("Cor: %s\n", mapa[i].cor);
                printf("Tropas: %d\n", mapa[i].tropas);
            }
        } 
        else if (opcao == 2) {
            int atq, def;

            printf("\nEscolha o território atacante (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &atq);
            getchar();

            printf("Escolha o território defensor (1 a %d): ", MAX_TERRITORIOS);
            scanf("%d", &def);
            getchar();

            if (atq < 1 || atq > MAX_TERRITORIOS || def < 1 || def > MAX_TERRITORIOS || atq == def) {
                printf("Escolha inválida!\n");
            } else {
                atacar(&mapa[atq - 1], &mapa[def - 1]);
            }
        }

    } while (opcao != 3);

    liberarMemoria(mapa);
    return 0;
}
