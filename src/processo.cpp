#include "../include/processo.h"

Processo::Processo() {
    _cicloVida = BLOQUEADO;
}

/**
 * @brief Define o estado do ciclo de vida do processo.
 *
 * @param estado Novo estado a ser atribuído ao processo.
 */
void Processo::setCicloVida(TipoEstado estado) {
    _cicloVida = estado;
}

/**
 * @brief Obtém o estado atual do ciclo de vida do processo.
 *
 * @return O estado atual do processo.
 */
TipoEstado Processo::getCicloVida() {
    return _cicloVida;
}

/**
 * @brief Armazena os valores dos registradores no PCB do processo.
 *
 * @param registradores Vetor contendo os valores dos registradores.
 */
void Processo::dowloadRegistrador(const vector<int> &registradores) {
    for (size_t i = 0; i < registradores.size(); i++) {
        if (registradores[i] != 0) {
            _pcb.inserirRegistrador(i, registradores[i]);
        }
    }

}