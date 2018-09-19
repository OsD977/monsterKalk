#include "eccezionemossa.h"


EccezioneMossa::EccezioneMossa(std::string err):Eccezione(err){}

std::string EccezioneMossa::getMessaggio() const{
    return "Eccezione Mossa: "+Eccezione::getMessaggio();
}
