#include <cstdlib>
#include <cstring>

using namespace std;

class Registro {
private:
    char chave[3];
    char dado[9];
public:

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