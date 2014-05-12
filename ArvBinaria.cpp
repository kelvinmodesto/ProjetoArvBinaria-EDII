#include <iostream>
using namespace std;
const int chave = 17;
int tamanho =17;
//Implementação da árvore em array
class ArrayTree{
    private:
    int tree[chave-1];
    public:
//     Árvore array implementada em niveis onde
//     o filho esquerdo de um no i é igual a 2i+1
//     e o filho direito é igual a 2i+2.
//     o nó será folha se ele não filho esquerdo e filho direito
    int getNode(int i){
        if(isValido(i)){
            return tree[i];
        }else{
            cout <<"Número inválido"<< endl;
        }
    }
    void setNode(int i, int novo){
        if(isValido(i)){
            tree[i]=novo;
        }else{
            cout <<"Número inválido"<< endl;
        }
    }
    int getEsquerdo(int i){
        int j = 2*i+1;
        if(isValido(i)&&isValido(j)){
            return tree[j];
        }else{
            cout <<"Número inválido"<< endl;
        }
    }
    int getDireito(int i){
    int j = 2*i+2;
        if(isValido(i)&&isValido(j)){
            return tree[j];
        }else{
            cout <<"Número inválido"<< endl;
        }}
    int getPai(int i){
        int j;
        if(isValido(i))
        if(i%2==0){
        int j = (i-1)/2;
        }else{
            int j = (i-2)/2;
        }
            return tree[j];
    }
    int getRaiz(){
        return tree[0];
    }
    bool isFolha(int i){
        if(isValido(getDireito(i))||(isValido(getEsquerdo(i)))){
            return true;
        }
    }
    bool isValido(int i){
        if(i>=0&&i<=chave -1){
            return true;
        }
        }
};
 //Atribuir que valores os registros armazenaram
 //Verificar se realmente é necessário essa struct
//     struct Node{
//         int value;
//
//     };
class ArvBinaria{
 private:

        int tamanho;
    int Hash[chave-1];
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
        ArrayTree arvore;
      int q= value % chave;
      bool OK = false;
        if(Hash[q]  ==0){
            Hash[q]= value;
            OK= true;
        }else{

        }
    return OK;
    }
    void mover(){
    }
    void continuar(){
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
     cout << "Hi" << endl;
     return 0;
 }
