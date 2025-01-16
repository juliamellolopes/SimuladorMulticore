#include "../include/scheduler/escalonador.h"

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