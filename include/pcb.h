/**
 * @file pcb.h
 * @brief Declaração da classe PCB (Process Control Block), que armazena informações sobre processos.
 *
 * A classe PCB contém informações como ID, instruções, estado, registradores, e prioridade do processo.
 * É utilizada pela CPU e escalonadores para gerenciar a execução de processos.
 */

#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <random>
#include <bitset>

using namespace std;

#define QUANTUM_P 10

enum TipoPrioridade {
    BAIXA,
    MEDIA,
    ALTA
};
class PCB {
private:
    int _quantum;
    vector<string> _instrucoes;
    int _limiteAlocacao;

    int _id;
    int _estadoAtual;
    TipoPrioridade _prioridade;
    queue<pair<int, int>> _dadosRegistradores;
    string _enderecoBase;

public:
    PCB() :
        _quantum(QUANTUM_P),
        _estadoAtual(0),
        _prioridade(gerarPrioridadeAleatoria()) {}
    ~PCB() {}

    string getInstrucao();
    string getEnderecoBase();
    int getId();
    int getQuantum();
    int getSizeIntrucoes();
    int getTempoAtual();
    int getTempoAtual() const;
    int getTempoTotal();
    bool checkEstadoFinalizado();
    TipoPrioridade getPrioridade();
    queue<pair<int, int>> getRegistradores();
    void setId(int id);
    void incrementeEstado();
    void setLimite(int limite);
    void setEnderecoBase(string endereco);
    void setInstrucoes(vector<string> caminho);
    void inserirRegistrador(int index, int value);
    TipoPrioridade gerarPrioridadeAleatoria();

    string getIdBinario() const;
};