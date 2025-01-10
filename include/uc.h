#pragma once

#include <iostream>

using namespace std;

#ifndef ULA_H   
#define ULA_H 
class ULA {
public:
    ULA() {}
    int operation(int var1, int var2, char var3);
private:
};

#endif
class UC {
private:
    ULA _ula;
public:
    UC() {}
    ~UC() {}

    int select(int opcode, int valor1, int valor2);
};
