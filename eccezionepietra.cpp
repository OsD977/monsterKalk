#include "eccezionepietra.h"

EccezionePietra::EccezionePietra(std::string s):Eccezione(s){}

std::string EccezionePietra::getMessaggio() const{
    return "Eccezione Pietra: "+Eccezione::getMessaggio();
}
