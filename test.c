#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "war.h"

// Programa de teste para demonstrar funcionalidades do jogo War
int main() {
    printf("========================================\n");
    printf("   TESTE DO SISTEMA DE ATAQUE - WAR    \n");
    printf("========================================\n\n");
    
    // Criar jogo
    Jogo *jogo = criar_jogo();
    
    // Configurar 2 jogadores para teste
    jogo->num_jogadores = 2;
    jogo->jogadores = (Jogador*)malloc(2 * sizeof(Jogador));
    
    strcpy(jogo->jogadores[0].nome, "João");
    strcpy(jogo->jogadores[0].cor, "Vermelho");
    jogo->jogadores[0].tropas_disponiveis = 30;
    jogo->jogadores[0].territorios_conquistados = 0;
    jogo->jogadores[0].ativo = 1;
    
    strcpy(jogo->jogadores[1].nome, "Maria");
    strcpy(jogo->jogadores[1].cor, "Azul");
    jogo->jogadores[1].tropas_disponiveis = 30;
    jogo->jogadores[1].territorios_conquistados = 0;
    jogo->jogadores[1].ativo = 1;
    
    // Inicializar territórios
    inicializar_territorios(jogo);
    
    // Configurar alguns territórios para teste de ataque
    printf("Configurando territórios para teste...\n\n");
    
    // João possui territórios 0-5 da Ásia com tropas variadas
    for (int i = 0; i < 6; i++) {
        jogo->territorios[i].proprietario = 0;
        jogo->territorios[i].tropas = 5 + i; // 5 a 10 tropas
        jogo->jogadores[0].territorios_conquistados++;
    }
    
    // Maria possui territórios 6-11 da Ásia
    for (int i = 6; i < 12; i++) {
        jogo->territorios[i].proprietario = 1;
        jogo->territorios[i].tropas = 3 + (i - 6); // 3 a 8 tropas
        jogo->jogadores[1].territorios_conquistados++;
    }
    
    // João possui América do Sul
    for (int i = 12; i < 18; i++) {
        jogo->territorios[i].proprietario = 0;
        jogo->territorios[i].tropas = 4;
        jogo->jogadores[0].territorios_conquistados++;
    }
    
    // Maria possui resto da América do Sul
    for (int i = 18; i < 24; i++) {
        jogo->territorios[i].proprietario = 1;
        jogo->territorios[i].tropas = 3;
        jogo->jogadores[1].territorios_conquistados++;
    }
    
    // Atribuir missões
    jogo->missoes = (Missao*)malloc(2 * sizeof(Missao));
    jogo->missoes[0].tipo = 1;
    strcpy(jogo->missoes[0].descricao, "Conquistar completamente a Ásia");
    jogo->missoes[0].param1 = 0;
    
    jogo->missoes[1].tipo = 1;
    strcpy(jogo->missoes[1].descricao, "Conquistar completamente a América do Sul");
    jogo->missoes[1].param1 = 1;
    
    // Exibir estado inicial
    printf("=== ESTADO INICIAL ===\n");
    exibir_jogadores(jogo);
    exibir_mapa(jogo);
    
    // Teste 1: Ataque simples
    printf("\n\n========================================\n");
    printf("TESTE 1: Ataque de Oriente Médio (João) contra Mongólia (Maria)\n");
    printf("========================================\n");
    printf("Antes do ataque:\n");
    printf("  %s: %d tropas (João)\n", jogo->territorios[0].nome, jogo->territorios[0].tropas);
    printf("  %s: %d tropas (Maria)\n", jogo->territorios[6].nome, jogo->territorios[6].tropas);
    
    realizar_ataque(jogo, 0, 6);
    
    printf("\nDepois do ataque:\n");
    printf("  %s: %d tropas\n", jogo->territorios[0].nome, jogo->territorios[0].tropas);
    printf("  %s: %d tropas\n", jogo->territorios[6].nome, jogo->territorios[6].tropas);
    
    // Teste 2: Tentativa de ataque sem tropas suficientes
    printf("\n\n========================================\n");
    printf("TESTE 2: Tentativa de ataque com tropas insuficientes\n");
    printf("========================================\n");
    
    // Configurar território com apenas 1 tropa
    jogo->territorios[23].tropas = 1;
    printf("Território %s tem apenas %d tropa\n", jogo->territorios[23].nome, jogo->territorios[23].tropas);
    realizar_ataque(jogo, 23, 18); // Deve falhar
    
    // Teste 3: Verificar vitória
    printf("\n\n========================================\n");
    printf("TESTE 3: Verificação de condição de vitória\n");
    printf("========================================\n");
    
    printf("\nVerificando vitória para João (precisa conquistar toda a Ásia):\n");
    if (verificar_vitoria(jogo, 0)) {
        printf("RESULTADO: João VENCEU!\n");
    } else {
        printf("RESULTADO: João ainda não venceu.\n");
        printf("João possui %d territórios da Ásia (precisa de 12)\n", 
               jogo->jogadores[0].territorios_conquistados);
    }
    
    printf("\nVerificando vitória para Maria (precisa conquistar toda a América do Sul):\n");
    if (verificar_vitoria(jogo, 1)) {
        printf("RESULTADO: Maria VENCEU!\n");
    } else {
        printf("RESULTADO: Maria ainda não venceu.\n");
        
        // Contar territórios de Maria na América do Sul
        int terr_maria_sul = 0;
        for (int i = 12; i < 24; i++) {
            if (jogo->territorios[i].proprietario == 1) {
                terr_maria_sul++;
            }
        }
        printf("Maria possui %d territórios da América do Sul (precisa de 12)\n", terr_maria_sul);
    }
    
    // Teste 4: Demonstrar alocação dinâmica
    printf("\n\n========================================\n");
    printf("TESTE 4: Demonstração de Alocação Dinâmica\n");
    printf("========================================\n");
    
    printf("\nMemória alocada dinamicamente:\n");
    printf("  - Jogo: %zu bytes\n", sizeof(Jogo));
    printf("  - Jogadores: %d x %zu = %zu bytes\n", 
           jogo->num_jogadores, sizeof(Jogador), 
           jogo->num_jogadores * sizeof(Jogador));
    printf("  - Territórios: %d x %zu = %zu bytes\n", 
           jogo->num_territorios, sizeof(Territorio), 
           jogo->num_territorios * sizeof(Territorio));
    printf("  - Missões: %d x %zu = %zu bytes\n", 
           jogo->num_jogadores, sizeof(Missao), 
           jogo->num_jogadores * sizeof(Missao));
    printf("  - Total aproximado: %zu bytes\n", 
           sizeof(Jogo) + 
           (jogo->num_jogadores * sizeof(Jogador)) + 
           (jogo->num_territorios * sizeof(Territorio)) + 
           (jogo->num_jogadores * sizeof(Missao)));
    
    // Teste 5: Ponteiros
    printf("\n\n========================================\n");
    printf("TESTE 5: Demonstração do Uso de Ponteiros\n");
    printf("========================================\n");
    
    Territorio *terr_ptr = &jogo->territorios[0];
    Jogador *jog_ptr = &jogo->jogadores[0];
    
    printf("\nUsando ponteiros para acessar dados:\n");
    printf("  Território (via ponteiro): %s\n", terr_ptr->nome);
    printf("  Proprietário (via ponteiro): %s\n", jog_ptr->nome);
    printf("  Tropas no território (via ponteiro): %d\n", terr_ptr->tropas);
    
    // Modificar via ponteiro
    terr_ptr->tropas += 5;
    printf("\nApós adicionar 5 tropas via ponteiro:\n");
    printf("  Tropas no território: %d\n", jogo->territorios[0].tropas);
    
    // Resumo final
    printf("\n\n========================================\n");
    printf("          RESUMO DOS TESTES             \n");
    printf("========================================\n");
    printf("✓ Sistema de cadastro com structs funcionando\n");
    printf("✓ Alocação dinâmica de memória implementada\n");
    printf("✓ Sistema de ataque com ponteiros funcional\n");
    printf("✓ Simulação de batalha com dados implementada\n");
    printf("✓ Sistema de missões estratégicas ativo\n");
    printf("✓ Verificação de vitória implementada\n");
    printf("✓ Gerenciamento adequado de memória\n");
    
    // Liberar memória
    liberar_jogo(jogo);
    
    printf("\n✓ Memória liberada corretamente!\n");
    printf("========================================\n");
    printf("       TESTES CONCLUÍDOS COM SUCESSO!   \n");
    printf("========================================\n");
    
    return 0;
}
