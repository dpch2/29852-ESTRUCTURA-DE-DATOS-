#include <iostream>
#include <cstring>
using namespace std;

    int busquedaBin(char* p[],int t,char* ob){
        int izq=0;
        int der=t-1;

        while(izq<=der){
        int med=(izq+der)/2;
        int ver=strcmp(p[med],ob);
        if(ver==0){return med;
        }else if(ver<0){
            izq=med+1;
        }else{
            der=med-1;
        }
        }

        return -1;
    }

int main(){
    char* palabras[]={"agua","arbol","casa","elefante","fuego"};
    char* ob1="agua";
    char* ob2="mango";

    int tam=size(palabras);

    int res1=busquedaBin(palabras,tam,ob1);
    int res2=busquedaBin(palabras,tam,ob2);

    if(res1!=-1){
        cout<<"-> Se encontró en el índice: "<<res1<<endl;
    }else{
        cout<<"-> No se encontró."<<endl;
    }

    if(res2!=-1){
        cout<<"-> Se encontró en el índice: "<<res2<<endl;
    }else{
        cout<<"-> No se encontró."<<endl;
    }


    return 0;
}