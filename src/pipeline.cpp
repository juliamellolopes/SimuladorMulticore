#include "../include/pipeline.h"

/**
 * @brief Divide uma instrução em tokens com base em um delimitador (' ').
 *
 * Esta função é utilizada para separar uma instrução em partes, como o opcode e os operandos,
 * retornando um vetor de strings. Cada token representa uma parte da instrução (ex.: "ADD R1 R2").
 *
 * @param instrucao A instrução a ser tokenizada.
 * @return Um vetor de strings, onde cada elemento é um token extraído da instrução.
 */
vector<string> Pipeline::tokenizar(string &instrucao) {
    char del = ' ';

    stringstream sstream(instrucao);
    string token;
    vector<string>tokens;

    while (getline(sstream, token, del))
        tokens.push_back(token);

    return tokens;
}

/**
 * @brief Lê o valor de um registrador específico do núcleo ativo.
 *
 * @param reg Índice do registrador a ser lido.
 * @return Valor armazenado no registrador.
 */

int Pipeline::lerRegistrador(int reg) {
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
void Pipeline::escreverRegistrador(int reg, int valor) {
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
void Pipeline::escreverNaMemoria(int endereco) {
    int valor = lerRegistrador(_cores[_coreAtivo]._reg1);
    _memoryCache.escrever(endereco, valor);
}


/**
 * @brief Realiza a busca da instrução atual na memória principal.
 *
 * Incrementa o contador de programa (PC) após a busca.
 */
void Pipeline::InstructionFetch() {
    cout << "[IF ] ";
    cout << "Buscando instrucao...\n";
    _instrucaoAtual.assign(_memoryRAM.getInstrucao(_PC));
}

/**
 * @brief Converte o nome de um registrador (como R1) em seu índice numérico.
 *
 * Esta função verifica se o nome do registrador começa com a letra 'R' e, em caso positivo,
 * converte o número subsequente em um inteiro que representa o índice do registrador.
 * Se o nome do registrador for inválido, uma mensagem de erro será exibida e o programa será encerrado.
 *
 * @param reg Nome do registrador (ex.: "R1").
 * @return O índice numérico correspondente ao registrador.
 * @throws Termina a execução se o nome do registrador for inválido.
 */
int obterIndiceRegistrador(const string &reg) {
    if (reg[0] == 'R') {
        return stoi(reg.substr(1));      
    }
    cerr << "Erro: Registrador inválido " << reg << endl;
    exit(EXIT_FAILURE);
}

/**
 * @brief Decodifica a instrução atual e identifica os registradores e o opcode.
 */
string Pipeline::InstructionDecode() {
    cout << "[ID ] ";

    cout << "Decodificando: " << _instrucaoAtual << endl;

    auto tokens = tokenizar(_instrucaoAtual);
    _opcode = tokens[0];

    if (_opcode.compare("LOAD") == 0) {

        _cores[_coreAtivo]._reg1 = obterIndiceRegistrador(tokens[1]);
        auto valor = stoi(tokens[2]);

        escreverRegistrador(_cores[_coreAtivo]._reg1, valor);

    } else if (_opcode.compare("STORE") == 0) {
        auto endereco = stoi(tokens[2]);
        _cores[_coreAtivo]._reg1 = obterIndiceRegistrador(tokens[1]);

        escreverNaMemoria(endereco);

    } else if (_opcode.compare("IF") == 0) {

        _cores[_coreAtivo]._reg1 = obterIndiceRegistrador(tokens[1]);
        _cores[_coreAtivo]._reg2 = obterIndiceRegistrador(tokens[3]);

        return tokens[2];

    } else {

        _cores[_coreAtivo]._regDest = obterIndiceRegistrador(tokens[1]);
        _cores[_coreAtivo]._reg1 = obterIndiceRegistrador(tokens[2]);
        _cores[_coreAtivo]._reg2 = obterIndiceRegistrador(tokens[3]);

        return _opcode;
    }

    return "";
}

/**
 * @brief Executa a operação correspondente ao opcode decodificado.
 *
 * @param code Código da operação (opcode).
 */
vector<int> Pipeline::Execute(string code) {
    cout << "[EX ] ";
    cout << "Chamando operações CPU " << endl;
    int valor0 = -1;
    int valor1 = lerRegistrador(_cores[_coreAtivo]._reg1);
    int valor2 = lerRegistrador(_cores[_coreAtivo]._reg2);

    if (code.compare("<") == 0) {
        valor0 = 4;
    } else if (code.compare(">") == 0) {
        valor0 = 5;
    } else if (code.compare("=") == 0) {
        valor0 = 6;
    } else if (code.compare("ADD") == 0) {
        valor0 = 0;
    } else if (code.compare("SUB") == 0) {
        valor0 = 1;
    } else if (code.compare("MULT") == 0) {
        valor0 = 2;
    } else if (code.compare("DIV") == 0) {
        valor0 = 3;
    } else {
        cerr << "Erro opcode nao encontrado." << endl;
        exit(EXIT_FAILURE);
    }

    return{ valor0, valor1, valor2 };
}