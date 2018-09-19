//PREPROCESSORE----------------------------------------------------------------------
#include "pozione.h"

//OVERLOADING
ostream& operator<<(ostream& os, const Pozione& p){
    os<<*(static_cast<const Strumento*>(&p));
    os<<"Salute "<<p.salute<<endl;
    return os;
}

//COSTRUTTORI----------------------------------------------------------------------
Pozione::Pozione(string form, int s):Strumento(form){
    salute=checkBounds(0,Mostro::getSogliaSaluteMax(), s);
}

//METODI DI GET----------------------------------------------------------------------
int Pozione::getSalute() const{
    return salute;
}


QMap<QString, QString> Pozione::toMap() const{
    QMap<QString, QString> ris;
    ris.insert(QString::fromStdString("Formato"),QString::fromStdString(Pozione::getFormatoFromValore(getFormato())));
    ris.insert(QString::fromStdString("Salute"), QString::number(getSalute()));

    return ris;
}

//FUNZIONI----------------------------------------------------------------------
Pozione* Pozione::clone() const{
    return new Pozione(*this);
}


void Pozione::usa(Mostro*m) const{
    if(m->isSaluteMax())
        throw EccezioneStrumento("Salute già al massimo, non avrebbe nessun effetto");
    else if(m->isDead())
        throw EccezioneStrumento("Il mostro è morto, usa prima un revitalizzante.");
    else
        m->modificaSalute(salute);

}






