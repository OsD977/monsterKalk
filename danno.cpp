//PREPROCESSORE
#include "danno.h"

//OVERLOADING

ostream& operator <<(ostream& os, const Danno& d){
    os<<*(static_cast<const Mossa*>(&d));
    os<<"Potenza: "<<d.potenza<<endl;
    os<<"Area: ";
    if(d.area)
        os<<"Sì"<<endl;
    else
        os<<"No"<<endl;
    return os;
}

//METODI DI GET

bool Danno::getArea() const{
    return area;
}


int Danno::getPotenza() const{
    return potenza;
}

//COSTRUTTORI

Danno::Danno(string n,double prec, int pot, bool ar): Mossa(n,prec), area(ar){
    if (pot>=0)
        potenza=pot;
    else
        throw EccezioneMossa("La potenza di una mossa non può essere negativa");
}

