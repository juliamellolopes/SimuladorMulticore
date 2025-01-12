#include "../include/cpu.h"

void CPU::init() {
    _PC = 0;
    _coreAtivo = 0;
    _processosAtivos = 0;
    _cores = vector<CORE>(TAM_CORE);
    _cores[_coreAtivo]._reg1 = 0;
    _cores[_coreAtivo]._reg2 = 0;
    _cores[_coreAtivo]._regDest = 0;
}

void CPU::inicializar() {

    cout << "Iniciando Simulacao com " << TAM_CORE << " Cores e " << TAM_R << " Registradores cada" << endl << endl;

    int posicaoInicial = 12;
    int idInicial = 1001;

    for (int i = 0; i < TAM_INSTRUCTIONS; i++) {
        ostringstream hexStream;
        hexStream << hex << uppercase << posicaoInicial + i;
        string endereco = hexStream.str();

        Processo processo;
        processo._pcb.setInstrucoes(_memoryRAM._instrucoes[i]);
        processo._pcb.setLimite(_memoryRAM._instrucoes[i].size() + TAM_R + 18);
        processo._pcb.setEnderecoBase(endereco);
        processo._pcb.setId(idInicial++);

        _processosID.push(endereco);
        _memoryRAM.guardarProcesso(endereco, processo);
    }


    do {
        organizarFila();
        _processosAtivos = 0;

        while (!_processosID.empty()) {
            auto processoID = _processosID.front();

            Processo processo;
            bool isProcesso = false;

            visit([&processo, &isProcesso](auto &&value) {
                if constexpr (is_same_v<decay_t<decltype(value)>, Processo>) {
                    processo = value;
                    isProcesso = true;
                } else {
                    cout << "Não é um processo!" << endl;
                }
            }, _memoryRAM.getProcesso(processoID));

            if (isProcesso) {
                processamento(processo);
            } else {
                cout << "Erro: ID inválido ou não é um processo válido." << endl;
            }

            _processosID.pop();
            if (processo.getCicloVida() != PRONTO) {
                gerenciarPrioridade(processo);
            }

            cout << endl;
        }
    } while (_processosAtivos > 0);

    _memoryCache.liberarCache();
    _memoryRAM.mostrarDados();
}

void CPU::gerenciarPrioridade(Processo &processo) {
    if (processo._pcb.getPrioridade() == BAIXA) {
        _filaAuxiliarBaixa.push(processo._pcb.getEnderecoBase());
    } else if (processo._pcb.getPrioridade() == ALTA) {
        _filaAuxiliarAlta.push(processo._pcb.getEnderecoBase());
    } else {
        _filaAuxiliarMedia.push(processo._pcb.getEnderecoBase());
    }

    _processosAtivos++;
}

void CPU::organizarFila() {
    atualizarFila(_filaAuxiliarAlta);
    atualizarFila(_filaAuxiliarMedia);
    atualizarFila(_filaAuxiliarBaixa);
}

void CPU::atualizarFila(queue<string> &fila) {
    while (!fila.empty()) {
        auto endereco = fila.front();
        _processosID.push(endereco);
        fila.pop();
    }
}

void CPU::processamento(Processo &processo) {
    int contQuantum = 0;

    if (processo.getCicloVida() == BLOQUEADO) {
        queue<pair<int, int>> reg = processo._pcb.getRegistradores();
        atualizarRegistradores(reg);
        processo.setCicloVida(EXECUTANDO);

        while (contQuantum < QUANTUM_CPU) {
            contQuantum += processo._pcb.getQuantum();
            cout << "[Processo ID]: " << processo._pcb.getId() << endl;

            executePipeline(processo._pcb.getInstrucao());
            processo._pcb.incrementeEstado();

            if (processo._pcb.checkEstadoFinalizado()) {
                processo.setCicloVida(PRONTO);
                _memoryRAM.guardarProcesso(processo._pcb.getEnderecoBase(), processo);
                return;
            }
        }
        processo.setCicloVida(BLOQUEADO);
        processo.dowloadRegistrador(_cores[_coreAtivo]._registradores);
        _memoryRAM.guardarProcesso(processo._pcb.getEnderecoBase(), processo);
    }

}

void CPU::executePipeline(const string &instrucao) {
    _pipeline.InstructionFetch(instrucao);
    auto code = _pipeline.InstructionDecode();

    if (code.size() != 0) {
        auto valores = _pipeline.Execute(code);
        auto res = select(valores[0], valores[1], valores[2]);
        _pipeline.escreverRegistrador(_cores[_coreAtivo]._regDest, res);
    }
}

void CPU::atualizarRegistradores(queue<pair<int, int>> &registradores) {
    while (!registradores.empty()) {
        auto [index, valor] = registradores.front();
        _cores[_coreAtivo]._registradores[index] = valor;
        registradores.pop();
    }
}

/**
 * @brief Incrementa o contador de programa (PC) e faz um loop baseado no tamanho da memória.
 */
void CPU::incrementaPC() {
    _PC++;
}
