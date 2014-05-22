#include <cstdlib>
#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

#define TAM TAM

class Arv {
private:
    int elem, arv[TAM * 10];

    int hash(int chave) {
        return chave % TAM;
    }

    int inc(int chave) {
        return (chave / TAM) % TAM;
    }
public:

    Arv() {
        elem = 0;
    }

    int calcPos(int chave) {
        cout << "Calculando a posicao da chave " << chave << endl;
        if (elem == 0) {
            arv[elem] = hash(chave);
        } else {
            int aux = inc(chave);
            if (aux > 0) {
                arv[elem] = getNoPai(elem) + aux;
            } else {
                arv[elem] = getNoPai(elem) + 1;
            }
            if (arv[elem] >= TAM)
                arv[elem] %= TAM;
        }
        cout << "Pos: " << arv[elem] << endl;
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
        return arv[getNoPaiId(i)];
    }

    int getNoPaiId(int i) {
        if (isNoDir(i)) {//NoPai do NoDir
            return (i - 2) / 2;
        } else {//NoPai do NoEsq
            return (i - 1) / 2;
        }
    }

    bool isNoRaiz(int i) {
        return i == 0;
    }

    bool isNoDir(int i) {
        return i % 2 == 0;
    }

    int getNoId() {
        return elem - 1;
    }

    int getProxNoId() {
        return elem;
    }

    bool temProx() {
        return elem < (TAM * 10);
    }

    bool isProxNoDir() {
        return elem % 2 == 0;
    }
};

int regs[TAM], elem;

void inic() {
    elem = 0;
    for (int i = 0; i < TAM; i++) {
        regs[i] = 0;
    }
}

Arv insAux(Arv arv, int chave) {
    int pos, aux, id;
    //Verifica se ta vazio a posicao
    id = arv.getProxNoId();
    aux = arv.getNoPai(id);
    if (arv.isProxNoDir()) {
        pos = arv.calcPos(regs[aux]);
    } else {
        pos = arv.calcPos(chave);
    }
    if (regs[pos] <= 0) {
        return arv;
    }
    //Nao estando vazio executa insAux de 
    if (arv.isProxNoDir()) {
        return insAux(arv, regs[aux]);
    } else {
        chave = arv.getNoPai(arv.getProxNoId());
        return insAux(arv, chave);
    }
}

void ins() {
    if (elem == TAM) {
        cout << "O registro nao foi inserido" << endl;
        return;
    }
    int chave, aux, regAux, id;
    Arv arv;
    bool ok = false;
    stack<int> pilha, pilhaId;
    cout << "Inserir registro" << endl;
    cout << "Chave: ";
    cin >> chave;
    cout << endl;
    int pos = arv.calcPos(chave);
    if (regs[pos] <= 0) {
        regs[pos] = chave;
        elem++;
        ok = true;
    } else {
        arv = insAux(arv, chave);
        //        while (arv.temProx()) {
        //            id = arv.getProxNoId();
        //            if (arv.isProxNoDir()) {
        //                aux = arv.getNoPai(id);
        //                pos = arv.calcPos(regs[aux]);
        //                if (regs[pos] <= 0) {
        //                    regs[pos] = regs[aux];
        //                    regs[aux] = chave;
        //                    elem++;
        //                    break;
        //                }
        //            } else {
        //                pos = arv.calcPos(chave);
        //                if (regs[pos] <= 0) {
        //                    regs[pos] = chave;
        //                    elem++;
        //                    break;
        //                }
        //            }
        //        }
        //Caminha a arvore do no vazio ate a raiz empilhando os nos
        if (arv.temProx()) {
            id = arv.getNoId();
            pos = arv.getNo(id);
            cout << "Empilhando os nos" << endl;
            while (!arv.isNoRaiz(id)) {
                cout << "No[" << id << "]=" << pos << endl;
                pilha.push(pos);
                pilhaId.push(id);
                pos = arv.getNoPai(id);
                id = arv.getNoPaiId(id);
            }
            cout << endl;
            cout << "Desempilhando os nos" << endl;
            while (!pilha.empty()) {
                pos = pilha.top();
                pilha.pop();
                id = pilhaId.top();
                pilhaId.pop();                
                if (arv.isNoDir(id)) {
                    cout << "NoDir[" << id << "]=" << pos << endl;
                    aux = arv.getNoPai(id);
                    regAux = regs[pos];
                    regs[pos] = regs[aux];
                    regs[aux] = chave;
                    chave = regAux;
                    if (!ok) {
                        elem++;
                        ok = true;
                    }
                } else {
                    cout << "NoEsq[" << id << "]=" << pos << endl;
                }
            }
            cout << endl;
            //Caso insira por caminhamento
            if (pilha.empty()&&!ok) {
                regs[pos] = chave;
                elem++;
                ok = true;
            }
        }
        if (ok) {
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
        if (!arv.temProx()) {
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
        if (arv.temProx()) {
            cout << "O registro foi removido" << endl;
        } else {
            cout << "O registro nao foi encontrado" << endl;
        }
    }
    cout << endl;
}

void exib() {
    cout << "Exibir registros" << endl;
    for (int i = 0; i < TAM; i++) {
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
        }
    }
}