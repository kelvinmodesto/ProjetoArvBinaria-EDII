#include <iostream>
#include <fstream>
#include <Arquivo.h>
#include <Registro.h>

using namespace std;

class Arquivo {
private:
    fstream arq;
    Registro reg;
    const int tam = 11;
    int elem = 0;

    void contElem() {
        while (arq.good()) {
            arq.read((char *) &reg, sizeof (reg));
            if (reg.getChave() > 0)
                elem++;
        }
    }

    void inicArq() {
        reg.setChave("0");
        reg.setDado("  ");
        for (int i = 0; i < tam; i++) {
            arq.write((char *) &reg, sizeof (reg));
        }
    }
public:

    Arquivo() {
        arq.open("registros.dat", ios::binary);
        if (arq) {
            contElem();
            if (elem == 0)
                inicArq();
            cout << "O arquivo foi aberto" << endl;
        } else {
            cerr << "O arquivo não foi aberto" << endl;
            delete this;
        }
    }

    ~Arquivo() {
        arq.close;
    }

    void inserir(Registro reg) {
        arq.clear();
        //Arvore.cpp obtem a pos da chave do Registro
        arq.seekp(0, ios::end);
        arq.write((char *) &reg, sizeof (reg));
    }

    Registro buscar(int chave) {
        arq.clear();
        //Arvore.cpp obtem a pos da chave
        arq.seekg(0);
        arq.read((char *) &reg, sizeof (reg));
        return reg;
    }

    Registro remover(int chave) {
        Registro aux;
        aux = buscar(chave);
        arq.clear();
        //Arvore.cpp obtem a pos da chave
        arq.seekp(0);
        reg.setChave("-1");
        reg.setDado("  ");
        arq.write((char *) &reg, sizeof (reg));
        return aux;
    }
};
