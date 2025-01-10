#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <variant> 

#define TAM_INSTRUCTIONS 5
#define TAM_CELL 100

using namespace std;

using MemoryCell = variant<monostate, int>;

class MemoryRAM {
private:
    vector<vector<string>>_instrucoes;
    vector<MemoryCell> _memoria;
    size_t _instrucaoAtual;

public:
    MemoryRAM() {}
    MemoryRAM(string path);
    ~MemoryRAM() {}

    string getInstrucao(int endereco);
    size_t getSize();
    size_t getInstrucaoAtual();

    void incrementaInstrucao();
    void escrever(int endereco, int valor);
    void mostrarDados();
    void mostrarTodosDados();
};