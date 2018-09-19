#include "eccezione.h"

#ifndef ECCEZIONETIPO_H
#define ECCEZIONETIPO_H

class EccezioneTipo: public Eccezione{
public:
    EccezioneTipo(std::string messaggio="");
    std::string getMessaggio() const;
};

#endif // ECCEZIONETIPO_H
