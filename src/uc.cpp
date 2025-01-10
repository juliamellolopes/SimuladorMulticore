#include "../include/uc.h"

/**
 * @brief Realiza uma operação aritmética ou condicional entre dois valores.
 *
 * @param var1 Primeiro valor.
 * @param var2 Segundo valor.
 * @param operador Operação a ser executada (+, -, *, /, <, >, =).
 * @return Resultado da operação.
 */
int ULA::operation(int var1, int var2, char operador) {
    cout << "[ULA] ";

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

/**
 * @brief Executa a operação correspondente ao opcode usando a ULA.
 *
 * @param opcode Código da operação.
 */
void UC::select(int opcode, int valor1, int valor2) {
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

    // escreverRegistrador(_cores[_coreAtivo]._regDest, res);
}