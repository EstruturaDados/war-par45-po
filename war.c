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

// NÍVEL AVENTUREIRO: CÓDIGO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de dados para o território.
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Protótipos das funções.
void cadastrarTerritorios(struct Territorio* mapa, int total);
void exibirTerritorios(struct Territorio* mapa, int total);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);

// Função Principal.
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios.
    int totalTerritorios;

    printf("--- WAR ESTRUTURADO (NIVEL AVENTUREIRO) ---\n");
    printf("Quantos territorios existem no mapa? ");
    scanf("%d", &totalTerritorios);

    // Alocação dinâmica de memória para o mapa.
    struct Territorio* mapa = (struct Territorio*) calloc(totalTerritorios, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, totalTerritorios);
    int opcao = 0;
    while (opcao != 2) {
        exibirTerritorios(mapa, totalTerritorios);
        printf("\nOpcoes:\n1. Atacar\n2. Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idxAtacante, idxDefensor;
            printf("\nEscolha o territorio ATACANTE (pelo numero): ");
            scanf("%d", &idxAtacante);
            printf("Escolha o territorio DEFENSOR (pelo numero): ");
            scanf("%d", &idxDefensor);
            idxAtacante--; 
            idxDefensor--;

            if (idxAtacante < 0 || idxAtacante >= totalTerritorios || idxDefensor < 0 || idxDefensor >= totalTerritorios) {
                printf("\nERRO: Territorio invalido!\n");
            } else if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
                printf("\nERRO: Voce nao pode atacar sua propria cor!\n");
            } else if (mapa[idxAtacante].tropas <= 1) {
                printf("\nERRO: O atacante precisa de mais de 1 tropa!\n");
            } else {
                atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
            }
             printf("\nPressione Enter para continuar...");
            while(getchar()!='\n'); getchar();
        }
    }

    liberarMemoria(mapa); // Libera a memória alocada.
    printf("\nJogo finalizado.\n");
    return 0;
}

// Função para cadastrar os territórios.
void cadastrarTerritorios(struct Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n--- Dados do Territorio %d ---\n", i + 1);
        printf("Nome: "); scanf("%s", (mapa + i)->nome);
        printf("Cor: "); scanf("%s", (mapa + i)->cor);
        printf("Tropas: "); scanf("%d", &(mapa + i)->tropas);
    }
}

// Função para exibir o mapa.
void exibirTerritorios(struct Territorio* mapa, int total) {
    printf("\n\n------------------- MAPA ATUAL -------------------\n");
    for (int i = 0; i < total; i++) {
        printf(" %d. %-15s | Cor: %-10s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("--------------------------------------------------\n");
}

// Função que simula o ataque.
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;
    printf("\n--- BATALHA: %s vs %s ---\n", atacante->nome, defensor->nome);
    printf("Dado de Ataque: %d\nDado de Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("\nVITORIA! %s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        int tropasMovidas = atacante->tropas / 2;
        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;
    } else {
        printf("\nDERROTA! O ataque falhou.\n");
        atacante->tropas--;
    }
}

// Função para liberar memória.
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}