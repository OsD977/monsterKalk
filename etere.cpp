//PREPROCESSORE----------------------------------------------------------------------
#include "etere.h"

//VARIABILI STATICHE

int Etere::maxAumentoPercentuale=100;

//OVERLOADING

ostream& operator<<(ostream& os, const Etere& e){
    os<<"Formato: "<<*(static_cast<const Strumento*>(&e))<<endl;
    os<<"Statistiche potenziate: ";
    os<<e.stat<<endl;
    os<<endl<<"Percentuale aumento: "<<e.aumento_percentuale<<endl;
    return os;
}

//COSTRUTTORI

Etere::Etere(string form, vector<string> st, int aum):Strumento(form){
    aumento_percentuale=checkBounds(0, maxAumentoPercentuale, aum);

    if (st.size()!=0){ //controllo che esista almeno una statistica da potenziare
        if ( (getComuni(st,Oggetto::statistiche)).size()==st.size()) //se le statistiche di st sono tutte presenti all'interno delle statistiche globali
            stat=st;
        else
            throw EccezioneStrumento("Statistica da potenziare non presente");
    }
    else
        throw EccezioneStrumento("Impossibile creare un etere senza una statistica da potenziare");
}

//METODI DI GET

int Etere::getAumentoPercentuale() const{
    return aumento_percentuale;
}


vector<string> Etere::getStat() const{
    if (stat.size()==0)
        throw EccezioneStrumento("vettore delle statistiche vuoto");
    return stat;
}


int Etere::getAumentoMax(){
    return maxAumentoPercentuale;
}

//FUNZIONI

Etere* Etere::clone() const{
    return new Etere(*this);
}


void Etere::usa(Mostro* m) const{ //bisognera' considerare che deve arrivare alla funzione ALMENO una statistica da potenziare, non si puo' quindi creare un etere con 0 statistiche
    vector<string>::const_iterator it = stat.begin();

    for (; it!=stat.end(); it++){ //per ogni statistica da aumentare la cerco nella mappa e la aumento di conseguenza. se non c'e' la statistica cercata lancio una eccezione
        if (m->statisticaPresente(*it))
            m->modificaStatPercentuale(*it, aumento_percentuale);
        else
            throw EccezioneStrumento("Non trovata");
    }
}


QMap<QString, QString> Etere::toMap() const{
     QMap<QString, QString> ris;
     //formato, stat e aumento percentuale
     ris.insert(QString::fromStdString("Formato"),QString::fromStdString(Etere::getFormatoFromValore(getFormato())));
     ris.insert(QString::fromStdString("Aumento percentuale"), QString::number(getAumentoPercentuale()));
     vector<std::string> stats=getStat();
     for(unsigned int i=0; i<stats.size(); i++){
         QString s= QString("Statistica")+QString::number(i+1);
          ris.insert(s,QString::fromStdString(stats[i]));
     }
    return ris;
}


