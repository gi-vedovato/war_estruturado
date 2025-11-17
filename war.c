#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "war.h"

// Função para criar o jogo com alocação dinâmica
Jogo* criar_jogo() {
    Jogo *jogo = (Jogo*)malloc(sizeof(Jogo));
    if (jogo == NULL) {
        printf("Erro ao alocar memória para o jogo!\n");
        exit(1);
    }
    
    jogo->num_jogadores = 0;
    jogo->num_territorios = 0;
    jogo->rodada = 1;
    jogo->jogadores = NULL;
    jogo->territorios = NULL;
    jogo->missoes = NULL;
    
    srand(time(NULL));
    
    return jogo;
}

// Função para liberar memória do jogo
void liberar_jogo(Jogo *jogo) {
    if (jogo != NULL) {
        if (jogo->jogadores != NULL) {
            free(jogo->jogadores);
        }
        if (jogo->territorios != NULL) {
            free(jogo->territorios);
        }
        if (jogo->missoes != NULL) {
            free(jogo->missoes);
        }
        free(jogo);
    }
}

// Função para inicializar territórios (foco em Ásia e América do Sul)
void inicializar_territorios(Jogo *jogo) {
    jogo->num_territorios = 24; // 12 da Ásia + 12 da América do Sul
    jogo->territorios = (Territorio*)malloc(jogo->num_territorios * sizeof(Territorio));
    
    if (jogo->territorios == NULL) {
        printf("Erro ao alocar memória para territórios!\n");
        exit(1);
    }
    
    // Territórios da Ásia
    strcpy(jogo->territorios[0].nome, "Oriente Médio");
    strcpy(jogo->territorios[0].continente, "Ásia");
    strcpy(jogo->territorios[1].nome, "Aral");
    strcpy(jogo->territorios[1].continente, "Ásia");
    strcpy(jogo->territorios[2].nome, "Omsk");
    strcpy(jogo->territorios[2].continente, "Ásia");
    strcpy(jogo->territorios[3].nome, "Dudinka");
    strcpy(jogo->territorios[3].continente, "Ásia");
    strcpy(jogo->territorios[4].nome, "Sibéria");
    strcpy(jogo->territorios[4].continente, "Ásia");
    strcpy(jogo->territorios[5].nome, "Tchita");
    strcpy(jogo->territorios[5].continente, "Ásia");
    strcpy(jogo->territorios[6].nome, "Mongólia");
    strcpy(jogo->territorios[6].continente, "Ásia");
    strcpy(jogo->territorios[7].nome, "Vladivostok");
    strcpy(jogo->territorios[7].continente, "Ásia");
    strcpy(jogo->territorios[8].nome, "China");
    strcpy(jogo->territorios[8].continente, "Ásia");
    strcpy(jogo->territorios[9].nome, "Índia");
    strcpy(jogo->territorios[9].continente, "Ásia");
    strcpy(jogo->territorios[10].nome, "Japão");
    strcpy(jogo->territorios[10].continente, "Ásia");
    strcpy(jogo->territorios[11].nome, "Vietnã");
    strcpy(jogo->territorios[11].continente, "Ásia");
    
    // Territórios da América do Sul
    strcpy(jogo->territorios[12].nome, "Venezuela");
    strcpy(jogo->territorios[12].continente, "América do Sul");
    strcpy(jogo->territorios[13].nome, "Peru");
    strcpy(jogo->territorios[13].continente, "América do Sul");
    strcpy(jogo->territorios[14].nome, "Brasil");
    strcpy(jogo->territorios[14].continente, "América do Sul");
    strcpy(jogo->territorios[15].nome, "Argentina");
    strcpy(jogo->territorios[15].continente, "América do Sul");
    strcpy(jogo->territorios[16].nome, "Colômbia");
    strcpy(jogo->territorios[16].continente, "América do Sul");
    strcpy(jogo->territorios[17].nome, "Equador");
    strcpy(jogo->territorios[17].continente, "América do Sul");
    strcpy(jogo->territorios[18].nome, "Chile");
    strcpy(jogo->territorios[18].continente, "América do Sul");
    strcpy(jogo->territorios[19].nome, "Uruguai");
    strcpy(jogo->territorios[19].continente, "América do Sul");
    strcpy(jogo->territorios[20].nome, "Bolívia");
    strcpy(jogo->territorios[20].continente, "América do Sul");
    strcpy(jogo->territorios[21].nome, "Paraguai");
    strcpy(jogo->territorios[21].continente, "América do Sul");
    strcpy(jogo->territorios[22].nome, "Guiana");
    strcpy(jogo->territorios[22].continente, "América do Sul");
    strcpy(jogo->territorios[23].nome, "Suriname");
    strcpy(jogo->territorios[23].continente, "América do Sul");
    
    // Inicializar todos os territórios sem proprietário e sem tropas
    for (int i = 0; i < jogo->num_territorios; i++) {
        jogo->territorios[i].tropas = 0;
        jogo->territorios[i].proprietario = -1;
    }
    
    printf("Territórios inicializados: %d\n", jogo->num_territorios);
}

