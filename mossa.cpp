//PREPROCESSORE---------------------------------------------
#include "mossa.h"

//OVERLOADING

ostream& operator<<(ostream& os, const Mossa& b){
    os<<"Tipo: "<<b.tipo<<endl;
    os<<"Precisione: "<<b.precisione<<endl;
    return os;
}

//COSTRUTTORI-----------------------------------------------

Mossa::Mossa(string t, double prec):tipo(t), precisione(prec){}

//METODI DI GET
double Mossa::getPrecisione() const{
    return precisione;
}


string Mossa::getTipo() const{
    return tipo;
}

//FUNZIONI--------------------------------------------------

double Mossa::getStab(string tmossa, vector<string> tmostro){
    return (inVector(tmostro,tmossa))? 1.5 :1;
}


bool Mossa::successo() const{
    int n = randomBetween(0,100);
    return n<=precisione;
}
