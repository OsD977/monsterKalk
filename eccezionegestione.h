#ifndef ECCEZIONEGESTIONE_H
#define ECCEZIONEGESTIONE_H
#include "eccezione.h"

class EccezioneGestione: public Eccezione{
public:
    EccezioneGestione(std::string m="");
    std::string getMessaggio() const;
};

#endif // ECCEZIONEGESTIONE_H
