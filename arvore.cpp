class arvore {
private:
    const int tam = 11;
    int regs[tam] = {0}; //inicializa tudo com zero
    int elem = 0;
public:

    int hash(int chave) {
        return chave % tam; //funcao hash
    }

    int inc(int chave) {
        return (chave / tam) % tam; //funcao inc
    }

    bool inserir(int chave) {
        int pos = hash(chave);
        if (elem == tam)
            return false;
        if (regs[pos] == 0) {
            regs[pos] = chave; //insercao simples
            elem++;
            return true;
        }
        return caminhar(chave, pos) || mover(chave, pos, regs[pos]); //A recursao esta ruim
    }

    bool caminhar(int chave, int pos) {
        pos += inc(chave);
        if (regs[pos] == 0) {
            regs[pos] = chave;
            elem++;
            return true;
        }
        return caminhar(chave, pos) || mover(chave, pos, regs[pos]); //A recursao ta ruim
    }

    bool mover(int chave, int pos, int valor) {
        pos += inc(valor);
        if (regs[pos] == 0) {
            regs[pos] = chave;
            elem++;
            return true;
        }
        return caminhar(chave, pos) || mover(chave, pos, regs[pos]); //A recursao ta ruim
    }
};