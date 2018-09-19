#include "eccezionetipo.h"

EccezioneTipo::EccezioneTipo(std::string s): Eccezione(s){}

std::string EccezioneTipo::getMessaggio() const{
    return "Eccezione Tipo: "+Eccezione::getMessaggio();
}
