#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>

#define TAM 11
#define NOME_ARQ "registros.dat"

using namespace std;

class Registro {
private:
    char chave[3];
    char dado[27];
public:

    Registro() {

    }

    Registro(string chave, string dado) {
        strncpy(this->chave, chave.c_str(), 2);
        chave[2] = '\0';
        strncpy(this->dado, dado.c_str(), 26);
        dado[26] = '\0';
    }

    void setChave(string chave) {
        strncpy(this->chave, chave.c_str(), 2);
        chave[2] = '\0';
    }

    void setDado(string dado) {
        strncpy(this->dado, dado.c_str(), 26);
        dado[26] = '\0';
    }

    int getIChave() {
        return atoi(chave);
    }

    string getChave() {
        return chave;
    }

    string getDado() {
        return dado;
    }
};

class Arvore {
private:
    int elem, arv[55];

    int hash(int chave) {
        return chave % TAM;
    }

    int inc(int chave) {
        return (chave / TAM) % TAM;
    }
public:

    Arvore() {
        elem = 0;
    }

    int calcPos(int chave) {
        if (elem == 0) {
            arv[elem] = hash(chave);
        } else {
            int aux = inc(chave);
            if (aux > 0)
                arv[elem] = getNoPai(elem) + aux;
            else
                arv[elem] = getNoPai(elem) + 1;
            if (arv[elem] >= TAM)
                arv[elem] %= TAM;
        }
        return arv[elem++];
    }

    int getRaiz() {
        return arv[0];
    }

    int getNo(int i) {
        return arv[i];
    }

    int getNoDir(int i) {
        return arv[2 * i + 2];
    }

    int getNoEsq(int i) {
        return arv[2 * i + 1];
    }

    int getNoPai(int i) {
        if (isNoDir(i)) {//NoPai do NoDir
            return arv[(elem - 2) / 2];
        } else {//NoPai do NoEsq
            return arv[(elem - 1) / 2];
        }
    }

    int getNoId() {
        return elem - 1;
    }

    bool temProx() {
        return elem < 55;
    }

    bool isNoDir(int i) {
        return i % 2 == 0;
    }

    bool isProxNoDir() {
        return elem % 2 == 0;
    }
};

int elem;

void inic() {
    ofstream arq;
    arq.open(NOME_ARQ, ios::out | ios::binary);
    if (!arq) {
        cerr << "O arquivo nao foi aberto" << endl << endl;
        return;
    }
    Registro reg("0", "");
    for (int i = 0; i < TAM; i++) {
        arq.write((char*) &reg, sizeof (reg));
    }
    arq.close();
}

bool cont() {
    elem = 0;
    Registro reg;
    ifstream arq;
    arq.open(NOME_ARQ, ios::in | ios::binary);
    if (!arq) {
        arq.close();
        inic();
        arq.open(NOME_ARQ, ios::in | ios::binary);
    }
    arq.seekg(0);
    while (!arq.eof()) {
        arq.read((char*) &reg, sizeof (reg));
        if (reg.getIChave() > 0)
            elem++;
    }
    arq.close();
}

Registro lerReg() {
    Registro reg;
    string aux;
    cout << "Digite a chave: ";
    cin >> aux;
    reg.setChave(aux);
    cout << "Digite o dado: ";
    cin >> aux;
    reg.setDado(aux);
    return reg;
}

void ins() {
    if (elem == TAM) {
        cerr << "O registro nao pode ser inserido" << endl << endl;
        return;
    }
    fstream arq;
    arq.open(NOME_ARQ, ios::in | ios::out | ios::binary);
    if (!arq) {
        cerr << "O arquivo nao foi aberto" << endl << endl;
        return;
    }
    cout << "Inserir registro" << endl;
    Arvore arv;
    int pos, aux;
    Registro regNovo, regAtual;
    regNovo = lerReg();
    pos = arv.calcPos(regNovo.getIChave());
    arq.seekg(pos * sizeof (regAtual));
    arq.read((char*) &regAtual, sizeof (regAtual));
    if (regAtual.getIChave() <= 0) {
        arq.seekp(pos * sizeof (regNovo));
        arq.write((char*) &regNovo, sizeof (regNovo));
        elem++;
        cout << "O registro foi inserido" << endl;
    } else {
        Registro regAnt;
        while (arv.temProx()) {
            if (arv.isProxNoDir()) {
                aux = arv.getNoPai(arv.getNoId());
                arq.seekg(aux * sizeof (regAnt));
                arq.read((char*) &regAnt, sizeof (regAnt));
                pos = arv.calcPos(regAnt.getIChave());
                arq.read((char*) &regAtual, sizeof (regAtual));
                if (regAtual.getIChave() <= 0) {
                    arq.seekp(pos * sizeof (regAnt));
                    arq.write((char*) &regAnt, sizeof (regAnt));
                    arq.seekp(aux * sizeof (regNovo));
                    arq.write((char*) &regNovo, sizeof (regNovo));
                    elem++;
                    break;
                }
            } else {
                pos = arv.calcPos(regNovo.getIChave());
                arq.seekg(pos * sizeof (regAtual));
                arq.read((char*) &regAtual, sizeof (regAtual));
                if (regAtual.getIChave() <= 0) {
                    arq.seekp(pos * sizeof (regNovo));
                    arq.write((char*) &regNovo, sizeof (regNovo));
                    elem++;
                    break;
                }
            }
        }
        if (arv.temProx()) {
            cout << "O registro foi inserido" << endl;
        } else {
            cout << "O registro nao foi inserido" << endl;
        }
    }
    arq.close();
    cout << endl;
}

