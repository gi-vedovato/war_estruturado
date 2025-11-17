# Guia de Uso do Jogo War Estruturado

## Compilação

Para compilar o projeto, execute:

```bash
make
```

Para compilar e executar os testes automatizados:

```bash
make test
```

## Execução

### Programa Principal (Interativo)

```bash
./war_game
```

ou

```bash
make run
```

### Programa de Testes (Automático)

```bash
./test_war
```

## Fluxo do Jogo

### 1. Inicialização

Ao iniciar o jogo, o sistema:
- Inicializa 24 territórios (12 da Ásia e 12 da América do Sul)
- Solicita o número de jogadores (2-6)
- Solicita nome e cor de cada jogador
- Distribui territórios equitativamente
- Distribui tropas iniciais
- Atribui missões estratégicas

### 2. Menu Principal

O jogo apresenta as seguintes opções:

```
========== JOGO WAR ==========
1. Exibir Mapa
2. Exibir Jogadores
3. Realizar Ataque
4. Verificar Vitória
5. Exibir Missões
0. Sair
==============================
```

### 3. Opções do Menu

#### Opção 1: Exibir Mapa
Mostra todos os territórios organizados por continente, com:
- Nome do território
- Número de tropas
- Proprietário (nome e cor)

#### Opção 2: Exibir Jogadores
Lista todos os jogadores com:
- Nome e cor
- Tropas disponíveis
- Territórios conquistados

#### Opção 3: Realizar Ataque
Permite atacar um território:
1. Exibe lista de todos os territórios com índices
2. Solicita índice do território atacante
3. Solicita índice do território defensor
4. Realiza simulação da batalha com dados
5. Exibe resultado (perdas de tropas, conquista)

**Regras de Ataque:**
- Território atacante deve ter pelo menos 2 tropas
- Território defensor deve pertencer a outro jogador
- Atacante lança até 3 dados
- Defensor lança até 2 dados
- Dados são comparados do maior para o menor
- Em empate, defensor vence
- Território é conquistado quando defensor perde todas as tropas

#### Opção 4: Verificar Vitória
Verifica se algum jogador completou sua missão:
- Mostra missão de cada jogador
- Indica se a missão foi cumprida
- Declara vencedor se houver

#### Opção 5: Exibir Missões
Lista as missões de todos os jogadores:
- "Conquistar completamente a Ásia"
- "Conquistar completamente a América do Sul"
- "Conquistar X territórios"

### 4. Exemplo de Uso

```
1. Iniciar jogo
2. Cadastrar 3 jogadores:
   - João (Vermelho)
   - Maria (Azul)
   - Pedro (Verde)
3. Territórios são distribuídos automaticamente
4. Usar opção 1 para ver o mapa
5. Usar opção 3 para realizar ataques estratégicos
6. Usar opção 4 para verificar progresso
7. Continuar até algum jogador completar sua missão
```

## Conceitos de Programação Demonstrados

### Structs
```c
typedef struct {
    char nome[MAX_NOME];
    char continente[MAX_NOME];
    int tropas;
    int proprietario;
} Territorio;
```

### Alocação Dinâmica
```c
jogo->jogadores = (Jogador*)malloc(num_jogadores * sizeof(Jogador));
```

### Ponteiros
```c
Territorio *atac = &jogo->territorios[territorio_atacante];
```

### Vetores de Structs
```c
Territorio *territorios; // Array dinâmico de territórios
```

## Observações Importantes

1. **Gerenciamento de Memória**: Toda memória alocada dinamicamente é liberada ao final do jogo
2. **Modularidade**: Código separado em arquivos .h (interface) e .c (implementação)
3. **Validação**: Sistema valida todas as entradas do usuário
4. **Aleatoriedade**: Dados são lançados aleatoriamente usando srand(time(NULL))

## Teste Automático

O programa `test_war` demonstra:
- Inicialização de estruturas
- Alocação dinâmica de memória
- Sistema de ataque
- Verificação de vitória
- Uso de ponteiros
- Cálculo de memória utilizada

Execute com: `make test`

## Limpeza

Para remover arquivos compilados:

```bash
make clean
```

Para recompilar do zero:

```bash
make rebuild
```

## Estrutura de Arquivos

```
war_estruturado/
├── war.h           # Definições e protótipos
├── war.c           # Implementação das funções
├── main.c          # Programa principal
├── test.c          # Programa de testes
├── Makefile        # Automação de compilação
├── README.md       # Documentação completa
└── GUIA_USO.md     # Este guia
```

## Requisitos

- GCC ou compilador C compatível
- Make (opcional, mas recomendado)
- Sistema Linux, macOS ou Windows com MinGW

## Solução de Problemas

### Erro de Compilação
```bash
make clean
make
```

### Programa não executa
```bash
chmod +x war_game
./war_game
```

### Entrada de jogadores não funciona
Certifique-se de pressionar Enter após cada entrada e usar texto sem caracteres especiais.

## Desenvolvimento Futuro

Possíveis melhorias:
- Adicionar mais continentes
- Implementar conexões entre territórios
- Adicionar cartas especiais
- Sistema de save/load
- Interface gráfica

## Autor

Projeto desenvolvido para demonstrar conceitos de:
- Estruturas de dados em C
- Alocação dinâmica de memória
- Ponteiros e referências
- Modularização de código
- Programação estruturada
