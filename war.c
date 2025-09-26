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
// Codigo final"Nivel Mestre"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para o Território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Protótipos das funções
void cadastrarTerritorios(struct Territorio* mapa, int total);
void exibirTerritorios(struct Territorio* mapa, int total);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void atribuirMissao(char* destinoMissao, char* missoes[], int totalMissoes);
void exibirMissao(char* missao);
int verificarMissao(char* missao, struct Territorio* mapa, int totalTerritorios, char* corJogador);
void liberarMemoria(struct Territorio* mapa, char* missao);
void limparBufferEntrada();

// Função Principal
int main() {
    // Inicializa o gerador de números aleatórios. Deve ser a primeira linha dentro do main.
    srand(time(NULL));

    // Vetor de strings com as missões pré-definidas
    char* missoes[] = {
        "Conquistar todos os territorios do mapa.",
        "Eliminar completamente o exercito Vermelho.",
        "Eliminar completamente o exercito Azul.",
        "Manter 5 tropas em 3 territorios diferentes.",
        "Conquistar 4 territorios no total."
    };
    int totalMissoes = 5;

    int totalTerritorios;
    char corJogador[10];

    printf("--- WAR ESTRUTURADO (NIVEL MESTRE) ---\n");
    printf("Qual a sua cor? ");
    scanf("%s", corJogador);
    printf("Quantos territorios existem no mapa? ");
    scanf("%d", &totalTerritorios);
    limparBufferEntrada(); // Limpa o buffer após ler um número

    // Alocação de memória para o mapa e para a missão do jogador.
    struct Territorio* mapa = (struct Territorio*)calloc(totalTerritorios, sizeof(struct Territorio));
    char* missaoJogador = (char*)malloc(100 * sizeof(char));

    if (mapa == NULL || missaoJogador == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Atribui uma missão aleatória ao jogador
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    cadastrarTerritorios(mapa, totalTerritorios);
    exibirMissao(missaoJogador);

    int opcao = 0;
    while (opcao != 2) {
        exibirTerritorios(mapa, totalTerritorios);

        // Verifica a condição de vitória no início de cada turno
        if (verificarMissao(missaoJogador, mapa, totalTerritorios, corJogador)) {
            printf("\n\n*** PARABENS, JOGADOR %s! VOCE CUMPRIU SUA MISSAO E VENCEU O JOGO! ***\n", corJogador);
            break;
        }

        printf("\nOpcoes:\n1. Atacar\n2. Sair\nEscolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada(); // Limpa o buffer após ler a opção

        if (opcao == 1) {
            int idxAtacante, idxDefensor;
            printf("\nEscolha o territorio ATACANTE (pelo numero): ");
            scanf("%d", &idxAtacante);
            limparBufferEntrada();

            printf("Escolha o territorio DEFENSOR (pelo numero): ");
            scanf("%d", &idxDefensor);
            limparBufferEntrada();

            idxAtacante--;
            idxDefensor--;

            if (idxAtacante < 0 || idxAtacante >= totalTerritorios || idxDefensor < 0 || idxDefensor >= totalTerritorios) {
                printf("\nERRO: Territorio invalido!\n");
            }
            else if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
                printf("\nERRO: Voce nao pode atacar sua propria cor!\n");
            }
            else if (mapa[idxAtacante].tropas <= 1) {
                printf("\nERRO: O atacante precisa de mais de 1 tropa!\n");
            }
            else {
                atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
            }

            printf("\nPressione Enter para continuar...");
            getchar(); // Espera por uma tecla, agora de forma segura.
        }
    }

    liberarMemoria(mapa, missaoJogador); // Libera a memória alocada
    printf("\nJogo finalizado.\n");
    return 0;
}

// Função para limpar o buffer de entrada (evita bugs com scanf e getchar).
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Sorteia e copia uma missão para o jogador.
void atribuirMissao(char* destinoMissao, char* missoes[], int totalMissoes) {
    int indiceSorteado = rand() % totalMissoes;
    strcpy(destinoMissao, missoes[indiceSorteado]);
}

// Exibe a missão do jogador no início do jogo.
void exibirMissao(char* missao) {
    printf("\n================ SUA MISSAO SECRETA ================\n");
    printf("  %s\n", missao);
    printf("==================================================\n");
}

// Verifica se a missão do jogador foi concluída.
int verificarMissao(char* missao, struct Territorio* mapa, int totalTerritorios, char* corJogador) {
    if (strcmp(missao, "Conquistar todos os territorios do mapa.") == 0) {
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) != 0) {
                return 0; // Missão não cumprida se encontrar outra cor.
            }
        }
        return 1; // Missão cumprida se todas as cores forem do jogador.
    }

    if (strcmp(missao, "Eliminar completamente o exercito Vermelho.") == 0) {
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                return 0; // Missão não cumprida se ainda existir um território Vermelho.
            }
        }
        return 1; // Missão cumprida se não houver mais territórios Vermelhos.
    }

    if (strcmp(missao, "Eliminar completamente o exercito Azul.") == 0) {
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0) {
                return 0;
            }
        }
        return 1;
    }

    if (strcmp(missao, "Manter 5 tropas em 3 territorios diferentes.") == 0) {
        int contagem = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 5) {
                contagem++;
            }
        }
        if (contagem >= 3) return 1;
    }

    if (strcmp(missao, "Conquistar 4 territorios no total.") == 0) {
        int contagem = 0;
        for (int i = 0; i < totalTerritorios; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contagem++;
            }
        }
        if (contagem >= 4) return 1;
    }

    // Se nenhuma missão foi cumprida, retorna 0.
    return 0;
}


// Libera toda a memória alocada dinamicamente.
void liberarMemoria(struct Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}


// Cadastra os dados iniciais dos territórios.
void cadastrarTerritorios(struct Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n--- Dados do Territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);
        limparBufferEntrada();

        printf("Cor: ");
        scanf("%s", mapa[i].cor);
        limparBufferEntrada();

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        limparBufferEntrada();
    }
}

// Exibe o estado atual de todos os territórios no mapa.
void exibirTerritorios(struct Territorio* mapa, int total) {
    printf("\n\n------------------- MAPA ATUAL -------------------\n");
    for (int i = 0; i < total; i++) {
        printf(" %d. %-15s | Cor: %-10s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("--------------------------------------------------\n");
}

// Simula um ataque entre dois territórios, atualizando as tropas e a posse.
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\n--- BATALHA: %s vs %s ---\n", atacante->nome, defensor->nome);
    printf("Dado de Ataque: %d\nDado de Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("\nVITORIA! %s conquistou %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);

        // O atacante move metade das suas tropas, mas sempre deixa ao menos uma para trás.
        int tropasMovidas = atacante->tropas / 2;
        if (tropasMovidas == 0) {
            tropasMovidas = 1;
        }

        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;

    }
    else {
        printf("\nDERROTA! O ataque de %s falhou.\n", atacante->nome);
        // O atacante perde uma tropa se tiver mais de uma.
        if (atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
}