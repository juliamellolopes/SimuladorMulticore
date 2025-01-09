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
 * @brief Inicializa o pipeline com referências para memória e CPU.
 *
 * Configura valores iniciais e inicia o loop de execução.
 */
Pipeline::Pipeline() {
    _instrucaoAtual.assign("");
    _opcode.assign("");

    _uc._cpu._cores[_uc._cpu._coreAtivo]._reg1 = _uc._cpu._cores[_uc._cpu._coreAtivo]._reg2 = _uc._cpu._cores[_uc._cpu._coreAtivo]._regDest = 0;

    for (int i = 0; i < TAM_INSTRUCTIONS; i++) {
        cout << "--- Inciando processo " << _uc._memory.instrucaoAtual + 1 << " ---" << endl << endl;
        InstructionLoop();
        cout << endl << "Instruções " << ++_uc._memory.instrucaoAtual << " finalizadas." << endl << endl;
    }

}

/**
 * @brief Controla o ciclo de execução do pipeline, processando todas as instruções.
 */
void Pipeline::InstructionLoop() {
    const int TAM_I = _uc._memory.getSize();      // tamanho de instruções 
    vector<bool> control(TAM_I, false);           // variavel de controle da utilização da instrução (true - usado, false - não usado)
    int cont = TAM_I;

    while (cont > 1) {

        if (control[_uc._cpu.getPC()] == false) {
            cont = TAM_I;
            control[_uc._cpu.getPC()] = true;
            InstructionFetch();

        } else {
            cont--;
        }
    }

}

/**
 * @brief Realiza a busca da instrução atual na memória principal.
 *
 * Incrementa o contador de programa (PC) após a busca.
 */
void Pipeline::InstructionFetch() {
    cout << "[IF ] ";
    cout << "Buscando instrucao...\n";
    _instrucaoAtual.assign(_uc._memory.getInstrucao(_uc._cpu.getPC()));

    // cout << endl;
    InstructionDecode();

    _uc._cpu.incrementaPC();
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
        return stoi(reg.substr(1));         // Converte o número após 'R' em um inteiro
    }
    cerr << "Erro: Registrador inválido " << reg << endl;
    exit(EXIT_FAILURE);
}

/**
 * @brief Decodifica a instrução atual e identifica os registradores e o opcode.
 */
void Pipeline::InstructionDecode() {
    cout << "[ID ] ";

    cout << "Decodificando: " << _instrucaoAtual << endl;

    auto tokens = tokenizar(_instrucaoAtual);
    _opcode = tokens[0];

    if (_opcode.compare("LOAD") == 0) {

        _uc._cpu._cores[_uc._cpu._coreAtivo]._reg1 = obterIndiceRegistrador(tokens[1]);
        auto valor = stoi(tokens[2]);

        _uc._cpu.escreverRegistrador(_uc._cpu._cores[_uc._cpu._coreAtivo]._reg1, valor);

    } else if (_opcode.compare("STORE") == 0) {
        auto endereco = stoi(tokens[2]);
        _uc._cpu._cores[_uc._cpu._coreAtivo]._reg1 = obterIndiceRegistrador(tokens[1]);

        _uc._cpu.escreverNaMemoria(endereco);

    } else if (_opcode.compare("IF") == 0) {

        _uc._cpu._cores[_uc._cpu._coreAtivo]._reg1 = obterIndiceRegistrador(tokens[1]);
        _uc._cpu._cores[_uc._cpu._coreAtivo]._reg2 = obterIndiceRegistrador(tokens[3]);

        Execute(tokens[2]);

    } else {

        _uc._cpu._cores[_uc._cpu._coreAtivo]._regDest = obterIndiceRegistrador(tokens[1]);
        _uc._cpu._cores[_uc._cpu._coreAtivo]._reg1 = obterIndiceRegistrador(tokens[2]);
        _uc._cpu._cores[_uc._cpu._coreAtivo]._reg2 = obterIndiceRegistrador(tokens[3]);

        Execute(_opcode);
    }
}

/**
 * @brief Executa a operação correspondente ao opcode decodificado.
 *
 * @param code Código da operação (opcode).
 */
void Pipeline::Execute(string code) {
    cout << "[EX ] ";
    cout << "Chamando operações CPU " << endl;

    if (code.compare("<") == 0) {
        _uc.select(4);
    } else if (code.compare(">") == 0) {
        _uc.select(5);
    } else if (code.compare("=") == 0) {
        _uc.select(6);
    } else if (code.compare("ADD") == 0) {
        _uc.select(0);
    } else if (code.compare("SUB") == 0) {
        _uc.select(1);
    } else if (code.compare("MULT") == 0) {
        _uc.select(2);
    } else if (code.compare("DIV") == 0) {
        _uc.select(3);
    } else {
        cerr << "Erro opcode nao encontrado." << endl;
        exit(EXIT_FAILURE);
    }
}