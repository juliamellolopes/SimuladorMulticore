# Simulador da Arquitetura de Von Neumann e Pipeline MIPS

Este projeto implementa um simulador avançado da arquitetura de Von Neumann com suporte ao pipeline MIPS em C++. O objetivo é permitir a visualização prática do funcionamento de componentes como a CPU, a memória principal, a memória cache e o pipeline, além de demonstrar o impacto das políticas de escalonamento de processos e da execução de instruções em paralelo.

## Funcionalidades

1. **CPU Multicore**:
   - Gerencia múltiplos núcleos (cores) com registradores independentes.
   - Integra-se ao pipeline MIPS para execução de instruções.
   - Suporta diferentes políticas de escalonamento: FCFS, Round Robin e Prioridade.
2. **Memória Hierárquica**:
   - **Memória Principal (RAM)**: Simula a memória principal com carregamento de instruções a partir de arquivos de texto.
   - **Memória Cache**: Implementada como uma fila FIFO com descarte automático para a memória principal quando cheia.
3. **Pipeline MIPS**:
   - Implementa os cinco estágios do pipeline MIPS:
     - **IF (Instruction Fetch)**: Busca a instrução da memória.
     - **ID (Instruction Decode)**: Decodifica a instrução.
     - **EX (Execute)**: Executa a operação na ULA.
     - **MEM (Memory Access)**: Acessa a memória principal.
     - **WB (Write Back)**: Escreve o resultado no registrador.
4. **Gerenciamento de Processos**:
   - Cada processo possui um bloco de controle (PCB) contendo informações como prioridade, instruções e estado.
   - O escalonador gerencia a fila de processos e decide qual será executado com base na política escolhida.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
/Simulador
  ├── src/
  │    ├── main.cpp          # Entrada principal do simulador
  │    ├── cpu.cpp           # Implementação da CPU
  │    ├── ram.cpp           # Implementação da memória principal
  │    ├── cache.cpp         # Implementação da memória cache
  │    ├── pipeline.cpp      # Implementação do pipeline MIPS
  │    ├── escalonador.cpp   # Implementação do escalonador
  │    └── uc.cpp            # Implementação da Unidade de Controle e ULA
  ├── include/
  │    ├── cpu.h             # Declaração da CPU
  │    ├── ram.h             # Declaração da memória principal
  │    ├── cache.h           # Declaração da memória cache
  │    ├── pipeline.h        # Declaração do pipeline MIPS
  │    ├── escalonador.h     # Declaração do escalonador
  │    ├── pcb.h             # Declaração do bloco de controle de processos (PCB)
  │    ├── processo.h        # Declaração da classe Processo
  │    ├── uc.h              # Declaração da UC e ULA
  │    └── core.h            # Estrutura básica de registradores
  └── Makefile               # Script Make para compilação
```

### Principais Componentes

- `main.cpp`: Ponto de entrada do simulador. Permite ao usuário escolher a política de escalonamento e inicializa a CPU.
- `cpu.cpp`/`cpu.h`: Implementa a lógica da CPU, incluindo gerenciamento de núcleos, threads e execução de processos.
- `ram.cpp`/`ram.h` e `cache.cpp`/`cache.h`: Simulam a memória principal e a cache.
- `pipeline.cpp`/`pipeline.h`: Implementam o pipeline MIPS, coordenando os cinco estágios para cada instrução.
- `escalonador.cpp`/`escalonador.h`: Gerenciam a ordem de execução dos processos com suporte a três políticas de escalonamento (FCFS, RR e Prioridade).
- `pcb.h`: Representa o bloco de controle de processos (PCB), contendo informações sobre os processos.
- `processo.h`: Encapsula o estado e o PCB de cada processo.
- `uc.cpp`/`uc.h`: Implementam a Unidade de Controle e a Unidade Lógica e Aritmética.
- `core.h`: Define a estrutura de registradores utilizada pelos núcleos da CPU.

## Requisitos

- **Compilador C++**: Certifique-se de ter um compilador C++ instalado (como `g++`).
- **Make**: Utilize `make` para compilar o projeto.

## Instruções de Compilação e Execução

### Compilando o Projeto

Para compilar o projeto, execute:

```bash
make
```

Isso irá compilar todos os arquivos `.cpp` e gerar o executável na pasta `bin/`.

### Executando o Simulador

Para rodar o simulador após a compilação, execute:

```bash
make run
```

O simulador irá inicializar a CPU, carregar processos e simular a execução com base na política de escalonamento escolhida.

### Limpando os Arquivos Compilados

Para remover os arquivos compilados (objetos e binários), execute:

```bash
make clean
```

### Exemplo de Arquivo de Instrução

O arquivo de entrada deve conter instruções no seguinte formato:

```plaintext
LOAD R1 10
ADD R3 R1 R2
STORE R3 15
IF R1 > R2
MULT R4 R1 R2
```
### Comandos Suportados

Abaixo segue os comandos que o simulador suporta atualmente caso queira alterar o `instructions.txt`:

| **Instrução** | **Descrição**                          | **Exemplo**     |
| ------------- | -------------------------------------- | --------------- |
| `LOAD`        | Carrega valor na memória para registro | `LOAD R1 10`    |
| `STORE`       | Armazena registro na memória           | `STORE R3 15`   |
| `ADD`         | Soma valores                           | `ADD R3 R1 R2`  |
| `SUB`         | Subtrai valores                        | `SUB R3 R1 R2`  |
| `MULT`        | Multiplica valores                     | `MULT R4 R1 R2` |
| `DIV`         | Divide valores                         | `DIV R5 R1 R2`  |
| `IF`          | Compara valores                        | `IF R1 > R2`    |

## Políticas de Escalonamento

O simulador suporta as seguintes políticas de escalonamento:

1. **FCFS (First-Come, First-Served)**: Executa os processos na ordem de chegada.
2. **Round Robin (RR)**: Cada processo recebe um quantum fixo para executar e alterna até terminar.
3. **Prioridade**: Processos de alta prioridade são executados antes dos de prioridade média e baixa.

## Fluxo de Funcionamento do Simulador

1. **Inicialização**:
   - O usuário escolhe a política de escalonamento e o modo de exibição (detalhado ou resumido).
   - A CPU, pipeline e memória são configurados.
2. **Carregamento de Processos**:
   - As instruções são carregadas na memória principal a partir de arquivos de texto.
3. **Execução**:
   - O escalonador seleciona o próximo processo com base na política configurada.
   - O pipeline executa as instruções usando os cinco estágios (IF, ID, EX, MEM, WB).
4. **Finalização**:
   - O simulador para quando todas as instruções forem executadas.

## Contato

Este projeto foi desenvolvido por **Julia Mello Lopes Gonçalves**, estudante de Engenharia da Computação.

- **E-mail**: juliamellolopesgoncalves@gmail.com
- **GitHub**: [github.com/juliamellolopes](https://github.com/juliamellolopes)