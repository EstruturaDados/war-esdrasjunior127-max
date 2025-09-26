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

