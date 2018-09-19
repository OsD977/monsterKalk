#include "eccezionebacca.h"

EccezioneBacca::EccezioneBacca(std::string err): Eccezione(err){}

std::string EccezioneBacca::getMessaggio() const{
    return "Eccezione Bacca: "+Eccezione::getMessaggio();
}
