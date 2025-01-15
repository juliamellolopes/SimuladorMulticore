// #include <iostream>

// using namespace std;

// #include "../include/cpu.h"

// int main() {

//     // menu

//     /*
//     opção de cada politica de escalonamento e se vc quer ver o sistema detalhadamente(CPU cpu(truw);) ou resumidamento(false)
//     */
//     CPU cpu(false);

//     cpu.setPolitica(FCFS);
//     // cpu.setPolitica(RR);
//     // cpu.setPolitica(PRIORIDADE);
//     cpu.inicializar();

//     return 0;
// }

#include <iostream>
#include "../include/cpu.h"

using namespace std;

void exibirMenu() {
    cout << "=============================" << endl;
    cout << "       MENU DE OPÇÕES        " << endl;
    cout << "=============================" << endl;
    cout << "1. FCFS (First-Come, First-Served)" << endl;
    cout << "2. Round Robin (RR)" << endl;
    cout << "3. Prioridade" << endl;
    cout << "=============================" << endl;
    cout << "Escolha uma opção de escalonamento: ";
}

int main() {
    int escolha;
    bool detalhado;

    exibirMenu();
    cin >> escolha;

    while (escolha < 1 || escolha > 3) {
        cout << "Opção inválida. Tente novamente: ";
        cin >> escolha;
    }

    cout << "Deseja visualizar o sistema detalhadamente? (1 = Sim, 0 = Não): ";
    cin >> detalhado;

    CPU cpu(detalhado);

    switch (escolha) {
    case 1:
        cpu.setPolitica(FCFS);
        cout << "Política de escalonamento configurada para FCFS." << endl;
        break;
    case 2:
        cpu.setPolitica(RR);
        cout << "Política de escalonamento configurada para Round Robin." << endl;
        break;
    case 3:
        cpu.setPolitica(PRIORIDADE);
        cout << "Política de escalonamento configurada para Prioridade." << endl;
        break;
    }

    cpu.inicializar();

    return 0;
}
