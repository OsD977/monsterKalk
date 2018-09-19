//PREPROCESSORE----------------------------------------------------------------------
#include "strumento.h"
#include "pietra.h"

//VARIABILI STATICHE
map<string, int> Strumento::Formati=init_formati();

//OVERLOADING
ostream& operator<<(ostream& os, const Strumento& str){
    os<<"Formato "<<str.formato<<endl;
    return os;
}


//COSTRUTTORI----------------------------------------------------------------------
Strumento::Strumento(string form){
    if (inMap(Formati,form))
        formato=form;
    else
        throw EccezioneStrumento("Formato non disponibile");
}


map<string, int> Strumento::init_formati(){
    map<string, int> ris;
    vector<string> nomi={"Sciroppo", "Crema", "Polvere", "Compressa"};
    vector<int> valori={1,2,3,4};
    for(unsigned int i=0; i<nomi.size(); i++){
        ris.insert(pair<string, int>(nomi[i], valori[i]));
    }
    return ris;
}


//METODI GET----------------------------------------------------------------------
int Strumento::getFormato() const{
    return Formati[formato];
}


string Strumento::getFormatoFromValore(int val){
    for(auto it=Formati.begin(); it!=Formati.end(); it++){
        if(it->second==val){
            return it->first;
        }
    }
    throw EccezioneStrumento("formato non trovato");
}

//FUNZIONI----------------------------------------
Pietra* Strumento::unisci(Strumento* str1, Strumento* str2){
    Pietra* ris= new Pietra(str1, str2);
    return ris;
}



