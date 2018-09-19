#ifndef POZIONE_H
#define POZIONE_H
#include "strumento.h"
#include "eccezionestrumento.h"

class Pozione:public Strumento{
friend ostream& operator<<(ostream&, const Pozione&);

private:
    int salute;

public:
    //COSTRUTTORI
    Pozione(string formato,int salute);

    //METODI DI GET
    int getSalute() const;
    QMap<QString, QString> toMap() const;

    //FUNZIONI
    Pozione* clone() const;
    void usa(Mostro* mostro) const;
};

#endif // POZIONE_H
