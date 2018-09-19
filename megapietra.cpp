//PREPROCESSORE----------------------------------------------------------------------
#include "megapietra.h"
#include "ambiente.h"
#include "eccezionepietra.h"
#include <stdlib.h>
#include <time.h>
#include "revitalizzante.h"

//COSTRUTTORI

MegaPietra::MegaPietra(int lucentezza_, int rischio_rottura_, bool rotta_, string tipo_): Pietra(lucentezza_, rischio_rottura_, rotta_), tipo(tipo_){
    vector<string> types= getTipi();
    if(!inVector(types,tipo)){
        throw EccezionePietra("tipo passato non valido");
    }
}


MegaPietra::MegaPietra(Pietra* pietra): Pietra(*pietra){
    vector<string> types= getTipi();
    tipo=types[randomBetween(0, types.size()-1)];
}


MegaPietra::MegaPietra(Pietra* pietra, Ambiente* ambiente): Pietra(*pietra){
    vector<string> types= ambiente->getPotenziati();
    tipo=types[randomBetween(0, types.size()-1)];
}

//OVERLOADING

ostream& operator<<(ostream& os, const MegaPietra& mp){
    os<<static_cast<const Pietra>(mp);
    os<<"Tipo: "<<mp.tipo<<endl;
    return os;
}

//METODI DI GET

string MegaPietra:: getTipo() const{
    return tipo;
}


QMap<QString, QString> MegaPietra::toMap() const{
    QMap<QString, QString> ris;

    ris.insert(QString("Lucentezza"),QString::number(getLucentezza()));
    ris.insert(QString("Rischio rottura"), QString::number(getRischioRottura()));
    ris.insert(QString::fromStdString("Rotta"), QString::fromStdString(getRotta() ?"Si":"No"));
    ris.insert(QString("Tipo"), QString::fromStdString(getTipo()));
    return ris;
}

//FUNZIONI

MegaPietra* MegaPietra::clone() const{
    return new MegaPietra(*this);
}


Revitalizzante* MegaPietra::frammenta(){
    Revitalizzante* ris= new Revitalizzante(Strumento::getFormatoFromValore(rischio_rottura%4+1), ((lucentezza-minLuc)*50/(maxLuc-minLuc)));
    return ris;
}


