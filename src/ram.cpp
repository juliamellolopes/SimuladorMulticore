#include "../include/memory/ram.h"

/**
 * @brief Construtor que inicializa a memória principal carregando instruções de um arquivo de texto.
 *
 * O arquivo de entrada deve conter uma instrução por linha, que será lida e armazenada no vetor `_instrucoes`.
 * Se o arquivo não for encontrado ou não puder ser aberto, o programa exibirá uma mensagem de erro e será encerrado.
 *
 * @param path Caminho do arquivo de texto contendo as instruções a serem carregadas na memória.
 */
MemoryRAM::MemoryRAM(string path) {

    // _memoria = vector<MemoryCell>(TAM_CELL, monostate{});
    for (size_t i = 0; i < TAM_CELL; i++) {
        ostringstream hexStream;
        hexStream << hex << uppercase << i;

        // Obtendo a string hexadecimal
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

        cout << "Instrucoes " << i + 1 << " carregadas!" << endl;

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

size_t MemoryRAM::getInstrucaoAtual() {
    return _instrucaoAtual + 1;
}

void MemoryRAM::incrementaInstrucao() {
    _instrucaoAtual++;
}

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
void MemoryRAM::escrever(int endereco, int valor) {
    // _memoria[endereco] = valor;
    ostringstream hexStream;
    hexStream << hex << uppercase << endereco;
    string hexValue = hexStream.str();
    _memoria[hexValue] = valor;
    cout << "      -> Valor " << valor << " foi armazenado no endereco " << endereco << endl;
}

void MemoryRAM::guardarProcesso(string endereco, Processo &processo) {
    _memoria[endereco] = processo;
}


void MemoryRAM::mostrarTodosDados() {
    // for (size_t i = 0; i < _memoria.size(); ++i) {
    //     cout << "Memory[" << i << "]: ";
        // visit([](auto &&value) {
        //     if constexpr (is_same_v<decay_t<decltype(value)>, monostate>) {
        //         cout << "null";
        //     } else {
        //         if constexpr (is_same_v<decay_t<decltype(value)>, int>) {
        //             cout << value;
        //         }
        //     }
        // }, _memoria[i]);
        // cout << endl;
    // }

    for (auto &[k, v] : _memoria) {
        cout << k << endl;
    }

}

void MemoryRAM::mostrarDados() {
    cout << endl;
    for (const auto &[key, value] : _memoria) {
        visit([&key](auto &&cellValue) {
            if constexpr (!is_same_v<decay_t<decltype(cellValue)>, monostate>) {
                if constexpr (is_same_v<decay_t<decltype(cellValue)>, int>) {
                    cout << "Memory[" << key << "]: " << cellValue << endl;
                } else if constexpr (is_same_v<decay_t<decltype(cellValue)>, Processo>) {
                    Processo processo = cellValue;
                    cout << "Memory[" << key << "]: Processo ID: " << processo._pcb.getId() << endl;
                } else {
                    cout << "Memory[" << key << "]: Não é do tipo tratado" << endl;
                }
            }
        }, value);
    }
}