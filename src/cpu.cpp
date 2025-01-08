#include "../include/cpu.h"

// Inicializa o vetor de registradores com zeros.
REG::REG() {
    _registradores = vector(TAM_R, 0);
}

// Inicializa a CPU com uma referência de memória e configura os registradores, ponteiro de programa e núcleo ativo.
CPU::CPU(MemoryRAM &memory) {
    _memoryRAM = memory;
    _PC = 0;
    _coreAtivo = 0;
    _cores = vector<REG>(TAM_C);
    cout << "--- Iniciando Simulacao com " << TAM_C << " Cores e " << TAM_R << " Registradores cada ---" << endl;
}

// Retorna o valor do contador de programa (_PC).
int CPU::getPC() {
    return _PC;
}

// Incrementa o valor do ponteiro de programa e faz um loop com base no tamanho da memória.
void CPU::incrementaPC() {
    _PC++;
    _PC = _PC % _memoryRAM.getSize();
}

// Lê o valor de um registrador específico do núcleo ativo. Valida o registrador e exibe uma mensagem de erro se for inválido.
int CPU::lerRegistrador(int reg) {
    if (reg > 0 && reg <= TAM_R) {
        return _cores[_coreAtivo]._registradores[reg - 1];
    } else {
        cerr << "Erro: Registrador invalido!" << endl;
        return -1;
    }
}

// Escreve um valor em um registrador específico do núcleo ativo e exibe uma mensagem de confirmação. Valida o registrador e exibe erro se for inválido.
void CPU::escreverRegistrador(int reg, int valor) {
    if (reg > 0 && reg <= TAM_R) {
        _cores[_coreAtivo]._registradores[reg - 1] = valor;
        cout << "Valor " << valor << " foi escrito no Registrador R" << reg << " no Core " << _coreAtivo << endl;
    } else {
        cerr << "Erro: Registrador invalido!" << endl;
    }
}

// Escreve o valor de um registrador em um endereço específico na memória cache.
void CPU::escreverNaMemoria(int endereco) {
    int valor = lerRegistrador(_reg1);
    _memoryCache.escrever(endereco, valor);
}

// Executa operações aritméticas com base no opcode (ADD, SUB, MULT, DIV), chamando a função ULA para realizar a operação e exibindo mensagens para cada operação realizada.
void CPU::UC(int opcode) {
    int valor1 = lerRegistrador(_reg1);
    int valor2 = lerRegistrador(_reg2);
    int res;

    switch (opcode) {
    case 0:
        res = ULA(valor1, valor2, '+');
        cout << "Executando operacao ADD: " << valor1 << " + " << valor2 << " = " << res << endl;
        break;
    case 1:
        res = ULA(valor1, valor2, '-');
        cout << "Executando operacao SUB: " << valor1 << " - " << valor2 << " = " << res << endl;
        break;
    case 2:
        res = ULA(valor1, valor2, '*');
        cout << "Executando operacao MULT: " << valor1 << " * " << valor2 << " = " << res << endl;
        break;
    case 3:
        res = ULA(valor1, valor2, '/');
        cout << "Executando operacao DIV: " << valor1 << " / " << valor2 << " = " << res << endl;
        break;
    case 4:
        res = ULA(valor1, valor2, '<');
        cout << "Executando operacao IF: " << valor1 << " < " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    case 5:
        res = ULA(valor1, valor2, '>');
        cout << "Executando operacao IF: " << valor1 << " > " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    case 6:
        res = ULA(valor1, valor2, '=');
        cout << "Executando operacao IF: " << valor1 << " == " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    default:
        res = 0;
        break;
    }

    escreverRegistrador(_regDest, res);
}

// Etapa de execução
int CPU::ULA(int var1, int var2, char operador) {
    int resultado;

    cout << "\n--------- CPU: Unidade Lógica Aritmética ---------\n";

    switch (operador) {
    case '+': // ADD
        return var1 + var2;
    case '-': // SUB
        return var1 - var2;
    case '*': // MULT
        return var1 * var2;
    case '/': // DIV
        if (var2 != 0) {
            return var1 / var2;
        } else {
            cerr << "Erro: Divisão por zero!" << endl;
            exit(EXIT_FAILURE);
        }
    case '<':
        return var1 < var2;
    case '>':
        return var1 > var2;
    case '=':
        return var1 == var2;
    default:
        cerr << "Operacao invalida!" << endl;
        exit(EXIT_FAILURE);
    }
}