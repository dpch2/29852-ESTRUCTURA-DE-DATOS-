#include <iostream>
using namespace std;

int busquedaBin(int a[],int l,int ob){
    int izq = 0;
    int der = l-1;

    while(izq<=der){
    int med = (izq+der)/2;
    if(a[med]==ob){return med;
    }else if(a[med]<ob){izq=med+1;
    }else{der=med-1;}
    }
    return -1;

}

int main() {
    int arr[]={1,2,3,4,5};
    int tam=size(arr);
    int obj1=3;
    int obj2=6;
    int res1=busquedaBin(arr,tam,obj1);
    int res2=busquedaBin(arr,tam,obj2);
    cout<<"Buscando "<<obj1<<"..."<<endl;
    if(res1!=-1){
        cout<<"-> Se encontró en el índice: "<<res1<<endl;
    }else{
        cout<<"-> No se encontró."<<endl;
    }
    cout<<"---"<<endl;
    cout<<"Buscando "<<obj2<<"..."<<endl;
    if(res2!=-1){
        cout<<"-> Se encontró en el índice: "<<res2<<endl;
    }else{
        cout<<"-> No se encontró."<<endl;
    }

    return 0;
}