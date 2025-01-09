
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
  │    ├── main.cpp          # Entrada principal do simulador
  │    ├── cpu.cpp           # Implementação da CPU 
  │    ├── memory.cpp        # Implementação da memória principal e cache
  │    ├── pipeline.cpp      # Implementação do pipeline MIPS
  │    └── uc.cpp            # Implementação da Unidade de Controle (UC) e ULA
  ├── include/
  │    ├── cpu.h             # Declaração da CPU 
  │    ├── memory.h          # Declaração da memória principal e cache
  │    ├── pipeline.h        # Declaração do pipeline MIPS
  │    ├── uc.h              # Declaração da UC e ULA
  │    └── core.h            # Estrutura básica de registradores
  └── Makefile               # Script Make para compilação
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

### Exemplo de Arquivo de Instrução

O arquivo de entrada (`instructions.txt`) deve conter as instruções no seguinte formato:

```plaintext
LOAD R1 10
ADD R3 R1 R2
STORE R3 15
IF R1 > R2
MULT R4 R1 R2

Ao rodar o simulador com o exemplo acima, a saída será semelhante a:

--------- Pipeline Stage: Instruction Fetch ---------
Buscando instrucao...
LOAD R1 10

--------- Pipeline Stage: Instruction Decode ---------
Decodificando: LOAD R1 10

--------- Pipeline Stage: Execution ---------
Executando operacao LOAD
Valor 10 foi escrito no Registrador R1 no Core 0

--------- Pipeline Stage: Instruction Fetch ---------
Buscando instrucao...
ADD R3 R1 R2

--------- Pipeline Stage: Instruction Decode ---------
Decodificando: ADD R3 R1 R2

--------- Pipeline Stage: Execution ---------
Executando operacao ADD: 10 + 0 = 10
Valor 10 foi escrito no Registrador R3 no Core 0

--------- Pipeline Stage: Instruction Fetch ---------
Buscando instrucao...
STORE R3 15

--------- Pipeline Stage: Instruction Decode ---------
Decodificando: STORE R3 15

--------- Pipeline Stage: Execution ---------
Guardando o valor no endereço 15 da memória
Valor 10 foi armazenado no endereco 15

--------- Pipeline Stage: Instruction Fetch ---------
Buscando instrucao...
IF R1 > R2

--------- Pipeline Stage: Instruction Decode ---------
Decodificando: IF R1 > R2

--------- Pipeline Stage: Execution ---------
Executando operacao IF: 10 > 0 = Verdade

--------- Pipeline Stage: Instruction Fetch ---------
Buscando instrucao...
MULT R4 R1 R2

--------- Pipeline Stage: Instruction Decode ---------
Decodificando: MULT R4 R1 R2

--------- Pipeline Stage: Execution ---------
Executando operacao MULT: 10 * 0 = 0
Valor 0 foi escrito no Registrador R4 no Core 0



## Explicação do Funcionamento

### CPU e UC

A CPU gerencia os núcleos e registradores, enquanto a Unidade de Controle coordena as operações com base nos opcodes.

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

## Comandos Suportados

| **Instrução** | **Descrição**                          | **Exemplo**       |
|---------------|----------------------------------------|-------------------|
| `LOAD`        | Carrega valor na memória para registro | `LOAD R1 10`      |
| `STORE`       | Armazena registro na memória           | `STORE R3 15`     |
| `ADD`         | Soma valores                          | `ADD R3 R1 R2`    |
| `SUB`         | Subtrai valores                       | `SUB R3 R1 R2`    |
| `MULT`        | Multiplica valores                    | `MULT R4 R1 R2`   |
| `DIV`         | Divide valores                        | `DIV R5 R1 R2`    |
| `IF`          | Compara valores                       | `IF R1 > R2`      |

## Autor

Este projeto foi desenvolvido por Julia Mello Loeps Gonçalves.
