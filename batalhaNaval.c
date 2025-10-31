#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

// Protótipos de Funções (Para evitar erro de declaração implícita)
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Criação das Matrizes de Habilidade
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3


// Criação das Matrizes de Habilidade

#define TAMANHO_HABILIDADE 5 // Matrizes 5x5
#define HABILIDADE 5

/**
 * Cria a matriz de habilidade em formato de Cone (apontando para baixo).
 * @param matriz A matriz de habilidade 5x5.
 */
void criar_cone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Lógica do Cone: A área afetada (1) se expande para baixo.
            // O centro do cone está em (0, 2).
            // A largura do cone na linha 'i' é 2*i + 1.
            int centro = TAMANHO_HABILIDADE / 2;
            int inicio = centro - i;
            int fim = centro + i;
            
            if (i >= 0 && i < TAMANHO_HABILIDADE && j >= inicio && j <= fim) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * Cria a matriz de habilidade em formato de Cruz.
 * @param matriz A matriz de habilidade 5x5.
 */
void criar_cruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Lógica da Cruz: A área afetada (1) está na linha central ou na coluna central.
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * Cria a matriz de habilidade em formato de Octaedro (Losango).
 * @param matriz A matriz de habilidade 5x5.
 */
void criar_octaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Lógica do Octaedro (Losango): |i - centro| + |j - centro| <= centro
            int dist_i = abs(i - centro);
            int dist_j = abs(j - centro);
            
            if (dist_i + dist_j <= centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Posicionamento de 4 Navios (Incluindo Diagonais)

/**
 * Tenta posicionar um navio no tabuleiro, incluindo diagonais.
 * @param tabuleiro A matriz 10x10.
 * @param linha_inicial Linha de início do navio.
 * @param coluna_inicial Coluna de início do navio.
 * @param orientacao 0: Horizontal, 1: Vertical, 2: Diagonal Principal (L+, C+), 3: Diagonal Secundária (L+, C-)
 * @return 1 se o posicionamento foi bem-sucedido, 0 caso contrário.
 */
int posicionar_navio_intermediario(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int orientacao) {
    
    // 1. Validação de Limites e Sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linha_inicial;
        int coluna = coluna_inicial;
        
        if (orientacao == 0) { // Horizontal
            coluna += i;
        } else if (orientacao == 1) { // Vertical
            linha += i;
        } else if (orientacao == 2) { // Diagonal Principal (L+, C+)
            linha += i;
            coluna += i;
        } else if (orientacao == 3) { // Diagonal Secundária (L+, C-)
            linha += i;
            coluna -= i;
        }
        
        // Validação de Limites
        if (linha < 0 || linha >= TAMANHO_TABULEIRO || coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
            printf("Erro: Navio fora dos limites do tabuleiro.\n");
            return 0;
        }
        
        // Validação de Sobreposição
        if (tabuleiro[linha][coluna] == NAVIO) {
            printf("Erro: Sobreposição de navios detectada.\n");
            return 0;
        }
    }
    
    // 2. Posicionamento
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linha_inicial;
        int coluna = coluna_inicial;
        
        if (orientacao == 0) { // Horizontal
            coluna += i;
        } else if (orientacao == 1) { // Vertical
            linha += i;
        } else if (orientacao == 2) { // Diagonal Principal (L+, C+)
            linha += i;
            coluna += i;
        } else if (orientacao == 3) { // Diagonal Secundária (L+, C-)
            linha += i;
            coluna -= i;
        }
        
        tabuleiro[linha][coluna] = NAVIO;
    }
    
    return 1;
}

void nivel_intermediario(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("========================================================\n");
    printf("           BATALHA NAVAL - NÍVEL INTERMEDIÁRIO\n");
    printf("========================================================\n");
    
    // Inicializa o tabuleiro
    inicializar_tabuleiro(tabuleiro);
    
    // Coordenadas definidas no código (Requisito)
    // Navio 1: Horizontal
    int linha_h = 0;
    int coluna_h = 0;
    // Navio 2: Vertical
    int linha_v = 4;
    int coluna_v = 9;
    // Navio 3: Diagonal Principal (L+, C+)
    int linha_dp = 7;
    int coluna_dp = 0;
    // Navio 4: Diagonal Secundária (L+, C-)
    int linha_ds = 0;
    int coluna_ds = 7;
    
    // Navio Horizontal
    if (posicionar_navio_intermediario(tabuleiro, linha_h, coluna_h, 0)) {
        printf("Navio Horizontal posicionado em (%d, %d) com sucesso.\n", linha_h, coluna_h);
    }
    
    // Navio Vertical
    if (posicionar_navio_intermediario(tabuleiro, linha_v, coluna_v, 1)) {
        printf("Navio Vertical posicionado em (%d, %d) com sucesso.\n", linha_v, coluna_v);
    }
    
    // Navio Diagonal Principal
    if (posicionar_navio_intermediario(tabuleiro, linha_dp, coluna_dp, 2)) {
        printf("Navio Diagonal Principal posicionado em (%d, %d) com sucesso.\n", linha_dp, coluna_dp);
    }
    
    // Navio Diagonal Secundária
    if (posicionar_navio_intermediario(tabuleiro, linha_ds, coluna_ds, 3)) {
        printf("Navio Diagonal Secundária posicionado em (%d, %d) com sucesso.\n", linha_ds, coluna_ds);
    }
    
    printf("\nTabuleiro com 4 Navios (Incluindo Diagonais):\n");
    exibir_tabuleiro(tabuleiro);
    printf("\n");
}

