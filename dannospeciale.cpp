//PREPROCESSORE
#include "dannospeciale.h"

//COSTRUTTORI

DannoSpeciale::DannoSpeciale(string t,double prec, int pot, bool ar,int en): Danno(t,prec,pot,ar){
    energia_richiesta = checkBounds(0,Mostro::sogliaEnergia,en);
}

//OVERLOADING

ostream& operator <<(ostream& os, const DannoSpeciale& d){
    os<<*(static_cast<const Danno*>(&d));
    os<<"Energia richiesta: "<<d.energia_richiesta<<endl;
    return os;
}

//METODI DI GET

int DannoSpeciale::getEnergiaRichiesta() const{
    return energia_richiesta;
}


QMap<QString, QString> DannoSpeciale::toMap() const{
     QMap<QString, QString> ris;
     //formato, stat e aumento percentuale
     ris.insert(QString("Tipo"),QString::fromStdString(getTipo()));
     ris.insert(QString("Precisione"),QString::number(getPrecisione()));
     ris.insert(QString("Potenza"),QString::number(getPotenza()));
     ris.insert(QString("Area"),QString::fromStdString(getArea() ?"Si":"No"));
     ris.insert(QString("Energia richiesta"),QString::number(getEnergiaRichiesta()));
    return ris;
}


//FUNZIONI

DannoSpeciale* DannoSpeciale::clone() const{
    return new DannoSpeciale(*this);
}


double DannoSpeciale::calcolaDanno(Mostro * att, Mostro* dif) const {
    double danno = ( (2*att->rango + Mostro::costante_attacco * att->stats["Attacco_speciale"]*potenza)  /
            (Mostro::costante_difesa * dif->stats["Difesa_speciale"] +1) + Mostro::costante_danno ) *
            getEfficaciaTot(att->tipo, dif->tipo) * getStab(tipo,att->tipo) * Mostro::getRandom();

    return danno;
}


double DannoSpeciale::calcolaDannoConAmbiente(Mostro * att, Mostro* dif, Ambiente* a) const {
    double danno = ( (2*att->rango + Mostro::costante_attacco * att->stats["Attacco_speciale"]*potenza)  /
            (Mostro::costante_difesa * dif->stats["Difesa_speciale"]*a->fattoreAmbienteDanno(dif->tipo) +1) + Mostro::costante_danno ) *
            getEfficaciaTot(att->tipo, dif->tipo) * a->fattoreAmbienteDanno(att->tipo) * getStab(tipo,att->tipo) * Mostro::getRandom();

    return danno;
}


void DannoSpeciale::esegui(Mostro* att,vector<Mostro*> ber) const{
    if(att->energia>=energia_richiesta){
        if (successo()){
            att->energia -= energia_richiesta;
            if (ber.size()>0){
                if (area){
                    for (unsigned int i=0; i<ber.size(); i++)
                        ber[i]->modificaSalute(-calcolaDanno(att,ber[i]));
                }
                else{
                    ber[0]->modificaSalute(-calcolaDanno(att, ber[0]));
                }
            }
            else
                throw EccezioneMossa("Non ci sono bersagli");
        }
        else
            throw EccezioneMossa("Mossa fallita");
    }
    else
        throw EccezioneMossa("Energia insufficiente");
}


void DannoSpeciale::esegui(Mostro* att,vector<Mostro*> ber, Ambiente* a) const{
    if(att->energia>=energia_richiesta){
        if (successo()){
            att->energia -= energia_richiesta;
            if (ber.size()>0){
                if (area){
                    for (unsigned int i=0; i<ber.size(); i++)
                        ber[i]->modificaSalute(-calcolaDannoConAmbiente(att,ber[i],a));
                }
                else{
                    ber[0]->modificaSalute(-calcolaDannoConAmbiente(att, ber[0],a));
                }
            }
            else
                throw EccezioneMossa("Non ci sono bersagli");
        }
        else
            throw EccezioneMossa("Mossa fallita");
    }
    else
        throw EccezioneMossa("Energia insufficiente");
}

