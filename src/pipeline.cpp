#include "../include/pipeline.h"

// Separa uma instrução em tokens com base em um delimitador (' '), retornando um vetor de strings.
vector<string> Pipeline::tokenizar(string &instrucao) {
    char del = ' ';

    stringstream sstream(instrucao);
    string token;
    vector<string>tokens;

    while (getline(sstream, token, del))
        tokens.push_back(token);

    return tokens;
}

// Inicializa o pipeline com referências para a memória e a CPU, ajustando valores iniciais e iniciando o loop de execução.
Pipeline::Pipeline() {
    _instrucaoAtual.assign("");
    _opcode.assign("");

    _uc._cpu._cores[_uc._cpu._coreAtivo]._reg1 = _uc._cpu._cores[_uc._cpu._coreAtivo]._reg2 = _uc._cpu._cores[_uc._cpu._coreAtivo]._regDest = 0;

    loop();
}

//  Controla o ciclo de execução de instruções. Itera até que todas as instruções na memória sejam executadas, chamando a etapa de busca (InstructionFetch) para instruções ainda não processadas.
void Pipeline::loop() {
    const int TAM_I = _uc._memory.getSize();   // tamanho de instruções 
    vector<bool> control(TAM_I, false);       // variavel de controle da utilização da instrução (true - usado, false - não usado)
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

// Executa a busca da instrução atual na memória e incrementa o contador de programa (PC). Passa a instrução para a próxima etapa, InstructionDecode.
void Pipeline::InstructionFetch() {
    cout << "\n--------- Pipeline Stage: Instruction Fetch ---------\n";
    cout << "Buscando instrucao..." << endl;
    _instrucaoAtual.assign(_uc._memory.getInstrucao(_uc._cpu.getPC()));

    InstructionDecode();

    _uc._cpu.incrementaPC();
}

// Converte um nome de registrador (como R1) em seu índice numérico. Exibe uma mensagem de erro caso o registrador seja inválido.
int obterIndiceRegistrador(const string &reg) {
    if (reg[0] == 'R') {
        return stoi(reg.substr(1)); // Converte o número após 'R' em um inteiro
    }
    cerr << "Erro: Registrador inválido " << reg << endl;
    exit(EXIT_FAILURE);
}

// Decodifica a instrução atual, identificando o opcode e os registradores envolvidos, utilizando a função auxiliar obterIndiceRegistrador para interpretar índices de registradores.
void Pipeline::InstructionDecode() {
    cout << "\n--------- Pipeline Stage: Instruction Decode ---------\n";

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

// Etapa de Execução
void Pipeline::Execute(string code) {
    cout << "\n--------- Pipeline Stage: Execution ---------\n";
    cout << "Chamando operações CPU" << endl;

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