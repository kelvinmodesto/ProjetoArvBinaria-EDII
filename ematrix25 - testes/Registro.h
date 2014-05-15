#ifndef REGISTRO_H
#define	REGISTRO_H

#include <cstdlib>
#include <cstring>

using namespace std;

class Registro {
private:
    char chave[3];
    char dado[9];
public:
    void setChave(string chave);
    void setDado(string dado);
    string getChave();
    string getDado();
};

#endif