// Função para cadastrar jogadores
void cadastrar_jogadores(Jogo *jogo) {
    printf("\n=== CADASTRO DE JOGADORES ===\n");
    printf("Quantos jogadores irão participar? (2-%d): ", MAX_JOGADORES);
    scanf("%d", &jogo->num_jogadores);
    
    if (jogo->num_jogadores < 2 || jogo->num_jogadores > MAX_JOGADORES) {
        printf("Número inválido! Definindo para 2 jogadores.\n");
        jogo->num_jogadores = 2;
    }
    
    // Alocar memória para jogadores
    jogo->jogadores = (Jogador*)malloc(jogo->num_jogadores * sizeof(Jogador));
    if (jogo->jogadores == NULL) {
        printf("Erro ao alocar memória para jogadores!\n");
        exit(1);
    }
    
    // Cadastrar cada jogador
    for (int i = 0; i < jogo->num_jogadores; i++) {
        printf("\n--- Jogador %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", jogo->jogadores[i].nome);
        printf("Cor: ");
        scanf(" %[^\n]", jogo->jogadores[i].cor);
        
        jogo->jogadores[i].tropas_disponiveis = 0;
        jogo->jogadores[i].territorios_conquistados = 0;
        jogo->jogadores[i].ativo = 1;
    }
    
    printf("\nJogadores cadastrados com sucesso!\n");
}

// Função para distribuir territórios entre jogadores
void distribuir_territorios(Jogo *jogo) {
    printf("\n=== DISTRIBUINDO TERRITÓRIOS ===\n");
    
    int territorios_por_jogador = jogo->num_territorios / jogo->num_jogadores;
    int territorios_restantes = jogo->num_territorios % jogo->num_jogadores;
    
    int territorio_idx = 0;
    
    // Distribuir territórios equitativamente
    for (int j = 0; j < jogo->num_jogadores; j++) {
        int territorios_para_este_jogador = territorios_por_jogador;
        if (j < territorios_restantes) {
            territorios_para_este_jogador++;
        }
        
        for (int t = 0; t < territorios_para_este_jogador; t++) {
            jogo->territorios[territorio_idx].proprietario = j;
            jogo->territorios[territorio_idx].tropas = 1; // 1 tropa inicial
            jogo->jogadores[j].territorios_conquistados++;
            territorio_idx++;
        }
    }
    
    printf("Territórios distribuídos!\n");
}

// Função para distribuir tropas iniciais
void distribuir_tropas_iniciais(Jogo *jogo) {
    int tropas_iniciais[] = {40, 35, 30, 25, 20, 15}; // baseado no número de jogadores
    int tropas = tropas_iniciais[jogo->num_jogadores - 2];
    
    printf("\n=== DISTRIBUINDO TROPAS INICIAIS ===\n");
    printf("Cada jogador recebe %d tropas.\n", tropas);
    
    for (int i = 0; i < jogo->num_jogadores; i++) {
        jogo->jogadores[i].tropas_disponiveis = tropas;
    }
}

// Função para lançar dado (1-6)
int lancar_dado() {
    return (rand() % 6) + 1;
}

