#ifndef REVITALIZZANTE_H
#define REVITALIZZANTE_H
#include "strumento.h"
#include "mostro.h"

class Revitalizzante:public Strumento{
friend ostream& operator<<(ostream&, const Revitalizzante&);

private:
    int percentuale_vita;
    static int maxPercentualeVita;

public:
    //COSTRUTTORI
    Revitalizzante(string formato,int perc_vita);

    //METODI DI GET
    int getPercentualeVita() const;
    QMap<QString, QString> toMap() const;

    //FUNZIONI
    Revitalizzante* clone() const;
    void usa(Mostro* mostro) const;
};

#endif // REVITALIZZANTE_H
