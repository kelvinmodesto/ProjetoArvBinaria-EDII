#include <iostream>
 using namespace std;
#define chave 17;
 class ArvBinaria{
 private:
    int tamanho;
    int hd[];
 public:
    ArvBinaria(int tam);
    int getTamanho(){
        return tamanho;
    }
    void setTamanho(int tam){
        tamanho=tam;
    }
    void inicializar(int t){
        setTamanho(t);
    }
    //Método incompleto, não executar
    bool isCrash(int i){
        bool crash=false;
        if(true){
            crash=true;
        }
        return crash;
    }
    //Cuidado com ponteiros no array
    bool inserir(int value){
      int q= value % chave;
      bool OK = false;
        if(hd[q]==NULL){
            hd[q]= value;
            OK= true;
        }else{
        }
    return OK;
    }
    void remover(){
    }
    void buscar(){
    }

 };
//Construtor da classe
 ArvBinaria::ArvBinaria(int tam){
    inicializar(tam);
 }
 int main(){
     cout << "Sempre que vc fizer alguma coisa poste nesse repositorio https://github.com/ProjetoArvBinaria-EDII"<< endl;
     return 0;
 }
