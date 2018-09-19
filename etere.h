#ifndef ETERE_H
#define ETERE_H
#include "strumento.h"

class Etere: public Strumento{
friend ostream& operator<<(ostream&, const Etere&);

private:
    vector<string> stat;
    int aumento_percentuale;
    static int maxAumentoPercentuale;

public:
    //COSTRUTTORI
    Etere(string formato, vector<string> statistiche,int aumento_percentuale);

    //METODI DI GET
    int getAumentoPercentuale() const;
    static int getAumentoMax();
    vector<string> getStat() const;
    QMap<QString, QString> toMap() const;

    //FUNZIONI
    Etere* clone() const;
    void usa(Mostro* mostro) const;
};

#endif // ETERE_H
