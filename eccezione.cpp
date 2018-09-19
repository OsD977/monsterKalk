#include "eccezione.h"
#include <QDebug>
Eccezione::Eccezione(std::string s): messaggio(s){}

std::string Eccezione::getMessaggio() const{
    return messaggio;
}
