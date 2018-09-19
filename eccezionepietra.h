#ifndef ECCEZIONEPIETRA_H
#define ECCEZIONEPIETRA_H
#include "eccezione.h"

class EccezionePietra: public Eccezione{
public:
    EccezionePietra(std::string messaggio="");
    std::string getMessaggio() const;
};

#endif // ECCEZIONEPIETRA_H