// Função para realizar ataque entre territórios
int realizar_ataque(Jogo *jogo, int territorio_atacante, int territorio_defensor) {
    // Validações
    if (territorio_atacante < 0 || territorio_atacante >= jogo->num_territorios ||
        territorio_defensor < 0 || territorio_defensor >= jogo->num_territorios) {
        printf("Territórios inválidos!\n");
        return 0;
    }
    
    Territorio *atac = &jogo->territorios[territorio_atacante];
    Territorio *def = &jogo->territorios[territorio_defensor];
    
    if (atac->proprietario == def->proprietario) {
        printf("Não pode atacar seu próprio território!\n");
        return 0;
    }
    
    if (atac->tropas <= 1) {
        printf("Não há tropas suficientes para atacar! (mínimo: 2)\n");
        return 0;
    }
    
    printf("\n=== BATALHA ===\n");
    printf("Atacante: %s (%s) - %d tropas\n", atac->nome, 
           jogo->jogadores[atac->proprietario].nome, atac->tropas);
    printf("Defensor: %s (%s) - %d tropas\n", def->nome,
           jogo->jogadores[def->proprietario].nome, def->tropas);
    
    // Determinar número de dados
    int dados_ataque = (atac->tropas >= 4) ? 3 : (atac->tropas >= 3) ? 2 : 1;
    int dados_defesa = (def->tropas >= 2) ? 2 : 1;
    
    // Alocar arrays dinamicamente para os dados
    int *dados_atac = (int*)malloc(dados_ataque * sizeof(int));
    int *dados_def = (int*)malloc(dados_defesa * sizeof(int));
    
    if (dados_atac == NULL || dados_def == NULL) {
        printf("Erro ao alocar memória para dados!\n");
        if (dados_atac) free(dados_atac);
        if (dados_def) free(dados_def);
        return 0;
    }
    
    // Lançar dados
    printf("\nDados do atacante: ");
    for (int i = 0; i < dados_ataque; i++) {
        dados_atac[i] = lancar_dado();
        printf("%d ", dados_atac[i]);
    }
    
    printf("\nDados do defensor: ");
    for (int i = 0; i < dados_defesa; i++) {
        dados_def[i] = lancar_dado();
        printf("%d ", dados_def[i]);
    }
    printf("\n");
    
    // Ordenar dados em ordem decrescente
    for (int i = 0; i < dados_ataque - 1; i++) {
        for (int j = i + 1; j < dados_ataque; j++) {
            if (dados_atac[j] > dados_atac[i]) {
                int temp = dados_atac[i];
                dados_atac[i] = dados_atac[j];
                dados_atac[j] = temp;
            }
        }
    }
    
    for (int i = 0; i < dados_defesa - 1; i++) {
        for (int j = i + 1; j < dados_defesa; j++) {
            if (dados_def[j] > dados_def[i]) {
                int temp = dados_def[i];
                dados_def[i] = dados_def[j];
                dados_def[j] = temp;
            }
        }
    }
    
    // Comparar dados
    int comparacoes = (dados_ataque < dados_defesa) ? dados_ataque : dados_defesa;
    int perdas_atac = 0, perdas_def = 0;
    
    for (int i = 0; i < comparacoes; i++) {
        if (dados_atac[i] > dados_def[i]) {
            perdas_def++;
        } else {
            perdas_atac++;
        }
    }
    
    printf("\nResultado: Atacante perde %d tropa(s), Defensor perde %d tropa(s)\n", 
           perdas_atac, perdas_def);
    
    atac->tropas -= perdas_atac;
    def->tropas -= perdas_def;
    
    // Verificar conquista
    int conquistou = 0;
    if (def->tropas == 0) {
        printf("\n*** TERRITÓRIO CONQUISTADO! ***\n");
        int old_owner = def->proprietario;
        def->proprietario = atac->proprietario;
        def->tropas = 1; // Atacante move pelo menos 1 tropa
        atac->tropas--;
        
        jogo->jogadores[atac->proprietario].territorios_conquistados++;
        jogo->jogadores[old_owner].territorios_conquistados--;
        conquistou = 1;
    }
    
    free(dados_atac);
    free(dados_def);
    
    return conquistou;
}

