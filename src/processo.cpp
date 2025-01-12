#include "../include/processo.h"

Processo::Processo() {
    _cicloVida = BLOQUEADO;
}

void Processo::setCicloVida(TipoEstado estado) {
    _cicloVida = estado;
}

TipoEstado Processo::getCicloVida() {
    return _cicloVida;
}

void Processo::dowloadRegistrador(const vector<int> &registradores) {
    for (size_t i = 0; i < registradores.size(); i++) {
        if (registradores[i] != 0) {
            _pcb.inserirRegistrador(i, registradores[i]);
        }
    }

}