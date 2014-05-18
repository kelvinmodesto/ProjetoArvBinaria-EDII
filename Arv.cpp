#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

class Arv {
private:
    int tam, elem, arv[110];

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
        cout << "Calcular a Posicao de " << chave << endl;
        if (elem == 0) {
            arv[elem] = hash(chave);
            cout << "No[" << elem << "] = " << arv[elem] << endl;
        } else {
            int aux = inc(chave); 
            if(aux>0)
                arv[elem] = getNoPai(elem) + aux;
            else
                arv[elem] = getNoPai(elem) + 1;
            if (arv[elem] >= tam)
                arv[elem] %= tam;
            cout << "No[" << elem << "] = " << arv[elem] << endl;
        }
        cout << endl;
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

    bool isProxNoDir() {
        return elem % 2 == 0;
    }

    bool isNoRaiz() {
        return elem == 0;
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
    if (elem == 11)
        return;
    int chave, aux;
    Arv arv;
    cout << "Inserir registro" << endl;
    cout << "Chave: ";
    cin >> chave;
    cout << endl;
    int pos = arv.calcPos(chave);
    if (regs[pos] <= 0) {
        regs[pos] = chave;
    } else {
        while (!arv.isNoRaiz()) {
            if (arv.isProxNoDir()) {
                aux = arv.getNoPai(arv.getNoId());
                pos = arv.calcPos(regs[aux]);
                if (regs[pos] <= 0) {
                    regs[pos] = regs[aux];
                    regs[aux] = chave;
                    break;
                }
            } else {
                pos = arv.calcPos(chave);
                if (regs[pos] <= 0) {
                    regs[pos] = chave;
                    break;
                }
            }
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
        cout << "1 - Inserir o registro" << endl;
        cout << "2 - Exibir os registros" << endl;
        cout << "3 - Sair do manipulador" << endl;
        cout << "Escolha a opcao: ";
        cin >> op;
        cout << endl;
        switch (op) {
            case 1: ins();
                break;
            case 2: exib();
                break;
            case 3: return 0;
            default: cout << "Opcao invalida" << endl;
        }
    }
}