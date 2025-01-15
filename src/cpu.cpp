#include "../include/cpu.h"

void CPU::init() {
    _PC = 0;
    _coreAtivo = 0;
    _processosAtivos = 0;
    _cores = vector<CORE>(TAM_CORE);
    for (auto &core : _cores) {
        core._reg1 = 0;
        core._reg2 = 0;
        core._regDest = 0;
    }
}

void CPU::inicializar() {

    if (getTipoExibicao()) {
        cout << "Iniciando Simulacao com " << TAM_CORE << " Cores e " << TAM_R << " Registradores cada" << endl << endl;
    } else {
        cout << " PID | CORE | TIME | Instruction " << endl << endl;
    }

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

    auto inicio = chrono::high_resolution_clock::now();
    inicializarThreads();
    _memoryCache.liberarCache();
    if (getTipoExibicao()) {
        _memoryRAM.mostrarDados();
    }

    auto fim = chrono::high_resolution_clock::now();
    auto duracao = chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);

    cout << "\nTempo de execução: " << duracao.count() << " ms" << endl;
}

void CPU::inicializarThreads() {

    if (getTipoExibicao()) {
        cout << "Inicializando Threads para " << TAM_CORE << " Cores" << endl;
    }

    for (int i = 0; i < TAM_CORE; ++i) {
        _threads.emplace_back([this, i]() {
            processarCore(i);
        });
    }

    for (auto &t : _threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    if (getTipoExibicao()) {
        cout << "Todas as Threads finalizaram o processamento." << endl;
    }
}

void CPU::processarCore(int coreID) {
    if (getTipoExibicao()) {
        cout << "[Core " << coreID << "] iniciando processamento..." << endl;
    }

    do {
        if (getPolitica() == PRIORIDADE) {
            _escalonador._prioridade.organizarFila();
            _processosAtivos = 0;
        }

        while (true) {
            this_thread::sleep_for(std::chrono::milliseconds(100));
            string processoID;

            {
                lock_guard<mutex> lock(_mutexFilaPrincipal);
                if (_processosID.empty()) {
                    break;
                }

                processoID = _processosID.front();
                _processosID.pop();
            }

            Processo processo;
            bool isProcesso = false;

            visit([&processo, &isProcesso](auto &&value) {
                if constexpr (is_same_v<decay_t<decltype(value)>, Processo>) {
                    processo = value;
                    isProcesso = true;
                } else {
                    cout << "Não é um processo válido!" << endl;
                }
            }, _memoryRAM.getProcesso(processoID));

            if (isProcesso) {
                lock_guard<mutex> lock(_mutexFilaPrincipal);
                if (getTipoExibicao()) {
                    cout << "[Core " << coreID << "] Processando ID: " << processoID << endl;
                }

                _coreAtivo = coreID;
                processamento(processo);

                if (processo.getCicloVida() != PRONTO) {
                    _escalonador.selecao(getPolitica(), processo, _processosAtivos);
                }
            }
        }
    } while (_processosAtivos > 0);

    if (getTipoExibicao()) {
        cout << "[Core " << coreID << "] concluiu processamento." << endl;
    }
}

void CPU::processamento(Processo &processo) {
    int contQuantum = 0;

    if (processo.getCicloVida() == BLOQUEADO) {
        queue<pair<int, int>> reg = processo._pcb.getRegistradores();
        atualizarRegistradores(reg);
        processo.setCicloVida(EXECUTANDO);

        while (true) {
            if (getPolitica() != FCFS) {
                if (contQuantum >= QUANTUM_CPU) {
                    break;
                }
                contQuantum += processo._pcb.getQuantum();
            }
            if (getTipoExibicao()) {
                cout << "[Processo ID]: " << processo._pcb.getId() << endl;
            } else {
                auto tempoAtual = processo._pcb.getTempoAtual();
                cout << processo._pcb.getId() << " | " << _coreAtivo << " | " << tempoAtual << "  | " << processo._pcb.getInstrucao() << endl;
            }

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
        auto res = select(valores[0], valores[1], valores[2], getTipoExibicao());
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

void CPU::setPolitica(TipoPolitica politica) {
    _politica = politica;
}

TipoPolitica CPU::getPolitica() {
    return _politica;
}


void CPU::setTipoExibicao(bool tipo) {
    _tipoExibicao = tipo;
}

bool CPU::getTipoExibicao() {
    return _tipoExibicao;
}