// Sobreposição das Habilidades no Tabuleiro

/**
 * Sobrepõe a matriz de habilidade ao tabuleiro.
 * @param tabuleiro O tabuleiro 10x10.
 * @param matriz_habilidade A matriz de habilidade 5x5 (0 ou 1).
 * @param linha_origem Linha central da habilidade no tabuleiro.
 * @param coluna_origem Coluna central da habilidade no tabuleiro.
 */
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int linha_origem, int coluna_origem) {
    int offset = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (matriz_habilidade[i][j] == 1) {
                int linha_tabuleiro = linha_origem + (i - offset);
                int coluna_tabuleiro = coluna_origem + (j - offset);
                
                // Condicional para garantir que a área de efeito permaneça dentro dos limites do tabuleiro
                if (linha_tabuleiro >= 0 && linha_tabuleiro < TAMANHO_TABULEIRO &&
                    coluna_tabuleiro >= 0 && coluna_tabuleiro < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição como afetada pela habilidade (5), mas não sobrescreve navios (3)
                    if (tabuleiro[linha_tabuleiro][coluna_tabuleiro] != NAVIO) {
                        tabuleiro[linha_tabuleiro][coluna_tabuleiro] = HABILIDADE;
                    }
                }
            }
        }
    }
}

void nivel_mestre(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("========================================================\n");
    printf("           BATALHA NAVAL - NÍVEL MESTRE\n");
    printf("========================================================\n");
    
    // Inicializa o tabuleiro com os navios
    nivel_intermediario(tabuleiro);
    
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    // Criação das Matrizes de Habilidade
    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octaedro);
    
    // Sobreposição das Habilidades (Coordenadas definidas no código)
    
    // Habilidade 1: Cone (Origem: 5, 5)
    sobrepor_habilidade(tabuleiro, cone, 5, 5);
    printf("Habilidade Cone (Origem: 5, 5) aplicada.\n");
    
    // Habilidade 2: Cruz (Origem: 2, 2)
    sobrepor_habilidade(tabuleiro, cruz, 2, 2);
    printf("Habilidade Cruz (Origem: 2, 2) aplicada.\n");
    
    // Habilidade 3: Octaedro (Origem: 8, 8)
    sobrepor_habilidade(tabuleiro, octaedro, 8, 8);
    printf("Habilidade Octaedro (Origem: 8, 8) aplicada.\n");
    
    printf("\nTabuleiro com Navios e Áreas de Efeito (5):\n");
    exibir_tabuleiro(tabuleiro);
    printf("\n");
}

// Tabuleiro 10x10 e Posicionamento de 2 Navios

/**
 * Inicializa o tabuleiro com água (0).
 * @param tabuleiro A matriz 10x10.
 */
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * Exibe o tabuleiro no console.
 * @param tabuleiro A matriz 10x10.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

/**
 * Tenta posicionar um navio no tabuleiro.
 * @param tabuleiro A matriz 10x10.
 * @param linha_inicial Linha de início do navio.
 * @param coluna_inicial Coluna de início do navio.
 * @param orientacao 0 para Horizontal, 1 para Vertical.
 * @return 1 se o posicionamento foi bem-sucedido, 0 caso contrário.
 */

void nivel_basico(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("========================================================\n");
    printf("           BATALHA NAVAL - NÍVEL BÁSICO\n");
    printf("========================================================\n");
    
    // Coordenadas definidas no código (Requisito)
    int linha_h = 1;
    int coluna_h = 1;
    int linha_v = 5;
    int coluna_v = 5;
    
    // Navio Horizontal
    if (posicionar_navio_intermediario(tabuleiro, linha_h, coluna_h, 0)) {
        printf("Navio Horizontal posicionado em (%d, %d) com sucesso.\n", linha_h, coluna_h);
    }
    
    // Navio Vertical
    if (posicionar_navio_intermediario(tabuleiro, linha_v, coluna_v, 1)) {
        printf("Navio Vertical posicionado em (%d, %d) com sucesso.\n", linha_v, coluna_v);
    }
    
    printf("\nTabuleiro com Navios Básicos:\n");
    exibir_tabuleiro(tabuleiro);
    printf("\n");
}
// FUNÇÃO PRINCIPAL

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    inicializar_tabuleiro(tabuleiro);  
    nivel_mestre(tabuleiro);
    
    return 0;
}
