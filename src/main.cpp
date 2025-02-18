#include <iostream>

#include "../include/cpu.h"

using namespace std;

// void exibirMenu() {
//     cout << "=============================" << endl;
//     cout << "       MENU DE OPÇÕES        " << endl;
//     cout << "=============================" << endl;
//     cout << "1. FCFS (First-Come, First-Served)" << endl;
//     cout << "2. Round Robin (RR)" << endl;
//     cout << "3. Prioridade" << endl;
//     cout << "4. SJF" << endl;
//     cout << "=============================" << endl;
//     cout << "Escolha uma opção de escalonamento: ";
// }

// int main() {
//     int escolha;
//     bool detalhado;

//     exibirMenu();
//     cin >> escolha;

//     while (escolha < 1 || escolha > 4) {
//         cout << "Opção inválida. Tente novamente: ";
//         cin >> escolha;
//     }

//     cout << "Deseja visualizar o sistema detalhadamente? (1 = Sim, 0 = Não): ";
//     cin >> detalhado;

//     CPU cpu(detalhado);

//     switch (escolha) {
//     case 1:
//         cpu.setPolitica(FCFS);
//         cout << "Política de escalonamento configurada para FCFS." << endl << endl;
//         break;
//     case 2:
//         cpu.setPolitica(RR);
//         cout << "Política de escalonamento configurada para Round Robin." << endl << endl;
//         break;
//     case 3:
//         cpu.setPolitica(PRIORIDADE);
//         cout << "Política de escalonamento configurada para Prioridade." << endl << endl;
//         break;
//     case 4:
//         cpu.setPolitica(ESJF);
//         cout << "Política de escalonamento configurada para SJF." << endl << endl;
//         break;
//     }

//     cpu.inicializar();

//     return 0;
// }

int main() {
    CPU cpu(1);
    cpu.setPolitica(ESJF);
    cpu.inicializar();
    return 0;
}
