#ifndef ARQUIVO_H
#define	ARQUIVO_H

#include <iostream>
#include <fstream>

class Arquivo {
private:
    fstream arq;
    Registro reg;
    const int tam = 11;
    int elem = 0;
    void contElem();
    void inicArq();

public:
    Arquivo();
    ~Arquivo();
    void inserir(Registro reg);
    Registro buscar(int chave);
    Registro remover(int chave);
};

#endif

