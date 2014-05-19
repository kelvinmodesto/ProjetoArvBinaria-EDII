#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

class Arv {
private:
    int tam, elem, arv[55];

    int hash(int chave) {
        return chave % tam;
    }

    int inc(int chave) {
        return (chave / tam) % tam;
    }
public:

    Arv() {
        tam = 11;
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
            if (arv[elem] >= tam)
                arv[elem] %= tam;
        }
        return arv[elem++];
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
        if (i % 2 == 0) {//NoPai do NoDir
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

    bool isProxNoDir() {
        return elem % 2 == 0;
    }
};

int regs[11], elem;

void inic() {
    elem = 0;
    for (int i = 0; i < 11; i++) {
        regs[i] = 0;
    }
}

void ins() {
    if (elem == 11) {
        cout << "O registro nao foi inserido" << endl;
        return;
    }
    int chave, aux;
    Arv arv;
    cout << "Inserir registro" << endl;
    cout << "Chave: ";
    cin >> chave;
    int pos = arv.calcPos(chave);
    if (regs[pos] <= 0) {
        regs[pos] = chave;
        elem++;
    } else {
        while (arv.temProx()) {
            if (arv.isProxNoDir()) {
                aux = arv.getNoPai(arv.getNoId());
                pos = arv.calcPos(regs[aux]);
                if (regs[pos] <= 0) {
                    regs[pos] = regs[aux];
                    regs[aux] = chave;
                    elem++;
                    break;
                }
            } else {
                pos = arv.calcPos(chave);
                if (regs[pos] <= 0) {
                    regs[pos] = chave;
                    elem++;
                    break;
                }
            }
        }
        if(arv.temProx()) {
            cout << "O registro foi inserido" << endl;
        } else {
            cout << "O registro nao foi inserido" << endl;
        }
    }
    cout << endl;
}

void exibReg(int reg, int pos) {
    cout << "Encontrou o registro " << reg;
    cout << " na posicao " << pos << endl;
}

void busc() {
    int chave;
    Arv arv;
    cout << "Buscar registro" << endl;
    cout << "Chave: ";
    cin >> chave;
    int pos = arv.calcPos(chave);
    if (regs[pos] == chave) {
        exibReg(regs[pos], pos);
    } else {
        while (arv.temProx()) {
            if (!arv.isProxNoDir()) {
                pos = arv.calcPos(chave);
                if (regs[pos] == chave) {
                    exibReg(regs[pos], pos);
                    break;
                }
            }
            arv.calcPos(chave);
        }
        if(!arv.temProx()) {
            cout << "O registro nao foi encontrado" << endl;
        }
    }
    cout << endl;
}

void rem() {
    int chave;
    Arv arv;
    cout << "Remover registro" << endl;
    cout << "Chave: ";
    cin >> chave;
    int pos = arv.calcPos(chave);
    if (regs[pos] == chave) {
	        regs[pos] = -1;
			elem--;
    } else {
        while (arv.temProx()) {
            if (!arv.isProxNoDir()) {
                pos = arv.calcPos(chave);
                if (regs[pos] == chave) {
                    regs[pos] = -1;
					elem--;
                    break;
                }
            }
            arv.calcPos(chave);
        }
        if(arv.temProx()) {
            cout << "O registro foi removido" << endl;
        } else {
            cout << "O registro nao foi encontrado" << endl;
        }
    }
    cout << endl;
}

void exib() {
    cout << "Exibir registros" << endl;
    for (int i = 0; i < 11; i++) {
        cout << "Reg[" << i << "] = ";
        cout << regs[i] << endl;
    }
    cout << endl;
}

int sair() {
    cin.ignore();
    cin.get();
    return 0;
}

int main() {
    int op;
    inic();
    while (true) {
        cout << "Manipulador de registros" << endl;
        cout << "1 - Inserir um registro" << endl;
        cout << "2 - Buscar um registro" << endl;
        cout << "3 - Remover um registro" << endl;
        cout << "4 - Exibir todos os registros" << endl;
        cout << "5 - Sair do manipulador" << endl;
        cout << "Escolha a opcao: ";
        cin >> op;
        cout << endl;
        switch (op) {
            case 1: ins();break;
            case 2: busc();break;
            case 3: rem();break;
            case 4: exib();break;
            case 5: return 0;
            default: cout << "Opcao invalida" << endl;
        }
    }
}