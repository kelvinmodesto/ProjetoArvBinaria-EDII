#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

class Registro {
private:
    char chave[3];
    char dado[9];
public:

    Registro() {

    }

    Registro(string chave, string dado) {
        strncpy(this->chave, chave.c_str(), 2);
        chave[2] = '\0';
        strncpy(this->dado, dado.c_str(), 8);
        dado[8] = '\0';
    }

    void setChave(string chave) {
        strncpy(this->chave, chave.c_str(), 2);
        chave[2] = '\0';
    }

    void setDado(string dado) {
        strncpy(this->dado, dado.c_str(), 8);
        dado[8] = '\0';
    }

    string getChave() {
        return chave;
    }

    string getDado() {
        return dado;
    }
};

class Arquivo {
private:
    fstream arq;
    Registro reg;
    int tam, elem;
    bool ok;

    void contElem() {
        elem = 0;
        int chave,cont=0;
        arq.clear();
        arq.seekg(0, ios::beg);
        cout << "Contagem de elementos" << endl;
        while (arq.good()) {
            arq.read((char *) &reg, sizeof (reg));
            chave = atoi(reg.getChave().c_str());cont++;
            cout << "R[" << cont << "] = ";
            cout << reg.getChave() << " " << reg.getDado() << endl;
            if (chave > 0)
                elem++;
        }
        cout << endl;
    }

    void inicArq() {
        cout << "Inicializando o arquivo" << endl;
        arq.clear();
        arq.seekp(0, ios::beg);
        reg = Registro("0", "");
        for (int i = 0; i < tam; i++) {
            arq.write((char *) &reg, sizeof (reg));
        }
        cout << endl;
    }
public:

    Arquivo() {
        tam = 11;
        arq.open("registros.dat", ios::in | ios::out | ios::binary);
        if (arq) {
            contElem();
            if (elem == 0)
                inicArq();
            cout << "O arquivo foi aberto" << endl;
            ok = true;
        } else {
            cerr << "O arquivo nao foi aberto" << endl;
            ok = false;
        }
        cout << endl;
    }

    ~Arquivo() {
        arq.close();
    }

    void substituir(int pos, Registro reg) {
        arq.clear();
        arq.seekp(pos, ios::beg);
        arq.write((char *) &reg, sizeof (reg));
    }

    int inserir(int pos, Registro reg) {
        substituir(pos, reg);
        return ++elem;
    }

    Registro buscar(int pos) {
        arq.clear();
        arq.seekg(pos, ios::beg);
        arq.read((char *) &reg, sizeof (reg));
        return reg;
    }

    int remover(int pos) {
        arq.clear();
        arq.seekp(pos, ios::beg);
        reg = Registro("-1", "");
        arq.write((char *) &reg, sizeof (reg));
        return --elem;
    }

    int getElem() {
        return elem;
    }

    int getTam() {
        return tam;
    }

    bool isOK() {
        return ok;
    }


};

class Arvore {
private:
    int tam, elem;
    Arquivo arq;
    Registro reg;

    int hash(int chave) {
        return chave % tam;
    }

    int inc(int chave) {
        return (chave / tam) % tam;
    }
public:

    Arvore() {
        this->tam = arq.getTam();
        this->elem = arq.getElem();
    }

    bool inserir(Registro regNovo) {
        if (elem == tam)
            return false;
        int chave = atoi(regNovo.getChave().c_str());
        int pos = hash(chave);
        reg = arq.buscar(pos);
        chave = atoi(reg.getChave().c_str());
        if (chave <= 0) {
            this->elem = arq.inserir(pos, regNovo);
            return true;
        } else {
            //Arvore de recursões com insCam e insMov
        }
    }

    bool insCam(int pos, Registro regNovo) {
        int chave = atoi(regNovo.getChave().c_str());
        pos += inc(chave);
        if (pos >= tam)
            pos %= tam;
        reg = arq.buscar(pos);
        chave = atoi(reg.getChave().c_str());
        if (chave <= 0) {
            this->elem = arq.inserir(pos, regNovo);
            return true;
        } else {
            //Arvore de recursões com insCam e insMov
        }
    }

    int insMov(int pos, Registro regNovo, Registro regAtual) {
        int aux = pos;
        int chave = atoi(regAtual.getChave().c_str());
        pos += inc(chave);
        if (pos >= tam)
            pos %= tam;
        reg = arq.buscar(pos);
        chave = atoi(reg.getChave().c_str());
        if (chave <= 0) {
            arq.substituir(aux, regNovo);
            this->elem = arq.inserir(pos, regAtual);
            return true;
        } else {
            //Arvore de recursões com insCam e insMov
        }
    }

    Registro buscar(string chave) {
        int ch = atoi(chave.c_str());
        int pos = hash(ch);
        reg = arq.buscar(pos);
        if (reg.getChave() == chave) {
            return reg;
        } else {
            //Arvore de recursões com buscCam e buscMov
        }
    }

    Registro buscCam(int pos, string chave) {
        int ch = atoi(chave.c_str());
        pos += inc(ch);
        if (pos >= tam)
            pos %= tam;
        reg = arq.buscar(pos);
        if (reg.getChave() == chave) {
            return reg;
        } else {
            //Arvore de recursões com buscCam e buscMov
        }
    }

    Registro remover(string chave) {
        int ch = atoi(chave.c_str());
        int pos = hash(ch);
        reg = arq.buscar(pos);
        if (reg.getChave() == chave) {
            this->elem = arq.remover(pos);
            return reg;
        } else {
            //Arvore de recursões com caminhar e mover
        }
    }

    Registro remCam(int pos, string chave) {
        int ch = atoi(chave.c_str());
        pos += inc(ch);
        if (pos >= tam)
            pos %= tam;
        reg = arq.buscar(pos);
        if (reg.getChave() == chave) {
            this->elem = arq.remover(pos);
            return reg;
        } else {
            //Arvore de recursões com buscCam e buscMov
        }
    }
};

Registro ler(Registro reg) {
    string aux;
    cout << "Inserir registro" << endl;
    cout << "Digite a chave: ";
    cin >> aux;
    reg.setChave(aux);
    cout << "Digite o dado: ";
    cin >> aux;
    reg.setDado(aux);
    cout << endl;
    return reg;
}

void exibir(Registro reg) {
    cout << "Buscar registro" << endl;
    cout << "Reg[0] = " << reg.getChave() << " " << reg.getDado() << endl;
    cout << endl;
}

int sair() {
    cin.ignore();
    cin.get();
    return 0;
}

int main() {
    Registro reg;
    Arquivo arq;
    if (arq.isOK()) {
        int op = 0;
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
                case 1: arq.inserir(0, ler(reg));
                    break;
                case 2: exibir(arq.buscar(0));
                    break;
                case 3: arq.remover(0);
                    break;
                case 4: break;
                case 5: cout << "Fim do programa";
                    return sair();
                default: cout << "Escolha uma opcao valida" << endl;
                    break;
            }
        }
    }
}