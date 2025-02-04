#include "../include/memory/ram.h"

/**
 * @brief Construtor que inicializa a memória principal carregando instruções de um arquivo de texto.
 *
 * O arquivo de entrada deve conter uma instrução por linha, que será lida e armazenada no vetor `_instrucoes`.
 * Se o arquivo não for encontrado ou não puder ser aberto, o programa exibirá uma mensagem de erro e será encerrado.
 *
 * @param path Caminho do arquivo de texto contendo as instruções a serem carregadas na memória.
 */
MemoryRAM::MemoryRAM(string path, bool tipo) {
    _tipoExibicao = tipo;

    for (size_t i = 0; i < TAM_CELL; i++) {
        ostringstream hexStream;
        hexStream << hex << uppercase << i;

        string hexValue = hexStream.str();
        _memoria[hexValue] = monostate{};
    }


    string linha;
    vector<string> instrucoesAtual;

    for (int i = 0; i < TAM_INSTRUCTIONS; i++) {
        ifstream instrFile(path + to_string(i + 1) + ".txt");

        if (instrFile.is_open()) {

            while (getline(instrFile, linha)) {
                instrucoesAtual.push_back(linha);
            }

        } else {
            cerr << "Erro ao abrir o arquivo de instruções." << endl;
            exit(EXIT_FAILURE);
        }

        if (_tipoExibicao) {
            cout << "Instrucoes " << i + 1 << " carregadas!" << endl;
        }

        _instrucoes.push_back(instrucoesAtual);
        instrucoesAtual.clear();
    }

    cout << endl;

    if (_instrucoes.size() > 0) {
        _instrucaoAtual = 0;
    } else {
        cout << "Quantidade de instruções insuficientes." << endl;
        exit(EXIT_SUCCESS);
    }
}

/**
 * @brief Retorna a instrução armazenada em um endereço específico da memória.
 *
 * @param endereco Endereço de memória.
 * @return Instrução armazenada no endereço.
 */
string MemoryRAM::getInstrucao(int endereco) {
    return _instrucoes[_instrucaoAtual].at(endereco);
}

/**
 * @brief Retorna o número total de instruções carregadas na memória.
 *
 * Esta função é útil para saber quantas instruções foram carregadas no vetor `_instrucoes` a partir do
 * arquivo de entrada, permitindo o controle do ciclo de execução no pipeline.
 *
 * @return O número total de instruções carregadas.
 */
size_t MemoryRAM::getSize() {
    return _instrucoes[_instrucaoAtual].size();
}

/**
 * @brief Retorna o índice da instrução atual.
 *
 * @return O índice da instrução atual.
 */
size_t MemoryRAM::getInstrucaoAtual() {
    return _instrucaoAtual + 1;
}

/**
 * @brief Incrementa o índice da instrução atual em execução.
 */
void MemoryRAM::incrementaInstrucao() {
    _instrucaoAtual++;
}

/**
 * @brief Recupera o processo armazenado em um endereço específico da memória.
 *
 * @param endereco O endereço de memória onde o processo está armazenado.
 * @return O processo armazenado no endereço especificado.
 */
MemoryCell MemoryRAM::getProcesso(string endereco) {
    return _memoria[endereco];
}

/**
 * @brief Armazena um valor em um endereço específico da memória principal (RAM).
 *
 * Esta função simula a escrita na memória principal, permitindo que valores sejam
 * associados a endereços específicos. Também exibe uma mensagem de confirmação
 * com o valor armazenado e o endereço.
 *
 * @param endereco O endereço de memória onde o valor será armazenado.
 * @param valor O valor a ser armazenado no endereço especificado.
 */
void MemoryRAM::escrever(int endereco, const MemoryCell valor) {
    ostringstream hexStream;
    hexStream << hex << uppercase << endereco;
    string hexValue = hexStream.str();

    if (!holds_alternative<monostate>(valor)) {
        if (holds_alternative<string>(valor)) {
            _memoria["3E" + hexValue] = valor;
        } else {
            _memoria[hexValue] = valor;
        }

        cout << "      -> Armazenado na RAM [" << hexValue << "]: ";
        visit([](auto &&cellValue) {
            if constexpr (is_same_v<decay_t<decltype(cellValue)>, int>) {
                cout << cellValue;
            } else if constexpr (is_same_v<decay_t<decltype(cellValue)>, string>) {
                cout << cellValue;
            } else {
                cout << "Tipo não tratado";
            }
        }, valor);
        cout << endl;
    } else {
        cout << "teste" << endl;
    }
}


/**
 * @brief Armazena um processo em um endereço específico da memória principal.
 *
 * @param endereco O endereço de memória onde o processo será armazenado.
 * @param processo O processo a ser armazenado.
 */
void MemoryRAM::guardarProcesso(string endereco, Processo &processo) {
    _memoria[endereco] = processo;
}

void MemoryRAM::mostrarDados() {
    cout << endl;
    for (const auto &[key, value] : _memoria) {
        visit([&key](auto &&cellValue) {
            using T = decay_t<decltype(cellValue)>;
            if constexpr (!is_same_v<T, monostate>) {
                cout << "Memory[" << key << "]: ";
                if constexpr (is_same_v<T, int>) {
                    cout << cellValue;
                } else  if constexpr (is_same_v<T, string>) {
                    cout << cellValue;
                } else if constexpr (is_same_v<decay_t<decltype(cellValue)>, Processo>) {
                    Processo processo = cellValue;
                    cout << "Processo ID: " << processo._pcb.getId();
                } else {
                    cout << "Valor não tratado";
                }
                cout << endl;
            }
        }, value);
    }
}

unordered_map<string, variant<int, string>> MemoryRAM::obterTodos() {
    unordered_map<string, variant<int, string>> resultado;

    for (const auto &[endereco, valor] : _memoria) {
        visit([&](auto &&cellValue) {
            using T = decay_t<decltype(cellValue)>;
            if constexpr (is_same_v<T, int> || is_same_v<T, string>) {
                resultado[endereco] = cellValue;
            }
        }, valor);
    }

    return resultado;
}