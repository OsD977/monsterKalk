#include "stato.h"

//COSTRUTTORI---------------------------------------
Stato::Stato(string t, double prec, vector<string> stat, int del, bool sel): Mossa(t,prec), delta(del), self(sel){
    for (unsigned int i=0; i<stat.size(); i++){
        if (!inVector(Oggetto::statistiche,stat[i]))
            throw EccezioneMossa("Una o più statistiche non esistono");
    }
    statistiche=stat;
}

//OVERLOADING
ostream& operator<<(ostream& os, const Stato& m){
    os<<*(static_cast<const Mossa*>(&m));
    os<<"Statistiche: " <<m.statistiche<<endl;
    os<<"Delta: "<<m.delta<<endl;
    os<<"Self: ";
    if(m.self)
        os<<"Sì"<<endl;
    else
        os<<"No"<<endl;
    return os;
}


//METODI DI GET
vector<string> Stato::getStat() const{
    return statistiche;
}


int Stato::getDelta() const{
    return delta;
}


bool Stato::getSelf() const{
    return self;
}


QMap<QString, QString> Stato::toMap() const{
     QMap<QString, QString> ris;
     //formato, stat e aumento percentuale
     ris.insert(QString("Tipo"),QString::fromStdString(getTipo()));
     ris.insert(QString("Precisione"),QString::number(getPrecisione()));
     vector<std::string> stats=getStat();
     for(unsigned int i=0; i<stats.size(); i++){
         QString s= QString("Statistica")+QString::number(i+1);
          ris.insert(s,QString::fromStdString(stats[i]));
     }
     ris.insert(QString("Variazione"),QString::number(getDelta()));
     ris.insert(QString::fromStdString("Self"), QString::fromStdString(getSelf() ?"Si":"No"));
    return ris;
}

//FUNZIONI-------------------------------------------
Stato* Stato::clone() const{
    return new Stato(*this);
}


void Stato::esegui(Mostro* att, vector<Mostro*> ber) const{
    if (successo()){
        if (self){ //self mossa da fare su se stessi (att)
            for (unsigned int i = 0; i<statistiche.size(); i++){
                att->modificaStatPercentuale(statistiche[i], delta*getStab(tipo,att->tipo));
            }
        }
        else {
            if (ber.size()>0){
                for (unsigned int i = 0; i<statistiche.size(); i++){
                    ber[0]->modificaStatPercentuale(statistiche[i], delta*getStab(tipo, att->tipo) * getEfficaciaTot(att->tipo, ber[0]->tipo));
                }
            }
            else
                throw EccezioneMossa("Non ci sono bersagli");
        }
        att->modificaEnergia(abs(delta)*10);
    }
    else
        throw EccezioneMossa("Mossa fallita");
}


void Stato::esegui(Mostro* att,vector<Mostro*> ber, Ambiente* a) const{
    if (successo()){
        if (self){ //self mossa da fare su se stessi (att)
            for (unsigned int i = 0; i<statistiche.size(); i++){
                att->modificaStatPercentuale(statistiche[i], delta*getStab(tipo,att->tipo)*a->fattoreAmbienteDanno(att->tipo));
            }
        }
        else {
            if (ber.size()>0){
                for (unsigned int i = 0; i<statistiche.size(); i++){
                    ber[0]->modificaStatPercentuale(statistiche[i], delta * getStab(tipo, att->tipo) * a->fattoreAmbienteDanno(att->tipo) * getEfficaciaTot(att->tipo, ber[0]->tipo) );
                }
            }
            else
                throw EccezioneMossa("Non ci sono bersagli");
        }
        att->modificaEnergia(abs(delta)*10);
    }
    else
        throw EccezioneMossa("Mossa fallita");
}







