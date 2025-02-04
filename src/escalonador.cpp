#include "../include/scheduler/escalonador.h"

bool Escalonador::verificarReaproveitamento(const string &operacao, int &resultado) {
    for (const auto &[_, valor] : _memoryCache.obterTodos()) {
        if (holds_alternative<string>(valor)) {
            string instrucao = get<string>(valor);
            if (instrucao.find(operacao) != string::npos) {
                vector<string> tokens;
                stringstream ss(instrucao);
                string token;
                while (ss >> token) tokens.push_back(token);

                if (!tokens.empty()) {
                    resultado = stoi(tokens.back()); 
                }

                cout << "      -> Instrução já está na memória Cache: " << instrucao << endl;
                return true;
            }
        }
    }

    for (const auto &[_, valor] : _memoryRAM.obterTodos()) {
        if (holds_alternative<string>(valor)) {
            string instrucao = get<string>(valor);
            if (instrucao.find(operacao) != string::npos) {
                vector<string> tokens;
                stringstream ss(instrucao);
                string token;
                while (ss >> token) tokens.push_back(token);

                if (!tokens.empty()) {
                    resultado = stoi(tokens.back());  // Pega o último valor como resultado
                }

                cout << "      -> Instrução já está na memória RAM: " << instrucao << endl;
                return true;
            }
        }
    }

    return false; 
}

/**
 * @brief Seleciona o próximo processo a ser executado com base na política de escalonamento.
 *
 * @param politica A política de escalonamento em uso (FCFS, RR, ou PRIORIDADE).
 * @param processo Referência ao processo em execução.
 * @param processosAtivos Contagem de processos ativos no sistema.
 */
void Escalonador::selecao(TipoPolitica politica, Processo &processo, int &processosAtivos) {
    switch (politica) {
    case FCFS:
        //implemtada direto no cpu.cpp retirando somente a usabilidade de quantum 
        break;
    case RR:
        _rr.atualizarFila(processo._pcb.getEnderecoBase());
        break;
    case PRIORIDADE:
        _prioridade.gerenciarPrioridade(processo, processosAtivos);
        break;
    default:
        break;
    }
}