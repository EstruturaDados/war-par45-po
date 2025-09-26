// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================
// Codigo final (Nivel Mestre)

// NÍVEL NOVATO: CÓDIGO
#include <stdio.h>
#include <string.h>

// Define a estrutura de dados para um território.
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função principal onde o programa inicia.
int main() {
    // Cria um vetor estático para armazenar 5 territórios.
    struct Territorio territorios[5];
    int i; // Variável de controle para os loops.

    printf("--- CADASTRO DE 5 TERRITORIOS (NIVEL NOVATO) ---\n");

    // Loop para cadastrar os 5 territórios.
    for (i = 0; i < 5; i++) {
        printf("\n--- Dados do Territorio %d ---\n", i + 1);
        printf("Digite o nome: ");
        scanf("%s", territorios[i].nome);
        printf("Digite a cor: ");
        scanf("%s", territorios[i].cor);
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\n\n--- DADOS DOS TERRITORIOS CADASTRADOS ---\n");

    // Loop para exibir os dados dos territórios cadastrados.
    for (i = 0; i < 5; i++) {
        printf("\n- Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
    }

    // Indica que o programa terminou com sucesso.
    return 0;
}