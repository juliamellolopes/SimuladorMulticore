#include "../include/cpu.h"

/**
 * @brief Inicializa os atributos principais da CPU, como os núcleos e o contador de programa.
 */
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

/**
 * @brief Inicializa a simulação, carregando processos na memória e configurando as threads.
 */
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

/**
 * @brief Inicializa as threads responsáveis pelo processamento de cada núcleo.
 */
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

/**
 * @brief Processa tarefas atribuídas a um núcleo específico.
 *
 * @param coreID Identificador do núcleo que será processado.
 */
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

/**
 * @brief Realiza o processamento de um processo no núcleo ativo.
 *
 * @param processo Referência ao processo a ser processado.
 */
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

/**
 * @brief Executa o pipeline para processar uma instrução.
 *
 * A função realiza as etapas do pipeline: busca da instrução, decodificação, execução
 * e armazenamento do resultado. Antes de executar, verifica se a instrução já foi processada
 * e está armazenada na Cache ou na RAM. Caso positivo, reutiliza o resultado e evita o processamento.
 *
 * @param instrucao A instrução a ser executada.
 */
void CPU::executePipeline(const string &instrucao) {
    _pipeline.InstructionFetch(instrucao);
    auto code = _pipeline.InstructionDecode();
    int aux = 0;

    if (!code.empty()) {
        auto valores = _pipeline.Execute(code);

        string instrucaoFormatada = code + " " + to_string(valores[1]) + " " + to_string(valores[2]);
        int resultado;

        if (_escalonador.verificarReaproveitamento(instrucaoFormatada, resultado)) {
            if (_tipoExibicao) {
                cout << "      -> Instrução já processada anteriormente. Resultado: " << resultado << endl;
            }
            _pipeline.escreverRegistrador(_cores[_coreAtivo]._regDest, resultado);
            return;
        }

        auto res = select(valores[0], valores[1], valores[2], getTipoExibicao());
        _pipeline.escreverRegistrador(_cores[_coreAtivo]._regDest, res);

        if (code != "STORE" && code != "LOAD") {
            string instrucaoFormatada = code + " " + to_string(valores[1]) + " " + to_string(valores[2]) + " " + to_string(res);
            _memoryCache.escreverNaCache(aux, instrucaoFormatada);
        }
    }
}

/**
 * @brief Atualiza os valores nos registradores do núcleo ativo.
 *
 * @param registradores Fila contendo pares de índice e valores para os registradores.
 */
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

/**
 * @brief Define a política de escalonamento utilizada pela CPU.
 *
 * @param politica A política de escalonamento (FCFS, RR, ou PRIORIDADE).
 */
void CPU::setPolitica(TipoPolitica politica) {
    _politica = politica;
}

/**
 * @brief Retorna a política de escalonamento atual da CPU.
 *
 * @return A política de escalonamento definida.
 */
TipoPolitica CPU::getPolitica() {
    return _politica;
}

/**
 * @brief Define o modo de exibição do sistema (detalhado ou resumido).
 *
 * @param tipo True para detalhado, False para resumido.
 */
void CPU::setTipoExibicao(bool tipo) {
    _tipoExibicao = tipo;
}

/**
 * @brief Obtém o modo de exibição configurado.
 *
 * @return True se detalhado, False se resumido.
 */
bool CPU::getTipoExibicao() {
    return _tipoExibicao;
}