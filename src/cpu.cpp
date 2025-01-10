#include "../include/cpu.h"

void CPU::init() {
    _PC = 0;
    _coreAtivo = 0;
    _cores = vector<CORE>(TAM_C);
}

void CPU::inicializar() {

    cout << "Iniciando Simulacao com " << TAM_C << " Cores e " << TAM_R << " Registradores cada" << endl << endl;
    cout << _coreAtivo << endl;


    _cores[_coreAtivo]._reg1 = _cores[_coreAtivo]._reg2 = _cores[_coreAtivo]._regDest = 0;

    for (int i = 0; i < TAM_INSTRUCTIONS; i++) {
        cout << "--- Inciando processo " << _memoryRAM.getInstrucaoAtual() << " ---" << endl << endl;
        InstructionLoop();
        cout << endl << "Instruções " << _memoryRAM.getInstrucaoAtual() << " finalizadas." << endl << endl;
        _memoryRAM.incrementaInstrucao();
    }
}

/**
 * @brief Controla o ciclo de execução do pipeline, processando todas as instruções.
 */
void CPU::InstructionLoop() {
    const int TAM_I = _memoryRAM.getSize();
    vector<bool> control(TAM_I, false);
    int cont = TAM_I;

    while (cont > 1) {

        if (control[_PC] == false) {
            cont = TAM_I;
            control[_PC] = true;

            _pipeline.InstructionFetch();
            auto code = _pipeline.InstructionDecode();

            if (code.size() != 0) {
                auto valores = _pipeline.Execute(code);
                select(valores[0], valores[1], valores[2]);
            }

            incrementaPC();
        } else {
            cont--;
        }
    }

    _memoryRAM.mostrarDados();

}

/**
 * @brief Incrementa o contador de programa (PC) e faz um loop baseado no tamanho da memória.
 */
void CPU::incrementaPC() {
    _PC++;
    _PC = _PC % _memoryRAM.getSize();
}
