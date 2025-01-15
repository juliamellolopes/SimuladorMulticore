#include "../include/scheduler/escalonador.h"

void Escalonador::selecao(TipoPolitica politica, Processo &processo, int &processosAtivos) {
    switch (politica) {
    case FCFS:

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