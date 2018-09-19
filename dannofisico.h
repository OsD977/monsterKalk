#ifndef DANNOFISICO_H
#define DANNOFISICO_H
#include "danno.h"

class DannoFisico: public Danno{

friend ostream& operator<<(ostream&, const DannoFisico&);

private:
    int collaterale; //percentuale della salute massima che viene rimossa

    //FUNZIONI AUSILIARIE
    double calcolaDanno(Mostro* attaccante, Mostro* difensore) const;
    double calcolaDannoConAmbiente(Mostro* attaccante, Mostro* difensore, Ambiente* ambiente) const;

public:
    //COSTRUTTORI
    DannoFisico(string tipo,double precisione, int potenza, bool area, int collaterale);

    //METODI DI GET
    int getCollaterale() const;
    QMap<QString, QString> toMap() const;

    //FUNZIONI
    DannoFisico* clone() const;
    void esegui(Mostro* attaccante,vector<Mostro*> difensori) const;
    void esegui(Mostro* attaccante,vector<Mostro*> difensori, Ambiente* ambiente) const;
};

#endif // DANNOFISICO_H
