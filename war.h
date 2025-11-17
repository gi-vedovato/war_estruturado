#ifndef WAR_H
#define WAR_H

#define MAX_JOGADORES 6
#define MAX_TERRITORIOS 42
#define MAX_NOME 50
#define MAX_COR 20
#define MAX_MISSOES 3

// Estrutura de Território
typedef struct {
    char nome[MAX_NOME];
    char continente[MAX_NOME];
    int tropas;
    int proprietario; // índice do jogador (-1 se não pertence a ninguém)
} Territorio;

// Estrutura de Jogador
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas_disponiveis;
    int territorios_conquistados;
    int ativo;
} Jogador;

// Estrutura de Missão
typedef struct {
    int id;
    char descricao[200];
    int tipo; // 1: conquistar continentes, 2: conquistar territórios, 3: eliminar jogador
    int param1; // número de territórios ou índice do jogador
    int param2; // complemento (ex: continente específico)
} Missao;

// Estrutura do Jogo
typedef struct {
    Jogador *jogadores;
    int num_jogadores;
    Territorio *territorios;
    int num_territorios;
    Missao *missoes;
    int rodada;
} Jogo;

// Funções de inicialização
Jogo* criar_jogo();
void liberar_jogo(Jogo *jogo);
void inicializar_territorios(Jogo *jogo);
void cadastrar_jogadores(Jogo *jogo);

// Funções de jogo
void distribuir_territorios(Jogo *jogo);
void distribuir_tropas_iniciais(Jogo *jogo);
int realizar_ataque(Jogo *jogo, int territorio_atacante, int territorio_defensor);
int verificar_vitoria(Jogo *jogo, int jogador_idx);
void atribuir_missoes(Jogo *jogo);

// Funções auxiliares
void exibir_mapa(Jogo *jogo);
void exibir_jogadores(Jogo *jogo);
int lancar_dado();
void exibir_missao(Missao *missao);

#endif
