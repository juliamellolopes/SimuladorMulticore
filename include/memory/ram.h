/**
 * @file ram.h
 * @brief Declaração da classe MemoryRAM, que implementa uma memória principal simulada.
 *
 * A classe MemoryRAM gerencia a leitura e escrita de valores na memória principal.
 * Ela também carrega instruções de arquivos para simular um ambiente de execução.
 */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <variant> 
#include <map>
#include <iomanip>
#include <unordered_map>

#include "processo.h"

#define TAM_INSTRUCTIONS 5
#define TAM_CELL 100

using namespace std;

using MemoryCell = variant<monostate, int, string, Processo>;

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
    void escrever(int endereco, const MemoryCell valor);
    void mostrarDados();
    void guardarProcesso(string endereco, Processo &processo);
    MemoryCell getProcesso(string endereco);
    unordered_map<string, variant<int, string>> obterTodos();

};