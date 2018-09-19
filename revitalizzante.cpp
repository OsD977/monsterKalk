//PREPROCESSORE----------------------------------------------------------------------
#include "revitalizzante.h"
#include "mostro.h"

//VARIABILI STATICHE
int Revitalizzante::maxPercentualeVita=100;

//OVERLOADING
ostream& operator<<(ostream& os, const Revitalizzante& r){
    os<<"Formato: "<<*(static_cast<const Strumento*>(&r))<<endl;
    os<<"Percentuale vita ripristinata "<<r.percentuale_vita<<endl;
    return os;
}

//COSTRUTTORI----------------------------------------------------------------------
Revitalizzante::Revitalizzante(string form, int pv):Strumento(form){
    percentuale_vita = checkBounds(0,maxPercentualeVita, pv);
}

//METODI DI GET
int Revitalizzante::getPercentualeVita() const{
    return percentuale_vita;
}


QMap<QString, QString> Revitalizzante::toMap() const{
     QMap<QString, QString> ris;
     //formato, stat e aumento percentuale
     ris.insert(QString::fromStdString("Formato"),QString::fromStdString(getFormatoFromValore(getFormato())));
     ris.insert(QString("Percentuale vita"), QString::number(getPercentualeVita()));

    return ris;
}

//FUNZIONI----------------------------------------------------------------------

Revitalizzante* Revitalizzante::clone() const{
    return new Revitalizzante(*this);
}


void Revitalizzante::usa(Mostro*m) const{
    if(m->isDead())
        m->modificaSalute(m->getSaluteMax()*percentuale_vita/100);
    else
        throw EccezioneStrumento("il mostro non è morto, impossibile revitalizzarlo");
}

