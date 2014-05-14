class Arvore {
private:
    int tam = 11;
    int regs[tam] = {0};
    int elem = 0;

    int hash(int chave) {
        return chave % tam;
    }

    int inc(int chave) {
        return (chave / tam) % tam;
    }
public:

    Arvore() {

    }

    Arvore(int tam, int regs[], int elem) {
        this->tam = tam;
        this->regs = regs;
        this->elem = elem;
    }

    int inserir(int chave) {
        int pos = hash(chave);
        if (elem == tam)
            return -1;
        if (regs[pos] == 0) {
            return pos;
        }
    }

    int caminhar(int chave, int pos) {
        pos += inc(chave);
        if (pos >= tam)
            pos %= tam;
        if (regs[pos] == 0) {
            regs[pos] = chave;
            elem++;
            return true;
        }
    }

    int mover(int chave, int pos, int valor) {
        int aux = pos;
        pos += inc(valor);
        if (pos >= tam)
            pos %= tam;
        if (regs[pos] == 0) {
            regs[aux] = chave;
            regs[pos] = valor;
            elem++;
            return true;
        }
    }
};