#include<iostream>
#include<cmath>
#include <algorithm>
using namespace std;

/*
Hay n eventos ocurridos en una línea (coordenadas).
Hay m sensores colocados también en esa línea.
Cada sensor detecta eventos dentro de un rango de distancia ≤ R.
Encuentra el valor mínimo de R para que todos los eventos sean detectados por al menos un sensor.
Entrada:
n, m
Coordenadas de eventos ordenadas
Coordenadas de sensores ordenadas
Salida:
El R mínimo.*/
bool isPosiblidades(float R,float *eventos,float n,float *sensores,int m){
int j=0;

for(int i=0;i<m;i++){
   float e=*(eventos+i);

   while(j<m && *(sensores+j)<e-R){
       j++;
   }
if(j==m) return false;

if(llabs(*(sensores+j)-e)<=R){
   continue;
}else {
    return false;
}
}
return true;
}
int main(){
int n,m;
cin>>n>>m;
float *eventos=new float[n];
float *sensores=new float[m];

for(int i=0;i<n;i++){
   cin>>*(eventos+i);

}
for(int i=0;i<m;i++){
   cin>>*(sensores+i);

}
sort(eventos, eventos + n);
sort(sensores, sensores + m);
float low=0;

float minE=eventos[0];
float maxE=eventos[n-1];

float minS=sensores[0];
float maxS=sensores[m-1];

float high=max(llabs(maxE-minE),llabs(maxS-minS));
float ans=high;

while(low<=high){
   float mid=(low+high)/2.0;

   if(isPosiblidades(mid,eventos,n,sensores,m)){
       ans=mid;
       high=mid-0.00001;
   }else {
       low=mid+0.00001;
   }
}
cout<<ans<<endl;
return 0;
}