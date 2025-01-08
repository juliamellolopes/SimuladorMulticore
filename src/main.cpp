#include <iostream>
#include "../include/pipeline.h"

using namespace std;


int main() {
    // Instancia MemoryRAM com o arquivo "instructions.txt" que contém as instruções para execução.
    MemoryRAM memory("instructions.txt");
    // Cria um objeto CPU, passando a memória instanciada.
    CPU cpu(memory);
    // Cria um objeto Pipeline, integrando-o com a memória e CPU.
    Pipeline pipeline(memory, cpu);

    return 0;
}
