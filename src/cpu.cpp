#include "../include/cpu.h"


// Inicializa a CPU com uma referência de memória e configura os registradores, ponteiro de programa e núcleo ativo.
CPU::CPU(MemoryRAM &memory) {
    _memoryRAM = memory;
    _PC = 0;
    _coreAtivo = 0;
    _cores = vector<CORE>(TAM_C);
    cout << "--- Iniciando Simulacao com " << TAM_C << " Cores e " << TAM_R << " Registradores cada ---" << endl;
}

// Retorna o valor do contador de programa (_PC).
int CPU::getPC() {
    return _PC;
}

/**
 * @brief Incrementa o valor do ponteiro de programa e faz um loop com base no tamanho da memória.
 * 
 */
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
    int valor = lerRegistrador(_cores[_coreAtivo]._reg1);
    _memoryCache.escrever(endereco, valor);
}
