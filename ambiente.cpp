//PREPROCESSORE----------------------------------------------------------------------
#include "ambiente.h"
#include "eccezioneambiente.h"


//COSTRUTTORI----------------------------------------------------------------------

Ambiente::Ambiente(vector<string> pot, vector<string> dep, int perc_aum, int perc_dec): percentuale_aumento(perc_aum), percentuale_decremento(perc_dec){
    //controllare che i potenziati e i depotenziati siano nel vettore dei tipi
    if(!(pot.size()==getComuni(getTipi(), pot).size()))
        throw EccezioneAmbiente("trovato un potenziato non valido");
    else
        potenziati=pot;

    if(!(dep.size()==getComuni(getTipi(), dep).size()))
        throw EccezioneAmbiente("trovato un depotenziato non valido");
    else
        depotenziati=dep;
}


//OVERLOADING-----------------------------------------------------------------------

ostream& operator<<(ostream& os, const Ambiente& amb){
    os<<"Tipi potenziati: "<<amb.potenziati<<endl;
    os<<"Tipi depotenziati: "<<amb.depotenziati<<endl;
    os<<"Percentuale decremento: "<<amb.percentuale_decremento<<endl;
    os<<"Percentuale aumento: "<<amb.percentuale_aumento<<endl;
    return os;
}


//METODI GET----------------------------------------------------------------------

int Ambiente::getPercAumento() const{
    return percentuale_aumento;
}


int Ambiente::getPercDecremento() const{
    return percentuale_decremento;
}


double Ambiente::fattoreAmbienteDanno(vector<string> m1){ //riceve in input il vettore dei tipi del mostro attaccante
    double risultato=0;
    vector<string>::const_iterator it = m1.begin();

    for (; it!=m1.end(); it++){
        bool trovatoPot=false;
        bool trovatoDep=false;

        for (unsigned int i=0; i<potenziati.size(); i++){ //guardo se e' nei potenziati
            if (*it == potenziati[i])
                trovatoPot=true;
        }

        for (unsigned int i=0; i<depotenziati.size(); i++){ //guardo se e' nei depotenziati
            if (*it == depotenziati[i])
                trovatoDep=true;
        }

        if (trovatoPot)
            risultato+=percentuale_aumento;
        if (trovatoDep) //CONSIDERO CHE LE PERCENTUALI MI ARRIVINO TUTTE POSITIVE E LA CONSIDERO SOLO QUI NEGATIVA
            risultato-=percentuale_decremento;
    }

    double ris= 1+(risultato/100);
    if (ris<0) //se depotenzia piu' del 100% allora ritorno 0 poiche' la mia mossa non avra' effetto
        return 0;
    return ris; //ritorno un numero del tipo 0.7, 1.1, 1.5, 2.5 ecc
}


QMap<QString, QString> Ambiente::toMap() const{
     QMap<QString, QString> ris;
     //formato, stat e aumento percentuale
     ris.insert(QString("Percentuale potenziamento"),QString::number(getPercAumento()));
     ris.insert(QString("Percentuale depotenziamento"),QString::number(getPercDecremento()));
     vector<std::string> pot= getPotenziati();
     vector<std::string> dep= getDepotenziati();
     for(unsigned int i=0; i<pot.size(); i++){
         QString s= QString("Tipo potenziato")+QString::number(i+1);
          ris.insert(s,QString::fromStdString(pot[i]));
     }
     for(unsigned int i=0; i<dep.size(); i++){
         QString s= QString("Tipo depotenziato")+QString::number(i+1);
          ris.insert(s,QString::fromStdString(dep[i]));
     }
    return ris;
}


//FUNZIONI----------------------------------------------------------------------

Ambiente* Ambiente::clone() const{
    return new Ambiente(*this);
}


void Ambiente::inverti(){
    vector<string> aux;
    aux=potenziati;
    potenziati=depotenziati;
    depotenziati=aux;
}


vector<string> Ambiente::getPotenziati() const{
    return potenziati;
}


vector<string> Ambiente::getDepotenziati() const{
    return depotenziati;
}


Ambiente* Ambiente::fusione(Ambiente* ambiente1){
    //crea un nuovo AMBIENTE fondendo i due, prendo quello che ha le caratteristiche minori tra i due e le aumento del 50%
    //dunque faccio la media delle loro caratteristiche e creo il nuovo mostro
    if(!ambiente1)
        throw EccezioneAmbiente("il materiale passato non è valido");
    //il costruttore di ambiente vuole due vettori di tipi, e due percentuali
    //costruisco il vettore dei potenziati cercando gli elementi i comune
    vector<string> pot=getComuni(ambiente1->potenziati,potenziati);
    vector<string> dep=getComuni(ambiente1->depotenziati,depotenziati);
    int aumento= (ambiente1->percentuale_aumento + percentuale_aumento)/2;
    int decremento=(ambiente1->percentuale_decremento + percentuale_decremento)/2;
    return new Ambiente(pot, dep, aumento, decremento);
}
