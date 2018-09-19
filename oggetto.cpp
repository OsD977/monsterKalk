//PREPROCESSORE----------------------------------------------------------------------
#include "oggetto.h"
#include "eccezionetipo.h"
//---FUNZIONE INIT PER TIPI---
map<string,map<string, double>> Oggetto::init_tipi(){
    //metto qui i due vettori così non li devo salvare per nulla sulla classe
    vector<string> nomi={"Acqua", "Fuoco", "Erba", "Elettro", "Volante", "Acciaio", "Spettro", "Lotta", "Drago"};
    vector<double> values={
            0.5,2,0.5,1,1,1,1,1,0.5,
            0.5,0.5,2,1,1,2,1,1,0.5,
            2,0.5,0.5,1,0.5,0.5,1,1,0.5,
            2,1,0.5,0.5,2,1,1,1,0.5,
            1,1,2,0.5,1,0.5,1,2,1,
            0.5,0.5,1,0.5,1,0.5,1,1,1,
            1,1,1,1,1,1,2,1,1,
            1,1,1,1,0.5,2,1,1,1,
            1,1,1,1,1,0.5,1,1,2
        };

    map<string,map<string, double>> tipi;
    for(unsigned int i = 0; i<nomi.size(); i++){
        map<string, double> aux;
        for(unsigned int j = 0; j<nomi.size(); j++){
            //construisco la "mappa interna"
            pair<string, double> coppia(nomi[j], values[i*nomi.size()+j]);
            aux.insert(coppia);
        }
        //la mia mappa del primo tipo sarà pronta, la devo inserire nella mappa grande
        pair<string, map<string, double>> coppia2(nomi[i], aux);
        tipi.insert(coppia2);
    }
    return tipi;
}

//---END INIT PER TIPI---

//inizializzo la mappa dei tipi grazie alla funzione di inizilizzazione
map<string,map<string, double>> Oggetto::tipi=init_tipi();

vector<string> Oggetto::statistiche= {"Attacco", "Difesa", "Attacco_speciale", "Difesa_speciale"};
///---EFFICACIA MOSSA SU BERSAGLIO---
double Oggetto::efficacia(string attaccante, string bersaglio){
    //controllo che i due tipi esistano, in quel caso torno l'efficacia, altrimenti lancia un'eccezione
    if(inMap(tipi, attaccante) && inMap(tipi, bersaglio))
        return tipi[attaccante][bersaglio];
    else
        throw EccezioneTipo("uno dei tipi inseriti non è presente");

//    map<string, map<string, double>>::iterator it1 =tipi.find(attaccante);
//    if(it1!=tipi.end()){
//        map<string, double>::iterator it2 =it1->second.find(bersaglio);
//        if(it2!=it1->second.end())
//            return it2->second;
//        else{
//            throw EccezioneTipo("uno dei tipi inseriti non è presente");
//        }
//    }
//    throw EccezioneTipo("uno dei tipi inseriti non è presente");
}


double Oggetto::getEfficaciaTot(vector<string> att, vector<string> dif){

    double efficaciaTot=1;

    vector<string>::const_iterator it = att.begin(); //sui tipi dell'attaccante

    for (; it!=att.end(); it++){
        vector<string>::const_iterator it2 = dif.begin();

        for (; it2!=dif.end(); it2++){
            efficaciaTot*= efficacia(*it, *it2);
        }
    }

    return efficaciaTot;
}
//--- RITORNA IL VETTORE CON TUTTI I NOME DEI TIPI

vector<string> Oggetto::getTipi(){
    vector<string> ris;
    for(auto it=tipi.begin(); it!= tipi.end(); ++it){
        ris.push_back(it->first);
    }
    return ris;
}
//METODI GET--------------------------------------------------------------------

vector<string> Oggetto::getTutteStatistiche(){
    return statistiche;
}

