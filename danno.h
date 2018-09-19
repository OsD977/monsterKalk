#ifndef DANNO_H
#define DANNO_H
#include "mossa.h"

class Danno: public Mossa{
friend ostream& operator <<(ostream&, const Danno&);

protected:
    int potenza;
    bool area;  //serve per colpire tutti gli avversari
public:
    //COSTRUTTORI
    Danno(string tipo,double precisione,int potenza, bool area);

    //METODI DI GET
    int getPotenza() const;
    bool getArea() const;
};

#endif // DANNO_H
