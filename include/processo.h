/**
 * @file processo.h
 * @brief Declaração da classe Processo, que encapsula o estado e o PCB de um processo.
 *
 * A classe Processo gerencia o ciclo de vida de um processo, incluindo estados como PRONTO,
 * BLOQUEADO e EXECUTANDO. Também encapsula o PCB associado ao processo.
 */

#pragma once

#include "pcb.h"

enum TipoEstado {
    PRONTO,
    BLOQUEADO,
    EXECUTANDO
};

class Processo {
private:
    TipoEstado _cicloVida;
public:
    Processo();
    ~Processo() {}
    PCB _pcb;

    TipoEstado getCicloVida();
    void dowloadRegistrador(const vector<int> &registradores);
    void setCicloVida(TipoEstado estado);
};
