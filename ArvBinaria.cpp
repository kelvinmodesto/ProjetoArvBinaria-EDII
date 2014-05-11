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
    void setTamanho(){
        tamanho=chave;
    }
    //Cuidado com ponteiros no array
    //Método Incompleto
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
    setTamanho();
 }
 int main(){
     cout << "Sempre que vc fizer alguma coisa poste nesse repositorio https://github.com/ProjetoArvBinaria-EDII"<< endl;
     return 0;
 }
