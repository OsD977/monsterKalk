#ifndef ECCEZIONEMOSTRO_H
#define ECCEZIONEMOSTRO_H
#include "eccezione.h"

class EccezioneMostro:public Eccezione{
public:
    EccezioneMostro(std::string messaggio="");
    std::string getMessaggio() const;
};


#endif // ECCEZIONEMOSTRO_H
