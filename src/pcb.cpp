#include "../include/pcb.h"

/**
 * @brief Define as instruções do processo a partir de um vetor de strings.
 *
 * @param caminho Vetor contendo as instruções do processo.
 */
void PCB::setInstrucoes(vector<string> caminho) {
    _instrucoes = caminho;
}

/**
 * @brief Obtém a instrução atual com base no estado do processo.
 *
 * @return A instrução atual.
 */
string PCB::getInstrucao() {
    return _instrucoes[_estadoAtual];
}

/**
 * @brief Obtém o quantum do processo.
 *
 * @return O valor do quantum.
 */
int PCB::getQuantum() {
    return _quantum;
}

/**
 * @brief Define o limite de alocação de memória para o processo.
 *
 * @param limite Limite de alocação em unidades de memória.
 */
void PCB::setLimite(int limite) {
    _limiteAlocacao = limite;
}

/**
 * @brief Define o endereço base do processo na memória.
 *
 * @param endereco O endereço base.
 */
void PCB::setEnderecoBase(string endereco) {
    _enderecoBase.assign(endereco);
}

/**
 * @brief Obtém o endereço base do processo na memória.
 *
 * @return O endereço base.
 */
string PCB::getEnderecoBase() {
    return _enderecoBase;
}

/**
 * @brief Define o ID único do processo.
 *
 * @param id O identificador do processo.
 */
void PCB::setId(int id) {
    _id = id;
}

/**
 * @brief Obtém o ID único do processo.
 *
 * @return O identificador do processo.
 */
int PCB::getId() {
    return _id;
}

/**
 * @brief Incrementa o estado atual do processo para avançar na execução.
 */
void PCB::incrementeEstado() {
    _estadoAtual++;
}

/**
 * @brief Obtém o número total de instruções no processo.
 *
 * @return O número total de instruções.
 */
int PCB::getSizeIntrucoes() {
    return _instrucoes.size();
}

/**
 * @brief Verifica se o estado atual do processo indica que ele foi concluído.
 *
 * @return True se concluído, False caso contrário.
 */
bool PCB::checkEstadoFinalizado() {
    return _estadoAtual == getSizeIntrucoes();
}

/**
 * @brief Insere um valor em um registrador específico do processo.
 *
 * @param index Índice do registrador.
 * @param value Valor a ser armazenado no registrador.
 */
void PCB::inserirRegistrador(int index, int value) {
    _dadosRegistradores.push({ index, value });
}

/**
 * @brief Obtém a prioridade do processo.
 *
 * @return A prioridade do processo (BAIXA, MÉDIA, ALTA).
 */
queue<pair<int, int>> PCB::getRegistradores() {
    return _dadosRegistradores;
}

/**
 * @brief Obtém a prioridade do processo.
 *
 * @return A prioridade do processo (BAIXA, MÉDIA, ALTA).
 */
TipoPrioridade PCB::getPrioridade() {
    return _prioridade;
}

/**
 * @brief Gera uma prioridade aleatória para o processo.
 *
 * @return A prioridade gerada aleatoriamente (BAIXA, MÉDIA, ALTA).
 */
TipoPrioridade PCB::gerarPrioridadeAleatoria() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(BAIXA, ALTA);

    return static_cast<TipoPrioridade>(distrib(gen));
}

/**
 * @brief Calcula o tempo atual do processo com base no estado atual.
 *
 * @return O tempo atual do processo.
 */
int PCB::getTempoAtual() {
    return (_estadoAtual + 1) * QUANTUM_P - getTempoTotal();
}

int PCB::getTempoAtual() const {
    return (_estadoAtual + 1) * QUANTUM_P - _instrucoes.size() * QUANTUM_P;
}

/**
 * @brief Calcula o tempo total necessário para concluir o processo.
 *
 * @return O tempo total do processo.
 */
int PCB::getTempoTotal() {
    return getSizeIntrucoes() * QUANTUM_P;
}

string PCB::getIdBinario() const {
    return bitset<16>(_id).to_string();
}