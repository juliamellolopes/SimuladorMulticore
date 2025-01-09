#include "../include/memory.h"

/**
 * @brief Inicializa a memória principal carregando instruções de um arquivo.
 *
 * @param path Caminho do arquivo de texto contendo as instruções.
 */
MemoryCache::MemoryCache(MemoryRAM memoryRAM) {
    _memoryRAM = memoryRAM;
}

/**
 * @brief Armazena um valor em um endereço específico da memória principal.
 *
 * @param endereco Endereço de memória.
 * @param valor Valor a ser armazenado.
 */
void MemoryCache::escrever(int endereco, int valor) {
    cout << "Guadando informação na Cache..." << endl;
    _cache.push(make_pair(endereco, valor));

    if (_cache.size() >= TAM_CACHE) {
        cout << "[Cache cheia]... Guardando o primeiro valor na memoria RAM" << endl;
        memoriaCheia();
    }
}

/**
 * @brief Libera espaço na cache movendo o valor mais antigo para a memória principal.
 */
void MemoryCache::memoriaCheia() {
    auto retirar = _cache.front();

    _cache.pop();
    _memoryRAM.escrever(retirar.first, retirar.second);
}

/**
 * @brief Construtor que inicializa a memória principal carregando instruções de um arquivo de texto.
 *
 * O arquivo de entrada deve conter uma instrução por linha, que será lida e armazenada no vetor `_instrucoes`.
 * Se o arquivo não for encontrado ou não puder ser aberto, o programa exibirá uma mensagem de erro e será encerrado.
 *
 * @param path Caminho do arquivo de texto contendo as instruções a serem carregadas na memória.
 */
MemoryRAM::MemoryRAM(string path) {
    ifstream instrFile(path);
    string linha;

    if (instrFile.is_open()) {
        
        while (getline(instrFile, linha)) {
            _instrucoes.push_back(linha);
        }

    } else {
        cerr << "Erro ao abrir o arquivo de instruções." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Instrucoes carregadas!" << endl;
}

/**
 * @brief Retorna a instrução armazenada em um endereço específico da memória.
 *
 * @param endereco Endereço de memória.
 * @return Instrução armazenada no endereço.
 */
string MemoryRAM::getInstrucao(int endereco) {
    return _instrucoes.at(endereco);
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
    return _instrucoes.size();
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
    _memoria[endereco] = valor;
    cout << "Valor " << valor << " foi armazenado no endereco " << endereco << endl;
}