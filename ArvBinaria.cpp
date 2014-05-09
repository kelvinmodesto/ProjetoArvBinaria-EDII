#include <iostream>
 using namespace std;

 class ArvBinaria{
 private:
    int tamanho;
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
    void inserir(){
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
