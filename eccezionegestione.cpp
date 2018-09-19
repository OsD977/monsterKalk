#include "eccezionegestione.h"

EccezioneGestione::EccezioneGestione(std::string m):Eccezione(m){

}

std::string EccezioneGestione::getMessaggio() const{
    std::string ris=("Eccezione di gestione: ")+ Eccezione::getMessaggio();
    return ris;
}
