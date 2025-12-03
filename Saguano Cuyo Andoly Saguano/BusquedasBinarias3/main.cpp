#include<iostream>
#include <algorithm> // para sort
#include <cmath>  
using namespace::std;
    /*

    Hay n robots colocados en una línea horizontal, cada uno en una coordenada entera.
    Quieres seleccionar k robots para realizar una misión, pero deben estar lo más alejados posible entre ellos para evitar interferencia.
    Tu tarea es encontrar la distancia mínima más grande que se puede asegurar entre cualquier par de robots elegidos.
    */
bool Posibilidades(float D,float *pos, float n, float k){

    int cout=1;
float last=pos[0];
for(int i=0;i<n;i++){
if(*(pos+i)-last>=D){
cout++;
last =*(pos+i);
if(cout==k) return true;
}
}
return false;
}
int main(){
int n,k;
cin >> n >> k;
float *pos=new float[n];
for(int i=0;i<n;i++){
cin>>*(pos+i);
}
sort(pos, pos+n);
float low=1;
float high=pos[n-1]-pos[0];
float ans=0;
while(low<=high){
float mid=(low+high)/2;
if(Posibilidades(mid,pos,n,k)){
ans=mid;
low=mid+1;
}else{
    high=mid -1;
}
}
cout<<"La mayor distencia minima es: "<<ans<<endl;
return 0;
}