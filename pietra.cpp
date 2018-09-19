//PREPROCESSORE----------------------------------------------------------------------
#include "pietra.h"
#include "megapietra.h"
#include <stdlib.h>
#include <time.h>
#include "eccezionepietra.h"
#include "oggetto.h"
#include <typeinfo>

//STATISTICHE E SOGLIE----------------------------------------------------------------------
int Pietra::minLuc=-1000;
int Pietra::maxLuc=1000;
int Pietra::sogliaMegaEv=0;

//OVERLOADING
ostream& operator <<(ostream& os, const Pietra& p){
    os<<"Lucentezza: "<<p.lucentezza<<endl;
    os<<"Rischio rottura: "<<p.rischio_rottura<<endl;
    os<<"Rotta: ";
    if(p.rotta)
        os<<"si"<<endl;
    else
        os<<"no"<<endl;
    return os;
}

//COSTRUTTORI----------------------------------------------------------------------
Pietra::Pietra(int lucentezz, int rischio_rottur, bool rott):rotta(rott){
    lucentezza=checkBounds(minLuc, maxLuc, lucentezz);
    rischio_rottura=checkBounds(0,100, rischio_rottur);
}


Pietra::Pietra(Strumento* str1, Strumento* str2){
    rotta=false;
    if(str1->getFormato()==str2->getFormato()){
        rischio_rottura=0;
    }
    else
        rischio_rottura=randomBetween(0,100);

    int parteNeg=sogliaMegaEv-minLuc;

    int maxInit=sogliaMegaEv-(parteNeg*40/100);
    int bonus= parteNeg*20/100;

    srand (time(NULL));
    lucentezza= randomBetween(minLuc, maxInit);

    if(typeid(*str1)==typeid(*str2))
        lucentezza+=bonus;
}

//METODI DI GET----------------------------------------------------------------------
int Pietra::getMinLuc(){
    return minLuc;
}


int Pietra::getMaxLuc(){
    return maxLuc;
}


int Pietra::getLucentezza() const{
    return lucentezza;
}


int Pietra::getRischioRottura() const{
    return rischio_rottura;
}


bool Pietra::getRotta() const{
    return rotta;
}


QMap<QString, QString> Pietra::toMap() const{

    QMap<QString, QString> ris;

    ris.insert(QString("Lucentezza"),QString::number(getLucentezza()));
    ris.insert(QString("Rischio rottura"), QString::number(getRischioRottura()));
    ris.insert(QString::fromStdString("Rotta"), QString::fromStdString(getRotta() ?"Si":"No"));
    return ris;

}

//FUNZIONI----------------------------------------------------------------------
Pietra* Pietra::clone() const{
    return new Pietra(*this);
}


bool Pietra::testRottura() const{
    srand (time(NULL));
    int var= randomBetween(1,100);
    return var<=rischio_rottura;
}


void Pietra::lucida(){
    if(!rotta){
        int aumento=(maxLuc-minLuc)*5/100;
        lucentezza+=aumento;
        if(testRottura()){
            rotta=true;
        }
    }
    else
        throw EccezionePietra("la pietra è rotta non può essere lucidata");
}


void Pietra::lucida(Pozione* poz){
    if(!rotta){
        int aumento;
        if(poz->getSalute()<=(maxLuc-minLuc)){
            aumento=(maxLuc-minLuc)*5/100+(poz->getSalute()%(maxLuc-minLuc))*50/100;
        }
        else{
            aumento=(maxLuc-minLuc)*30/100;
        }
        lucentezza+=aumento;
        if(testRottura()){
            rotta=true;
        }
        lucentezza=checkBounds(minLuc, maxLuc, lucentezza);

    }
    else{
        throw EccezionePietra("la pietra è rotta non può essere lucidata");
    }
}


MegaPietra* Pietra::raffina(){
    if(lucentezza>=sogliaMegaEv && !rotta){
        MegaPietra* ris=new MegaPietra(this);
        return ris;
    }
    else{
        throw EccezionePietra("la pietra non ha ancora abbastanza lucentezza per essere raffinata o è rotta");
    }
}


MegaPietra* Pietra::raffina(Ambiente* amb){
    if(lucentezza>=sogliaMegaEv &&!rotta){
        MegaPietra* ris=new MegaPietra(this, amb);
        return ris;
    }
    else{
        throw EccezionePietra("la pietra non ha ancora abbastanza lucentezza per essere raffinata o è rotta");
    }
}