// Função para atribuir missões aos jogadores
void atribuir_missoes(Jogo *jogo) {
    jogo->missoes = (Missao*)malloc(jogo->num_jogadores * sizeof(Missao));
    if (jogo->missoes == NULL) {
        printf("Erro ao alocar memória para missões!\n");
        exit(1);
    }
    
    // Missões estratégicas
    for (int i = 0; i < jogo->num_jogadores; i++) {
        jogo->missoes[i].id = i;
        if (i % 3 == 0) {
            jogo->missoes[i].tipo = 1;
            strcpy(jogo->missoes[i].descricao, "Conquistar completamente a Ásia");
            jogo->missoes[i].param1 = 0;
        } else if (i % 3 == 1) {
            jogo->missoes[i].tipo = 1;
            strcpy(jogo->missoes[i].descricao, "Conquistar completamente a América do Sul");
            jogo->missoes[i].param1 = 1;
        } else {
            jogo->missoes[i].tipo = 2;
            snprintf(jogo->missoes[i].descricao, 200, "Conquistar %d territórios", 18);
            jogo->missoes[i].param1 = 18;
        }
    }
    
    printf("\n=== MISSÕES ATRIBUÍDAS ===\n");
    for (int i = 0; i < jogo->num_jogadores; i++) {
        printf("Jogador %s: %s\n", jogo->jogadores[i].nome, jogo->missoes[i].descricao);
    }
}

// Função para exibir missão
void exibir_missao(Missao *missao) {
    printf("Missão: %s\n", missao->descricao);
}

// Função para verificar vitória
int verificar_vitoria(Jogo *jogo, int jogador_idx) {
    Missao *missao = &jogo->missoes[jogador_idx];
    Jogador *jogador = &jogo->jogadores[jogador_idx];
    
    if (missao->tipo == 1) { // Conquistar continente
        char *continente_alvo;
        if (missao->param1 == 0) {
            continente_alvo = "Ásia";
        } else {
            continente_alvo = "América do Sul";
        }
        
        // Verificar se jogador possui todos os territórios do continente
        int territorios_continente = 0;
        int territorios_jogador = 0;
        
        for (int i = 0; i < jogo->num_territorios; i++) {
            if (strcmp(jogo->territorios[i].continente, continente_alvo) == 0) {
                territorios_continente++;
                if (jogo->territorios[i].proprietario == jogador_idx) {
                    territorios_jogador++;
                }
            }
        }
        
        if (territorios_jogador == territorios_continente) {
            return 1;
        }
    } else if (missao->tipo == 2) { // Conquistar número de territórios
        if (jogador->territorios_conquistados >= missao->param1) {
            return 1;
        }
    }
    
    return 0;
}

// Função para exibir mapa
void exibir_mapa(Jogo *jogo) {
    printf("\n=== MAPA DO JOGO ===\n\n");
    
    printf("--- ÁSIA ---\n");
    for (int i = 0; i < jogo->num_territorios; i++) {
        if (strcmp(jogo->territorios[i].continente, "Ásia") == 0) {
            printf("%-20s | Tropas: %2d | ", jogo->territorios[i].nome, jogo->territorios[i].tropas);
            if (jogo->territorios[i].proprietario >= 0) {
                printf("Proprietário: %s (%s)\n", 
                       jogo->jogadores[jogo->territorios[i].proprietario].nome,
                       jogo->jogadores[jogo->territorios[i].proprietario].cor);
            } else {
                printf("Proprietário: Nenhum\n");
            }
        }
    }
    
    printf("\n--- AMÉRICA DO SUL ---\n");
    for (int i = 0; i < jogo->num_territorios; i++) {
        if (strcmp(jogo->territorios[i].continente, "América do Sul") == 0) {
            printf("%-20s | Tropas: %2d | ", jogo->territorios[i].nome, jogo->territorios[i].tropas);
            if (jogo->territorios[i].proprietario >= 0) {
                printf("Proprietário: %s (%s)\n", 
                       jogo->jogadores[jogo->territorios[i].proprietario].nome,
                       jogo->jogadores[jogo->territorios[i].proprietario].cor);
            } else {
                printf("Proprietário: Nenhum\n");
            }
        }
    }
}

// Função para exibir jogadores
void exibir_jogadores(Jogo *jogo) {
    printf("\n=== JOGADORES ===\n");
    for (int i = 0; i < jogo->num_jogadores; i++) {
        if (jogo->jogadores[i].ativo) {
            printf("Jogador %d: %s (%s)\n", i + 1, 
                   jogo->jogadores[i].nome, jogo->jogadores[i].cor);
            printf("  Tropas disponíveis: %d\n", jogo->jogadores[i].tropas_disponiveis);
            printf("  Territórios conquistados: %d\n", jogo->jogadores[i].territorios_conquistados);
        }
    }
}
