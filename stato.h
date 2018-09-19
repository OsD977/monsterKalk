#ifndef STATO_H
#define STATO_H
#include "mossa.h"
#include "eccezionemossa.h"
#include "ambiente.h"

class Stato: public Mossa{
friend ostream& operator<<(ostream&, const Stato&);

private:
    vector<string> statistiche;
    int delta;
    bool self;

public:
    //COSTRUTTORI
    Stato(string tipo, double precisione, vector<string> statistiche, int delta, bool self);

    //METODI DI GET
    vector<string> getStat() const;
    int getDelta() const;
    bool getSelf() const;
    QMap<QString, QString> toMap() const;

    //FUNZIONI
    Stato* clone() const;
    void esegui(Mostro* attaccante,vector<Mostro*> difensori) const;
    void esegui(Mostro* attaccante,vector<Mostro*> difensori, Ambiente* ambiente) const;
};

#endif // STATO_H
