#ifndef DANNOSPECIALE_H
#define DANNOSPECIALE_H
#include "stato.h"
#include "danno.h"

class DannoSpeciale: public Danno{
friend ostream& operator <<(ostream&, const DannoSpeciale&);
private:
    int energia_richiesta;

    //FUNZIONI AUSILIARIE
    double calcolaDanno(Mostro * attaccante, Mostro* difensore) const;
    double calcolaDannoConAmbiente(Mostro * attaccante, Mostro* difensore, Ambiente* ambiente) const;

public:
    //COSTRUTTORI
    DannoSpeciale(string tipo, double precisione, int potenza, bool area, int energia);
    int getEnergiaRichiesta() const;
    QMap<QString, QString> toMap() const;

    //FUNZIONI
    DannoSpeciale* clone() const;
    void esegui(Mostro* attaccante,vector<Mostro*> difensori) const;
    void esegui(Mostro* attaccante,vector<Mostro*> difensori, Ambiente* ambiente) const;
};

#endif // DANNOSPECIALE_H
