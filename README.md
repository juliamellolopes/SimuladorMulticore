
# Simulador da Arquitetura de Von Neumann e Pipeline MIPS

Este projeto implementa um simulador básico da arquitetura de Von Neumann e do pipeline MIPS em C++. O objetivo é permitir a visualização prática do funcionamento de componentes como a CPU, a memória principal, a memória cache, e o pipeline, além de demonstrar o impacto das instruções executadas em paralelo usando o pipeline MIPS.

## Funcionalidades

1. **CPU**: Simula o comportamento de uma CPU com múltiplos registradores e uma Unidade Lógica Aritmética (ULA).
2. **Memória Principal e Cache**: A memória principal é simulada como um vetor, enquanto a cache é implementada como uma fila (FIFO), com substituição simples.
3. **Pipeline MIPS**: Implementa os cinco estágios do pipeline MIPS:
   - **IF (Instruction Fetch)**: Busca a instrução da memória.
   - **ID (Instruction Decode)**: Decodifica a instrução.
   - **EX (Execute)**: Executa a operação na ULA.
   - **MEM (Memory Access)**: Acessa a memória principal.
   - **WB (Write Back)**: Escreve o resultado no registrador.
   
4. **Simulação de Políticas de Cache**: A cache utiliza a política de substituição FIFO para gerenciar os dados armazenados.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
/Simulador
  ├── src/
  │    ├── main.cpp          # Arquivo principal que inicia o simulador
  │    ├── cpu.cpp           # Implementação das funções da CPU e ULA
  │    ├── memory.cpp        # Implementação das funções de memória e cache
  │    └── pipeline.cpp      # Implementação do pipeline MIPS
  ├── include/
  │    ├── cpu.h             # Declaração das funções da CPU e ULA
  │    ├── memory.h          # Declaração das funções de memória e cache
  │    └── pipeline.h        # Declaração das funções do pipeline MIPS
  └── Makefile               # Arquivo Make para compilar e rodar o projeto
```

### Arquivos:

- `main.cpp`: Responsável por simular uma execução de uma instrução usando o pipeline MIPS e cache.
- `cpu.cpp`/`cpu.h`: Contém a lógica da CPU, incluindo os registradores, Unidade Lógica Aritmética (ULA) e Unidade de Controle.
- `memory.cpp`/`memory.h`: Simula a memória principal e a cache com política de substituição FIFO.
- `pipeline.cpp`/`pipeline.h`: Implementa os cinco estágios do pipeline MIPS.

## Requisitos

- **Compilador C++**: Certifique-se de ter um compilador C++ instalado (como `g++`).
- **Make**: Utilize `make` para compilar o projeto.

## Instruções de Compilação e Execução

### Compilando o Projeto

Para compilar o projeto, basta rodar o comando:

```bash
make
```

Isso irá compilar todos os arquivos `.cpp` e gerar o executável na pasta `bin/`.

### Executando o Simulador

Para rodar o simulador após a compilação, execute:

```bash
make run
```

O simulador irá executar uma instrução `ADD` (soma) e simular os cinco estágios do pipeline MIPS, além de realizar uma leitura de memória com cache. O resultado será mostrado no terminal.

### Limpando os Arquivos Compilados

Para remover os arquivos compilados (objetos e binários), execute:

```bash
make clean
```

## Explicação do Funcionamento

### CPU e Registradores

A CPU possui múltiplos registradores organizados em núcleos, com suporte para uma ULA que executa operações aritméticas como soma (+), subtração (-), multiplicação (*) e divisão (/). A Unidade de Controle processa as instruções com base nos opcodes, gerenciando o fluxo dos dados entre os registradores e a memória.

### Memória e Cache

A memória principal (RAM) armazena as instruções, enquanto a cache age como um buffer FIFO. Quando a cache atinge seu limite de capacidade, os dados mais antigos são transferidos para a RAM, liberando espaço para novas operações.

### Pipeline MIPS

O pipeline MIPS simula a execução paralela de instruções em cinco estágios:

- **Instruction Fetch (IF)**: Busca a instrução da memória.
- **Instruction Decode (ID)**: Decodifica a instrução e identifica os operandos e o tipo de operação.
- **Execute (EX)**: A ULA executa a operação aritmética e, caso necessário, armazena o resultado na memória.
- **Memory Access (MEM)**: Lê ou escreve na memória.
- **Write Back (WB)**: Escreve o resultado de volta nos registradores.

O pipeline permite que as instruções sejam processadas em paralelo, simulando um sistema de execução com três estágios básicos.

## Autor

Este projeto foi desenvolvido por Julia Mello Loeps Gonçalves.
