#include "../include/uc.h"

UC::UC() {
    // Instancia MemoryRAM com o arquivo "instructions.txt" que contém as instruções para execução.
    MemoryRAM memory("instructions.txt");
    // Cria um objeto CPU, passando a memória instanciada.
    CPU cpu(memory);

    _memory = memory;
    _cpu = cpu;
}

// Executa operações aritméticas com base no opcode (ADD, SUB, MULT, DIV), chamando a função ULA para realizar a operação e exibindo mensagens para cada operação realizada.
void UC::select(int opcode) {
    int valor1 = _cpu.lerRegistrador(_cpu._cores[_cpu._coreAtivo]._reg1);
    int valor2 = _cpu.lerRegistrador(_cpu._cores[_cpu._coreAtivo]._reg2);
    int res;

    switch (opcode) {
    case 0:
        res = _ula.operation(valor1, valor2, '+');
        cout << "Executando operacao ADD: " << valor1 << " + " << valor2 << " = " << res << endl;
        break;
    case 1:
        res = _ula.operation(valor1, valor2, '-');
        cout << "Executando operacao SUB: " << valor1 << " - " << valor2 << " = " << res << endl;
        break;
    case 2:
        res = _ula.operation(valor1, valor2, '*');
        cout << "Executando operacao MULT: " << valor1 << " * " << valor2 << " = " << res << endl;
        break;
    case 3:
        res = _ula.operation(valor1, valor2, '/');
        cout << "Executando operacao DIV: " << valor1 << " / " << valor2 << " = " << res << endl;
        break;
    case 4:
        res = _ula.operation(valor1, valor2, '<');
        cout << "Executando operacao IF: " << valor1 << " < " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    case 5:
        res = _ula.operation(valor1, valor2, '>');
        cout << "Executando operacao IF: " << valor1 << " > " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    case 6:
        res = _ula.operation(valor1, valor2, '=');
        cout << "Executando operacao IF: " << valor1 << " == " << valor2 << " = " << ((res) ? "Verdade" : "Falso") << endl;
        break;
    default:
        res = 0;
        break;
    }

    _cpu.escreverRegistrador(_cpu._cores[_cpu._coreAtivo]._regDest, res);
}

// Etapa de execução
/**
 * @brief realiza operação entre var1 e var2 
 * 
 * @param var1 
 * @param var2 
 * @param operador 
 * @return int 
 */
int ULA::operation(int var1, int var2, char operador) {

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