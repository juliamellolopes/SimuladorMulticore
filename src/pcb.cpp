#include "../include/pcb.h"

void PCB::setInstrucoes(vector<string> caminho) {
    _instrucoes = caminho;
}

string PCB::getInstrucao() {
    return _instrucoes[_estadoAtual];
}

int PCB::getQuantum() {
    return _quantum;
}

void PCB::setLimite(int limite) {
    _limiteAlocacao = limite;
}

void PCB::setEnderecoBase(string endereco) {
    _enderecoBase.assign(endereco);
}

string PCB::getEnderecoBase() {
    return _enderecoBase;
}

void PCB::setId(int id) {
    _id = id;
}

int PCB::getId() {
    return _id;
}

void PCB::incrementeEstado() {
    _estadoAtual++;
}

int PCB::getSizeIntrucoes() {
    return _instrucoes.size();
}

bool PCB::checkEstadoFinalizado() {
    return _estadoAtual == getSizeIntrucoes();
}

void PCB::inserirRegistrador(int index, int value) {
    _dadosRegistradores.push({ index, value });
}

queue<pair<int, int>> PCB::getRegistradores() {
    return _dadosRegistradores;
}

TipoPrioridade PCB::getPrioridade() {
    return _prioridade;
}

TipoPrioridade PCB::gerarPrioridadeAleatoria() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(BAIXA, ALTA);

    return static_cast<TipoPrioridade>(distrib(gen));
}


int PCB::getTempoAtual() {
    return (_estadoAtual + 1) * QUANTUM_P - getTempoTotal();
}

int PCB::getTempoTotal() {
    return getSizeIntrucoes() * QUANTUM_P;
}