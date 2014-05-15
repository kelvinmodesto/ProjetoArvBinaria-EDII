
#include <iostream>
using namespace std;
const int chave = 11;
int tamanho =17;
//Implementa��o da �rvore em array
class ArrayTree{
    private:
    int tree[chave]={0};
    int flag=0;
    public:
//     �rvore array implementada em niveis onde
//     o filho esquerdo de um no i � igual a 2i+1
//     e o filho direito � igual a 2i+2.
//     o n� ser� folha se ele n�o filho esquerdo e filho direito
    int getNode(int i){
        if(isValido(i)){
            return tree[i];
        }else{
            cout <<"N�mero inv�lido"<< endl;
        }
    }
    void setNode(int i, int novo){
        if(isValido(i)){
            tree[i]=novo;
        }else{
            cout <<"N�mero inv�lido"<< endl;
        }
    }
    int getEsquerdo(int i){
        int j = 2*i+1;
        if(isValido(i)&&isValido(j)){
            return tree[j];
        }else{
            cout <<"N�mero inv�lido"<< endl;
        }
    }
    int getDireito(int i){
    int j = 2*i+2;
        if(isValido(i)&&isValido(j)){
            return tree[j];
        }else{
            cout <<"N�mero inv�lido"<< endl;
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
    bool isVazia(int pos){
        if(isValido(pos) && tree[pos] == 0 ){
            return true;
        }
    }
    int encontrar(int value){
        int i=0,j=0;
        while(tree[i] != value){
            i++;
        }
     if(tree[i] != 0){
        j=tree[i];
     }
     return j;
    }
    void imprimir(){
        for(int i=0;i<chave;i++){
            cout<<i<<" : " <<tree[i]<<endl;
        }
    }
    int getFlag(){
        return flag;
    }
    void setFlag(){
        flag++;
    }
};
 //Atribuir que valores os registros armazenaram
 //Verificar se realmente � necess�rio essa struct
//     struct Node{
//         int value;
//
//     };
class ArvBinaria{
 private:

        int tamanho;
    int reg[chave];
    ArrayTree at;
 public:
    ArvBinaria(int tam);
    int getTamanho(){
        return tamanho;
    }
    void setTamanho(){
        tamanho=chave;
    }
    void inserir(int v){
      int q= hash(v);
        inserirAux(v,q);
    }
    //Cuidado com ponteiros no array
    //M�todo Incompleto
    bool inserirAux(int value, int q){
      bool OK = false;
        if(reg[q]  ==0){
            reg[q]= value;
            OK= true;
        }else{
//            at.setNode(at.flag);
//            at.setFlag();
            int p =inc(value);
            inserirAux(value,p);
            }
    return OK;
    }
    int hash(int p){
        return p % chave;
    }
    int inc(int q){
        int p=q/chave;
        return p % chave;

    }
    //se o n� for �mpar utilize esse m�todo
    void mover(){
    }
    //Se o n� for par utiliza esse m�todo
    void continuar(){
    }
    void remover(){
    }
    void buscar(){
    }


 };
//Construtor da classe
// ArvBinaria::ArvBinaria(int tam){
//    setTamanho();
// }
 int main(){
     ArrayTree at;
     //at.imprimir();
    // ArvBinaria ab;
     int k= 29/11;
     cout<< k%11<<endl;
     return 0;
 }
