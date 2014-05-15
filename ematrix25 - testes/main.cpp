#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Arquivo.h"
#include "Registro.h"

using namespace std;

Registro ler(Registro reg) {
    string aux;
    cout << "Digite a chave: ";
    cin >> aux;
    reg.setChave(aux);
    cout << "Digite o dado: ";
    cin >> aux;
    reg.setDado(aux);
    return reg;
}

int main() {
    Registro reg;
    Arquivo arq;
    arq.inserir(ler(reg));
    reg = arq.buscar();
    cout << reg.getChave() << " " << reg.getDado() << endl;
    return 0;
}

