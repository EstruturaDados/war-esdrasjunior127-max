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














int main() {
    Territorio territorios[MAX_TERRITORIOS];

    printf("=== Cadastro de Territorios ===\n");

    // Cadastro dos 5 territórios
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, MAX_STRING, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remover \n

        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, MAX_STRING, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // remover \n

        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // limpar buffer do scanf
    }

    // Exibição dos territórios cadastrados
    printf("\n=== Lista de Territorios Cadastrados ===\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}

