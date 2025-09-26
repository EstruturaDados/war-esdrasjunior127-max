#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define MAX_STRING 50

// Definição da estrutura
typedef struct {
    char nome[MAX_STRING];
    char cor[MAX_STRING];
    int tropas;
} Territorio;

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