int lerCh() {
    int aux;
    cout << "Digite a chave: ";
    cin >> aux;
    return aux;
}

void exibReg(Registro reg, int pos) {
    cout << "Encontrou o registro '" << reg.getDado();
    cout << "' na posicao " << pos << endl;
}

void busc() {
    ifstream arq;
    arq.open(NOME_ARQ, ios::in | ios::binary);
    if (!arq) {
        cerr << "O arquivo nao foi aberto" << endl << endl;
        return;
    }
    cout << "Buscar registro" << endl;
    Arvore arv;
    Registro regAtual;
    int chave = lerCh();
    int pos = arv.calcPos(chave);
    arq.seekg(pos * sizeof (regAtual));
    arq.read((char*) &regAtual, sizeof (regAtual));
    if (regAtual.getIChave() == chave) {
        exibReg(regAtual, pos);
    } else {
        while (arv.temProx()) {
            if (!arv.isProxNoDir()) {
                pos = arv.calcPos(chave);
                arq.seekg(pos * sizeof (regAtual));
                arq.read((char*) &regAtual, sizeof (regAtual));
                if (regAtual.getIChave() == chave) {
                    exibReg(regAtual, pos);
                    break;
                }
            }
            arv.calcPos(chave);
        }
        if (!arv.temProx()) {
            cout << "O registro nao foi encontrado" << endl;
        }
    }
    arq.close();
    cout << endl;
}

void rem() {
    fstream arq;
    arq.open(NOME_ARQ, ios::in | ios::out | ios::binary);
    if (!arq) {
        cerr << "O arquivo nao foi aberto" << endl << endl;
        return;
    }
    cout << "Remover registro" << endl;
    Arvore arv;
    Registro regNovo("-1", ""), regAtual;
    int chave = lerCh();
    int pos = arv.calcPos(chave);
    arq.seekg(pos * sizeof (regAtual));
    arq.read((char*) &regAtual, sizeof (regAtual));
    if (regAtual.getIChave() == chave) {
        arq.seekp(pos * sizeof (regNovo));
        arq.write((char*) &regNovo, sizeof (regNovo));
        elem--;
        cout << "Removeu o registro '" << regAtual.getDado();
        cout << "' na posicao " << pos << endl;
    } else {
        while (arv.temProx()) {
            if (!arv.isProxNoDir()) {
                pos = arv.calcPos(chave);
                arq.seekg(pos * sizeof (regAtual));
                arq.read((char*) &regAtual, sizeof (regAtual));
                if (regAtual.getIChave() == chave) {
                    arq.seekp(pos * sizeof (regNovo));
                    arq.write((char*) &regNovo, sizeof (regNovo));
                    elem--;
                    break;
                }
            }
            arv.calcPos(chave);
        }
        if (arv.temProx()) {
            cout << "Removeu o registro '" << regAtual.getDado();
            cout << "' na posicao " << pos << endl;
        } else {
            cout << "O registro nao foi encontrado" << endl;
        }
    }
    arq.close();
    cout << endl;
}

void exib() {
    ifstream arq;
    arq.open(NOME_ARQ, ios::in | ios::binary);
    if (!arq) {
        cerr << "O arquivo nao foi aberto" << endl << endl;
        return;
    }
    Registro reg;
    cout << "Exibir registros" << endl;
    arq.seekg(0);
    for (int i = 0; i < TAM; i++) {
        arq.read((char*) &reg, sizeof (reg));
        if (i < 10)
            cout << "Reg[0" << i << "] = ";
        else
            cout << "Reg[" << i << "] = ";
        cout << reg.getChave() << ", '";
        cout << reg.getDado() << "'" << endl;
    }
    arq.close();
    cout << endl;
}

int sair() {
    cin.ignore();
    cin.get();
    return 0;
}

int main() {
    int op = 0;
    cont();
    while (true) {
        cout << "Manipulador de registros" << endl;
        cout << "1 - Inserir um registro" << endl;
        cout << "2 - Buscar um registro" << endl;
        cout << "3 - Remover um registro" << endl;
        cout << "4 - Exibir todos os registros" << endl;
        cout << "5 - Sair do programa" << endl;
        cout << "Escolha uma opcao: ";
        cin >> op;
        cout << endl;
        switch (op) {
            case 1: ins();
                break;
            case 2: busc();
                break;
            case 3: rem();
                break;
            case 4: exib();
                break;
            case 5: return 0;
            default: cout << "Opcao invalida" << endl;
                break;
        }
    }
}