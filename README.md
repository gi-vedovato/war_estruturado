# War Estruturado - Jogo de Estratégia em C

## Descrição do Projeto

Sistema interativo do jogo War desenvolvido em linguagem C, implementando estruturas de dados, alocação dinâmica de memória e ponteiros para simular batalhas estratégicas com foco nos continentes da Ásia e América do Sul.

## Objetivos Implementados

### ✅ Objetivo 1: Sistema de Cadastro
- Implementação de structs para armazenar dados de jogadores (nome, cor, tropas)
- Uso de vetores de structs para gerenciar múltiplos jogadores
- Sistema modular e escalável

### ✅ Objetivo 2: Sistema de Ataque
- Funcionalidade completa de ataque entre territórios
- Uso de alocação dinâmica para dados de batalha
- Simulação realista com sistema de dados (1-6)
- Ponteiros para manipulação eficiente de territórios

### ✅ Objetivo 3: Sistema de Missões
- Implementação de missões estratégicas
- Verificação de condições de vitória
- Uso de ponteiros e alocação dinâmica
- Missões: conquistar continentes ou número específico de territórios

## Estrutura do Projeto

```
war_estruturado/
├── war.h           # Cabeçalho com definições de estruturas e protótipos
├── war.c           # Implementação das funções do jogo
├── main.c          # Programa principal com menu interativo
├── Makefile        # Automação de compilação
└── README.md       # Documentação
```

## Estruturas de Dados

### Território
```c
typedef struct {
    char nome[MAX_NOME];
    char continente[MAX_NOME];
    int tropas;
    int proprietario;
} Territorio;
```

### Jogador
```c
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas_disponiveis;
    int territorios_conquistados;
    int ativo;
} Jogador;
```

### Missão
```c
typedef struct {
    int id;
    char descricao[200];
    int tipo;
    int param1;
    int param2;
} Missao;
```

### Jogo
```c
typedef struct {
    Jogador *jogadores;
    int num_jogadores;
    Territorio *territorios;
    int num_territorios;
    Missao *missoes;
    int rodada;
} Jogo;
```

## Funcionalidades

### Gerenciamento de Memória
- Alocação dinâmica com `malloc()` para jogadores, territórios e missões
- Liberação adequada de memória com `free()`
- Uso de ponteiros para manipulação eficiente

### Sistema de Batalha
- Lançamento de dados aleatórios (1-6)
- Comparação de resultados entre atacante e defensor
- Alocação dinâmica de arrays para dados
- Cálculo de perdas e conquista de territórios

### Territórios Implementados

**Ásia (12 territórios):**
- Oriente Médio, Aral, Omsk, Dudinka
- Sibéria, Tchita, Mongólia, Vladivostok
- China, Índia, Japão, Vietnã

**América do Sul (12 territórios):**
- Venezuela, Peru, Brasil, Argentina
- Colômbia, Equador, Chile, Uruguai
- Bolívia, Paraguai, Guiana, Suriname

### Tipos de Missão
1. Conquistar completamente a Ásia
2. Conquistar completamente a América do Sul
3. Conquistar 18 territórios

## Compilação e Execução

### Compilar o projeto
```bash
make
```

### Executar o jogo
```bash
make run
```

ou

```bash
./war_game
```

### Limpar arquivos compilados
```bash
make clean
```

### Recompilar tudo
```bash
make rebuild
```

## Como Jogar

1. **Inicialização**: O jogo solicita o número de jogadores (2-6)
2. **Cadastro**: Cada jogador informa nome e cor
3. **Distribuição**: Territórios são distribuídos automaticamente
4. **Menu Principal**: Opções disponíveis:
   - `1` - Exibir Mapa
   - `2` - Exibir Jogadores
   - `3` - Realizar Ataque
   - `4` - Verificar Vitória
   - `5` - Exibir Missões
   - `0` - Sair

### Realizando um Ataque
1. Selecione a opção 3 no menu
2. Visualize a lista de territórios com seus índices
3. Digite o índice do território atacante (deve ter pelo menos 2 tropas)
4. Digite o índice do território defensor (deve pertencer a outro jogador)
5. O sistema simula a batalha automaticamente

### Regras de Batalha
- Atacante precisa ter pelo menos 2 tropas no território
- Número de dados: até 3 para atacante, até 2 para defensor
- Dados são comparados do maior para o menor
- Em empate, defensor vence
- Território conquistado quando defensor perde todas as tropas

## Técnicas de Programação Utilizadas

### Alocação Dinâmica de Memória
```c
jogo->jogadores = (Jogador*)malloc(num_jogadores * sizeof(Jogador));
```

### Uso de Ponteiros
```c
Territorio *atac = &jogo->territorios[territorio_atacante];
```

### Estruturas de Dados Complexas
- Structs aninhadas
- Arrays dinâmicos
- Ponteiros para structs

### Modularização
- Separação de interface (war.h) e implementação (war.c)
- Funções especializadas para cada funcionalidade
- Código reutilizável e manutenível

## Requisitos do Sistema

- Compilador GCC (ou compatível)
- Sistema operacional: Linux, macOS, ou Windows (com MinGW)
- Make (para usar o Makefile)

## Conceitos de C Aplicados

1. **Structs**: Organização de dados complexos
2. **Ponteiros**: Manipulação eficiente de memória
3. **Alocação Dinâmica**: `malloc()` e `free()`
4. **Arrays**: Vetores estáticos e dinâmicos
5. **Modularização**: Separação em múltiplos arquivos
6. **Entrada/Saída**: `printf()` e `scanf()`
7. **Strings**: Manipulação com `strcpy()` e `strcmp()`
8. **Números Aleatórios**: `rand()` e `srand()`

## Autor

Desenvolvido para o projeto de estrutura de dados do jogo War.

## Licença

Projeto educacional - Livre para uso acadêmico.