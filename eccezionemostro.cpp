#include "eccezionemostro.h"

EccezioneMostro::EccezioneMostro(std::string s): Eccezione(s){}

std::string EccezioneMostro::getMessaggio() const{
    return "Eccezione Mostro: "+Eccezione::getMessaggio();
}

