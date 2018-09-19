//PREPROCESSORE
#include "dannofisico.h"

//COSTRUTTORI

DannoFisico::DannoFisico(string t,double prec, int pot, bool ar, int col): Danno(t,prec, pot, ar){
    collaterale = checkBounds(0,100,col);
}

//OVERLOADING

ostream& operator<<(ostream& os, const DannoFisico& df){
    os<<*(static_cast<const Danno*>(&df));
    os<<"Collaterale: "<<df.collaterale<<endl;
    return os;
}

//METODI DI GET

int DannoFisico::getCollaterale() const{
    return collaterale;
}


QMap<QString, QString> DannoFisico::toMap() const{
     QMap<QString, QString> ris;
     //formato, stat e aumento percentuale
     ris.insert(QString("Tipo"),QString::fromStdString(getTipo()));
     ris.insert(QString("Precisione"),QString::number(getPrecisione()));
     ris.insert(QString("Potenza"),QString::number(getPotenza()));
     ris.insert(QString("Area"),QString::fromStdString(getArea() ?"Si":"No"));
     ris.insert(QString("Collaterale"),QString::number(getCollaterale()));
    return ris;
}

//FUNZIONI AUSILIARIE

double DannoFisico::calcolaDanno(Mostro * att, Mostro* dif) const{
    double danno =  ( (2*att->rango + Mostro::costante_attacco * att->stats["Attacco"]*potenza) /
            (Mostro::costante_difesa * dif->stats["Difesa"] +1) + Mostro::costante_danno ) * getEfficaciaTot(att->tipo, dif->tipo) *
            getStab(tipo,att->tipo) * Mostro::getRandom();

    return danno;
}


double DannoFisico::calcolaDannoConAmbiente(Mostro * att, Mostro* dif, Ambiente* a) const{
    double danno = ( (2*att->rango + Mostro::costante_attacco * att->stats["Attacco"]*potenza) /
            (Mostro::costante_difesa * dif->stats["Difesa"]*a->fattoreAmbienteDanno(dif->tipo) +1) + Mostro::costante_danno )
            * getEfficaciaTot(att->tipo, dif->tipo) * a->fattoreAmbienteDanno(att->tipo) * getStab(tipo,att->tipo) * Mostro::getRandom();

    return danno;
}

//FUNZIONI

DannoFisico* DannoFisico::clone() const{
    return new DannoFisico(*this);
}


void DannoFisico::esegui(Mostro* att,vector<Mostro*> ber) const{
    if (successo()){
        if (ber.size()>0){
            if (area){
                for (unsigned int i=0; i<ber.size(); i++)
                    ber[i]->modificaSalute(-calcolaDanno(att,ber[i]));
            }
            else{
                ber[0]->modificaSalute(-calcolaDanno(att, ber[0]));
            }
            att->modificaSalutePerc(-collaterale);
        }
        else
            throw EccezioneMossa("Non ci sono bersagli");
    }
    else
        throw EccezioneMossa("Mossa fallita");
}


void DannoFisico::esegui(Mostro* att,vector<Mostro*> ber, Ambiente* a) const{
    if (successo()){
        if (ber.size()>0){
            if (area){
                for (unsigned int i=0; i<ber.size(); i++)
                    ber[i]->modificaSalute(-calcolaDannoConAmbiente(att,ber[i],a));
            }
            else{
                ber[0]->modificaSalute(-calcolaDannoConAmbiente(att, ber[0],a));
            }
            att->modificaSalutePerc(-collaterale);
        }
        else
            throw EccezioneMossa("Non ci sono bersagli");
    }
    else
        throw EccezioneMossa("Mossa fallita");
}





