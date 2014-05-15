#ifndef ARVORE_H
#define	ARVORE_H

class Arvore {
private:
    int tam = 11;
    int regs[tam] = {0};
    int elem = 0;
    int hash(int chave);
    int inc(int chave);
public:
    Arvore();
    Arvore(int tam, int regs[], int elem);
    int inserir(int chave);
    int caminhar(int chave, int pos);
    int mover(int chave, int pos, int valor);
};

#endif

