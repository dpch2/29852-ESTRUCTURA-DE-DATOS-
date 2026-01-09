/*
una contratista acaba de cobrar una factura semanal de 37,000 
en una de las obras que se desarrolla. Debe pagar los servicios de
20 trabjadores, con siderando los siguientes datos: un elecestisita 
gana 6000, los maestros albañiles ganan 1000 y los chacales solamente 
500. ¿cuantos electricistas, maestros albañiles y chacales
 en el grupo de 20 trabjadores ?
*/
#include <iostream>
using namespace std;

class Busqueda{
    private:
    int totalTrabajadores;
    int totalPago;
    public:
    Busqueda(int t, int p){
        totalTrabajadores = t;
        totalPago = p;
    }
    void buscarsolucion(int* x,int* y,int* z){
for(*x=0;*x<=totalTrabajadores;(*x)++){
    int dineroUsado= (*x)*6000;
    if(dineroUsado>totalPago){
break;
    }
    int personasRestantes= totalTrabajadores - (*x);
    int dineroRestante= totalPago - dineroUsado;
    
for(*y=0;*y<=personasRestantes;(*y)++){
int pagoMaestros= (*y)*1000;
int pagoChacales= dineroRestante - pagoMaestros;
if (pagoChacales<0){
    break;;
}
if(pagoChacales%500==0){
    *z=pagoChacales/500;
    if((*x)+(*y)+(*z)==totalTrabajadores){
        return;
}
}
}
}
}
};
int main(){
    int x,y,z;
    int* px = &x;
    int* py = &y;
    int* pz = &z;
    Busqueda busqueda(20,37000);
    busqueda.buscarsolucion(px,py,pz);
cout<<"Electricistas: "<<x<<endl;
cout<<"Maestros albaniles: "<<y<<endl;
cout<<"Chacales: "<<z<<endl;
return 0;
}