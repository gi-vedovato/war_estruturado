# Objetivos Concluídos - Jogo War Estruturado

## ✅ Objetivo 1: Sistema de Cadastro com Structs

**Requisito:** Desenvolver um programa em C que implemente um sistema para cadastro dos dados (nome, cor e tropas) para estruturar as informações básicas do jogo War utilizando um vetor de structs.

**Implementação:**

### Structs Criadas:

1. **Struct Jogador** (`war.h` linha 16-22):
```c
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas_disponiveis;
    int territorios_conquistados;
    int ativo;
} Jogador;
```

2. **Struct Territorio** (`war.h` linha 8-14):
```c
typedef struct {
    char nome[MAX_NOME];
    char continente[MAX_NOME];
    int tropas;
    int proprietario;
} Territorio;
```

3. **Struct Jogo** (`war.h` linha 32-39):
```c
typedef struct {
    Jogador *jogadores;        // Vetor dinâmico de jogadores
    int num_jogadores;
    Territorio *territorios;    // Vetor dinâmico de territórios
    int num_territorios;
    Missao *missoes;
    int rodada;
} Jogo;
```

### Função de Cadastro:

Implementada em `war.c` (linhas 110-146):
- Solicita número de jogadores (2-6)
- Coleta nome e cor de cada jogador
- Aloca memória dinamicamente para o vetor de jogadores
- Inicializa atributos de cada jogador

**Evidência:** Arquivo `war.c`, função `cadastrar_jogadores()`

---

## ✅ Objetivo 2: Sistema de Ataque com Alocação Dinâmica

**Requisito:** Implementar a funcionalidade de ataque entre territórios em linguagem C, utilizando alocação dinâmica e ponteiros, para simular batalhas e aproximação do sistema do comportamento estratégico do jogo real.

**Implementação:**

### Sistema de Ataque:

Implementado em `war.c` (linhas 186-293):

1. **Alocação Dinâmica de Dados:**
```c
int *dados_atac = (int*)malloc(dados_ataque * sizeof(int));
int *dados_def = (int*)malloc(dados_defesa * sizeof(int));
```

2. **Uso de Ponteiros:**
```c
Territorio *atac = &jogo->territorios[territorio_atacante];
Territorio *def = &jogo->territorios[territorio_defensor];
```

3. **Simulação de Batalha:**
- Lançamento de dados aleatórios (1-6)
- Atacante: até 3 dados
- Defensor: até 2 dados
- Comparação ordenada dos resultados
- Cálculo de perdas
- Conquista de território quando defensor perde todas as tropas

4. **Validações:**
- Verificação de tropas suficientes (mínimo 2)
- Impossibilidade de atacar próprio território
- Territórios válidos

**Evidência:** Arquivo `war.c`, função `realizar_ataque()`

### Demonstração no Teste:

```
=== BATALHA ===
Atacante: Oriente Médio (João) - 5 tropas
Defensor: Mongólia (Maria) - 3 tropas

Dados do atacante: 1 2 5 
Dados do defensor: 4 4 

Resultado: Atacante perde 1 tropa(s), Defensor perde 1 tropa(s)
```

---

## ✅ Objetivo 3: Sistema de Missões Estratégicas

**Requisito:** Implementar o sistema de missões estratégicas em linguagem C, utilizando ponteiros e alocação dinâmica, para verificar a condição de vitória e conclusão do desenvolvimento do jogo.

**Implementação:**

### Struct Missão:

Definida em `war.h` (linhas 25-30):
```c
typedef struct {
    int id;
    char descricao[200];
    int tipo;    // 1: conquistar continentes, 2: conquistar territórios
    int param1;  // número de territórios ou continente
    int param2;  // complemento
} Missao;
```

### Atribuição de Missões:

Implementada em `war.c` (linhas 295-322):
- Alocação dinâmica do vetor de missões
- Três tipos de missões:
  1. Conquistar completamente a Ásia
  2. Conquistar completamente a América do Sul
  3. Conquistar 18 territórios

```c
jogo->missoes = (Missao*)malloc(jogo->num_jogadores * sizeof(Missao));
```

### Verificação de Vitória:

Implementada em `war.c` (linhas 330-365):
- Usa ponteiros para acessar missões e jogadores
- Verifica conquista de continentes completos
- Verifica número de territórios conquistados
- Retorna 1 se missão completa, 0 caso contrário

**Uso de Ponteiros:**
```c
Missao *missao = &jogo->missoes[jogador_idx];
Jogador *jogador = &jogo->jogadores[jogador_idx];
```

**Evidência:** Arquivo `war.c`, funções `atribuir_missoes()` e `verificar_vitoria()`

---

## Funcionalidades Adicionais Implementadas

### 1. Territórios
- **24 territórios totais**
  - 12 da Ásia: Oriente Médio, Aral, Omsk, Dudinka, Sibéria, Tchita, Mongólia, Vladivostok, China, Índia, Japão, Vietnã
  - 12 da América do Sul: Venezuela, Peru, Brasil, Argentina, Colômbia, Equador, Chile, Uruguai, Bolívia, Paraguai, Guiana, Suriname

### 2. Gerenciamento de Memória
- Função `criar_jogo()`: Aloca memória para estrutura principal
- Função `liberar_jogo()`: Libera toda memória alocada
- Prevenção de memory leaks

### 3. Interface Interativa
Menu completo com opções:
1. Exibir Mapa
2. Exibir Jogadores
3. Realizar Ataque
4. Verificar Vitória
5. Exibir Missões
0. Sair

### 4. Sistema de Testes
Programa `test.c` que demonstra:
- Todos os objetivos implementados
- Alocação dinâmica em ação
- Uso de ponteiros
- Sistema de batalha
- Verificação de vitória

---

## Evidências de Compilação

### Compilação sem Warnings:
```bash
gcc -Wall -Wextra -std=c99 -c main.c
gcc -Wall -Wextra -std=c99 -c war.c
gcc -Wall -Wextra -std=c99 -o war_game main.o war.o
```

### Verificação de Segurança:
```
CodeQL Analysis: 0 alerts
- cpp: No alerts found.
```

---

## Métricas do Projeto

### Linhas de Código:
- `war.h`: 65 linhas (definições e protótipos)
- `war.c`: 428 linhas (implementação)
- `main.c`: 140 linhas (interface)
- `test.c`: 195 linhas (testes)
- **Total**: 828 linhas de código C

### Estruturas de Dados:
- 4 structs principais
- 3 vetores dinâmicos (jogadores, territórios, missões)
- Múltiplos ponteiros para manipulação eficiente

### Funcionalidades:
- 13+ funções implementadas
- Menu interativo completo
- Sistema de batalha realista
- Verificação de vitória automática
- Gerenciamento completo de memória

---

## Conclusão

✅ **Todos os três objetivos foram completamente implementados:**

1. ✅ Sistema de cadastro com structs e vetores
2. ✅ Sistema de ataque com alocação dinâmica e ponteiros
3. ✅ Sistema de missões com verificação de vitória

O projeto demonstra domínio de:
- Estruturas de dados (structs)
- Alocação dinâmica de memória (malloc/free)
- Ponteiros e referências
- Modularização de código
- Programação estruturada em C

**Status Final: CONCLUÍDO COM SUCESSO** ✅
