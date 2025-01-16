/**
 * @file prioridade.h
 * @brief Declaração da classe Prioridade, que implementa o algoritmo de escalonamento baseado em prioridades.
 *
 * O algoritmo de Prioridade organiza processos em filas de alta, média e baixa prioridade, garantindo
 * que processos críticos sejam executados antes dos demais.
 */

#pragma once

#include "processo.h"

using namespace std;

class Prioridade {
private:
    queue<string> _filaAuxiliarMedia;
    queue<string> _filaAuxiliarBaixa;
    queue<string> _filaAuxiliarAlta;
    queue<string> &_processosID;

public:

    Prioridade(queue<string> &processosID) :
        _processosID(processosID) {}
    ~Prioridade() {}

    void gerenciarPrioridade(Processo &processo, int &processosAtivos) {
        if (processo._pcb.getPrioridade() == BAIXA) {
            _filaAuxiliarBaixa.push(processo._pcb.getEnderecoBase());
        } else if (processo._pcb.getPrioridade() == ALTA) {
            _filaAuxiliarAlta.push(processo._pcb.getEnderecoBase());
        } else {
            _filaAuxiliarMedia.push(processo._pcb.getEnderecoBase());
        }

        processosAtivos++;
    }

    void organizarFila() {
        atualizarFila(_filaAuxiliarAlta);
        atualizarFila(_filaAuxiliarMedia);
        atualizarFila(_filaAuxiliarBaixa);
    }

    void atualizarFila(queue<string> &fila) {
        while (!fila.empty()) {
            auto endereco = fila.front();
            _processosID.push(endereco);
            fila.pop();
        }
    }

};