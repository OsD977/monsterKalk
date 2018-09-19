#ifndef ECCEZIONEMOSSA_H
#define ECCEZIONEMOSSA_H
#include "eccezione.h"

class EccezioneMossa:public Eccezione{
public:
    EccezioneMossa(std::string messaggio="");
    std::string getMessaggio() const;
};

#endif // ECCEZIONEMOSSA_H
