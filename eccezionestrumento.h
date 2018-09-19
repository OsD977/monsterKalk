#ifndef ECCEZIONESTRUMENTO_H
#define ECCEZIONESTRUMENTO_H
#include "eccezione.h"

class EccezioneStrumento:public Eccezione{
public:
    EccezioneStrumento(std::string messaggio="");
    std::string getMessaggio() const;
};

#endif // ECCEZIONESTRUMENTO_H
