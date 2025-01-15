#include <iostream>

using namespace std;

#include "../include/cpu.h"

int main() {

    CPU cpu;

    // cpu.setPolitica(FCFS);
    // cpu.setPolitica(RR);
    cpu.setPolitica(PRIORIDADE);

    cpu.inicializar();

    return 0;
}