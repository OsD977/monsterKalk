#ifndef CARAMELLA_H
#define CARAMELLA_H
#include "bacca.h"
#include "mostro.h"
#include "etere.h"

//DICHIARAZIONI INCOMPLETE
class Etere;


class Caramella: public Bacca{
friend ostream& operator<<(ostream&, const Caramella&);

private:
    int qualita;
    static int minQualita;
    static int maxQualita;
    static int maxAumentoCaramella;

public:
    //COSTRUTTORI
    Caramella(string gusto, int calorie, int qualita);
    QMap<QString, QString> toMap() const;

    //METODI DI GET
    int getQualita() const;
    static int getMinQual();
    static int getMaxQual();

    //FUNZIONI
    Caramella* clone() const;
    void usa(Mostro* mostro) const;
    Etere* spremi();
    Caramella* cucina(Cura* cura);
    void esponi(Ambiente* ambiente);

};

#endif // CARAMELLA_H
