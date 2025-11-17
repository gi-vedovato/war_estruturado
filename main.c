#include <stdio.h>
#include <stdlib.h>
#include "war.h"

void exibir_menu() {
    printf("\n========== JOGO WAR ==========\n");
    printf("1. Exibir Mapa\n");
    printf("2. Exibir Jogadores\n");
    printf("3. Realizar Ataque\n");
    printf("4. Verificar Vitória\n");
    printf("5. Exibir Missões\n");
    printf("0. Sair\n");
    printf("==============================\n");
    printf("Escolha uma opção: ");
}

int main() {
    printf("========================================\n");
    printf("       BEM-VINDO AO JOGO WAR!           \n");
    printf("========================================\n");
    printf("Sistema estratégico de conquista de territórios\n");
    printf("Foco: Ásia e América do Sul\n");
    printf("========================================\n\n");
    
    // Criar jogo com alocação dinâmica
    Jogo *jogo = criar_jogo();
    
    // Inicializar territórios
    inicializar_territorios(jogo);
    
    // Cadastrar jogadores
    cadastrar_jogadores(jogo);
    
    // Distribuir territórios
    distribuir_territorios(jogo);
    
    // Distribuir tropas iniciais
    distribuir_tropas_iniciais(jogo);
    
    // Atribuir missões
    atribuir_missoes(jogo);
    
    // Loop principal do jogo
    int opcao;
    int jogo_ativo = 1;
    
    while (jogo_ativo) {
        exibir_menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: // Exibir Mapa
                exibir_mapa(jogo);
                break;
                
            case 2: // Exibir Jogadores
                exibir_jogadores(jogo);
                break;
                
            case 3: { // Realizar Ataque
                printf("\n=== REALIZAR ATAQUE ===\n");
                
                // Listar territórios
                printf("\nTerritórios disponíveis:\n");
                for (int i = 0; i < jogo->num_territorios; i++) {
                    printf("%d. %s (%s) - Tropas: %d", i, 
                           jogo->territorios[i].nome,
                           jogo->territorios[i].continente,
                           jogo->territorios[i].tropas);
                    if (jogo->territorios[i].proprietario >= 0) {
                        printf(" - %s\n", jogo->jogadores[jogo->territorios[i].proprietario].nome);
                    } else {
                        printf(" - Sem proprietário\n");
                    }
                }
                
                int atac, def;
                printf("\nDigite o número do território ATACANTE: ");
                scanf("%d", &atac);
                printf("Digite o número do território DEFENSOR: ");
                scanf("%d", &def);
                
                realizar_ataque(jogo, atac, def);
                break;
            }
            
            case 4: { // Verificar Vitória
                printf("\n=== VERIFICAÇÃO DE VITÓRIA ===\n");
                for (int i = 0; i < jogo->num_jogadores; i++) {
                    if (jogo->jogadores[i].ativo) {
                        printf("\nJogador: %s\n", jogo->jogadores[i].nome);
                        exibir_missao(&jogo->missoes[i]);
                        
                        if (verificar_vitoria(jogo, i)) {
                            printf("\n*** VITÓRIA! ***\n");
                            printf("O jogador %s completou sua missão!\n", jogo->jogadores[i].nome);
                            printf("\n========================================\n");
                            printf("          FIM DE JOGO!                  \n");
                            printf("========================================\n");
                            jogo_ativo = 0;
                            break;
                        } else {
                            printf("Status: Missão ainda não concluída.\n");
                        }
                    }
                }
                break;
            }
            
            case 5: { // Exibir Missões
                printf("\n=== MISSÕES DOS JOGADORES ===\n");
                for (int i = 0; i < jogo->num_jogadores; i++) {
                    if (jogo->jogadores[i].ativo) {
                        printf("\nJogador: %s (%s)\n", 
                               jogo->jogadores[i].nome, 
                               jogo->jogadores[i].cor);
                        exibir_missao(&jogo->missoes[i]);
                    }
                }
                break;
            }
            
            case 0: // Sair
                printf("\nEncerrando o jogo...\n");
                jogo_ativo = 0;
                break;
                
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    }
    
    // Liberar memória alocada
    liberar_jogo(jogo);
    
    printf("\nObrigado por jogar!\n");
    printf("========================================\n");
    
    return 0;
}
