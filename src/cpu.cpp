#include "../include/cpu.h"

/**
 * @brief Inicializa a CPU com uma referência de memória principal.
 *
 * Configura os registradores, contador de programa (PC) e núcleo ativo (Core).
 * @param memory Referência para a memória principal (RAM).
 */
CPU::CPU(MemoryRAM &memory) {
    _memoryRAM = memory;
    _PC = 0;
    _coreAtivo = 0;
    _cores = vector<CORE>(TAM_C);
    cout << "Iniciando Simulacao com " << TAM_C << " Cores e " << TAM_R << " Registradores cada" << endl << endl;
}

/**
 * @brief Retorna o valor do contador de programa (PC).
 * @return Valor atual do contador de programa.
 */
int CPU::getPC() {
    return _PC;
}

/**
 * @brief Incrementa o contador de programa (PC) e faz um loop baseado no tamanho da memória.
 */
void CPU::incrementaPC() {
    _PC++;
    _PC = _PC % _memoryRAM.getSize();
}

/**
 * @brief Lê o valor de um registrador específico do núcleo ativo.
 *
 * @param reg Índice do registrador a ser lido.
 * @return Valor armazenado no registrador.
 */

int CPU::lerRegistrador(int reg) {
    if (reg > 0 && reg <= TAM_R) {

        return _cores[_coreAtivo]._registradores[reg - 1];

    } else {
        cerr << "Erro: Registrador invalido!" << endl;
        return -1;
    }
}

/**
 * @brief Escreve um valor em um registrador específico do núcleo ativo.
 *
 * @param reg Índice do registrador a ser escrito.
 * @param valor Valor a ser armazenado no registrador.
 */
void CPU::escreverRegistrador(int reg, int valor) {
    if (reg > 0 && reg <= TAM_R) {

        _cores[_coreAtivo]._registradores[reg - 1] = valor;
        cout << "      -> Valor " << valor << " foi escrito no Registrador R" << reg << " no Core " << _coreAtivo << endl << endl;

    } else {
        cerr << "Erro: Registrador invalido!" << endl;
    }
}

/**
 * @brief Escreve o valor de um registrador em um endereço específico na memória.
 *
 * @param endereco Endereço de memória onde o valor será escrito.
 */
void CPU::escreverNaMemoria(int endereco) {
    int valor = lerRegistrador(_cores[_coreAtivo]._reg1);
    _memoryCache.escrever(endereco, valor);
}
