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
    // vector<MemoryCell> _memoria;
    map<string,MemoryCell> _memoria;
    size_t _instrucaoAtual;

public:
    MemoryRAM() {}
    MemoryRAM(string path);
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