#ifndef ECCEZIONEBACCA_H
#define ECCEZIONEBACCA_H
#include "eccezione.h"

class EccezioneBacca:public Eccezione{
public:
    EccezioneBacca(std::string messaggio="");
    std::string getMessaggio() const;
};

#endif // ECCEZIONEBACCA_H
