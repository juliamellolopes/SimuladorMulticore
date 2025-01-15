#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <variant> 
#include <map>
#include <iomanip>

#include "processo.h"

#define TAM_INSTRUCTIONS 5
#define TAM_CELL 100

using namespace std;

using MemoryCell = variant<monostate, int, Processo>;

class MemoryRAM {
private:
    map<string, MemoryCell> _memoria;
    size_t _instrucaoAtual;
    bool _tipoExibicao;

public:
    MemoryRAM() {}
    MemoryRAM(string path, bool tipo);
    ~MemoryRAM() {}

    string getInstrucao(int endereco);
    size_t getSize();
    size_t getInstrucaoAtual();
    vector<vector<string>>_instrucoes;

    void incrementaInstrucao();
    void escrever(int endereco, int valor);
    void mostrarDados();
    void mostrarTodosDados();
    void guardarProcesso(string endereco, Processo &processo);
    MemoryCell getProcesso(string endereco);
};