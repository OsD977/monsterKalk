#include "model.h"

Model::Model(){}

Model::~Model(){
    for (unsigned int i =0; i<attuali.size(); i++){
        delete attuali[i];
    }

    for (unsigned int i =0; i<salvati.size(); i++){
        delete salvati[i];
    }

    for (unsigned int i =0; i<risultati.size(); i++){
        delete risultati[i];
    }
}

int Model::getSizeAttuali() const{
    return attuali.size();
}
void Model::freeAttuali(){
    //deve svuotare tutti gli oggetti che sono in attuale
    for(auto it=attuali.begin(); it!=attuali.end(); it++){
        delete *it;
        it=attuali.erase(it);
        it--;

    }
}
void Model::freeSalvati(){
    //deve svuotare tutti gli oggetti che sono in attuale
    for(auto it=salvati.begin(); it!=salvati.end(); it++){
        delete *it;
        it=salvati.erase(it);
        it--;

    }
}
void Model::freeRisultati(){
    //deve svuotare tutti gli oggetti che sono in attuale
    for(auto it=risultati.begin(); it!=risultati.end(); it++){
        delete *it;
        it=risultati.erase(it);
        it--;
    }
}

void Model::reset(){
    freeAttuali();
    freeSalvati();
    freeRisultati();
}

void Model::inserisciAttuali(Oggetto* oggetto){
    attuali.push_back(oggetto);
}

void Model::inserisciSalvati(Oggetto* oggetto){
    salvati.push_back(oggetto);
}

void Model::inserisciRisultati(Oggetto* oggetto){
    risultati.push_back(oggetto);
}

Oggetto* Model::getLastAttuali() const{
    if(attuali.size()!=0){
        return attuali[attuali.size()-1];
    }
    else{
        throw Eccezione("getLast fallita, non sono presenti mostri nella pila degli attuali");
    }
}

void Model::deleteFromSalvati(Oggetto *oggetto){
    bool trovato=false;
    for(auto it=salvati.begin(); !trovato && it!=salvati.end(); it++){
        if(*it==oggetto){
            delete *it;
            it=salvati.erase(it);
            it--;
            trovato=true;
        }
    }
}

void Model::deleteLastAttuali(){
    if(attuali.size()!=0){
        delete attuali[attuali.size()-1];
        attuali.erase(--attuali.end());

    }
    else{
        throw Eccezione("attuali è vuoto, non posso eliminare");
    }
}

Oggetto* Model::popFirstAttuali(){
    if(attuali.size()==0)
        return nullptr;
    else{
        Oggetto* ris=attuali[0];
        attuali.erase(attuali.begin());
        return ris;
    }
}


