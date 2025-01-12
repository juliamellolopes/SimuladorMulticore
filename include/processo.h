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
