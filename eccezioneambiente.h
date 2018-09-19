#include "eccezione.h"

#ifndef ECCEZIONEAMBIENTE_H
#define ECCEZIONEAMBIENTE_H

class EccezioneAmbiente: public Eccezione{
public:
    EccezioneAmbiente(std::string messaggio="");
    std::string getMessaggio() const;
};

#endif // ECCEZIONEAMBIENTE_H
