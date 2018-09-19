#ifndef MOSSA_H
#define MOSSA_H
#include "mostro.h"
#include "eccezionemossa.h"

class Mossa: public Oggetto{
friend ostream& operator<<(ostream&, const Mossa&);

protected:
    string tipo;
    double precisione;

    //FUNZIONI AUSILIARIE
    static double getStab(string tipo_mossa, vector<string> tipo_mostro);
    bool successo() const;

public:
    //COSTRUTTORI
    Mossa(string tipo, double precisione);

    //METODI DI GET
    string getTipo() const;
    double getPrecisione() const;

    //FUNZIONI
    virtual void esegui(Mostro* attaccante,vector<Mostro*> bersagli) const=0;
    virtual void esegui(Mostro* attaccante,vector<Mostro*> bersagli, Ambiente* ambiente) const=0;
};

#endif // MOSSA_H
