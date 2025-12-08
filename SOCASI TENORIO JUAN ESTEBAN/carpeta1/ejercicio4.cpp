#include <iostream>
#include <string>
using namespace std;

void ordenamiento(string &p,int t){
    for(int i=0;i<t-1;i++){
        for(int j=0;j<t-i-1;j++){
            if(p[j]<p[j+1]){
                int aux=p[j];
                p[j]=p[j+1];
                p[j+1]=aux;
            }
        }
    }
}

int busquedaBin(string p,int t,char ob){
    int izq=0;
    int der=t-1;
    
    while(izq<=der){
        int mid=(izq+der)/2;
        if(p[mid]==ob){
            return mid;
        }else if(p[mid]>ob){
            izq=mid+1;
        }else{
            der=mid-1;
        }
    }
    return -1;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main(){
    string palabra="universidad";
    int n=size(palabra);
    char letra='n';

    ordenamiento(palabra,n);
    cout<<palabra<<endl;// Imprime los valores ASCII de los caracteres ordenados
    int res1=busquedaBin(palabra,n,letra);

    if(res1!=-1){
        cout<<"se encontro en: "<<res1<<endl;
    }else{
        cout<<"no se encontro";
    }

    return 0;
}