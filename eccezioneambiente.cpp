#include "eccezioneambiente.h"

EccezioneAmbiente::EccezioneAmbiente(std::string s): Eccezione(s){}

std::string EccezioneAmbiente::getMessaggio() const{
    return "Eccezione Ambiente: "+Eccezione::getMessaggio();
}
