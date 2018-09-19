#include "eccezionestrumento.h"

EccezioneStrumento::EccezioneStrumento(std::string err):Eccezione(err){}

std::string EccezioneStrumento::getMessaggio() const{
    return "Eccezione Strumento: "+Eccezione::getMessaggio();
}
