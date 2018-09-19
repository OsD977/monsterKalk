#ifndef CURA_H
#define CURA_H
#include "oggetto.h"
//DICHIARAZIONI INCOMPLETE
class Mostro;

class Cura: public Oggetto{
public:
    //FUNZIONI
    virtual void usa(Mostro* mostro) const =0;
};

#endif // CURA_H
