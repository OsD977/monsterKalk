#ifndef MEGAPIETRA_H
#define MEGAPIETRA_H
#include "pietra.h"
#include "ambiente.h"
#include "revitalizzante.h"

class MegaPietra: public Pietra{
friend ostream& operator<<(ostream&, const MegaPietra&);

private:
    string tipo;

public:
    //COSTRUTTORI
    MegaPietra(int lucentezza, int rischio_rottura, bool rotta, string tipo);
    MegaPietra(Pietra* pietra);
    MegaPietra(Pietra* pietra, Ambiente* ambiente);

    //METODO DI GET
    string getTipo() const;
    QMap<QString, QString> toMap() const;

    //FUNZIONI
    MegaPietra* clone() const;
    Revitalizzante* frammenta();
};

#endif // MEGAPIETRA_H
