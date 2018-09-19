#include "ambiente.h"
#include "oggetto.h"
#ifndef MOSTRO_H
#define MOSTRO_H


//DICHIARAZIONI INCOMPLETE
class Pietra;
class Megapietra;
class Strumento;

class Mostro: public Oggetto{
//DICHIARAZIONI DI AMICIZIA
friend class Stato;
friend class DannoFisico;
friend class DannoSpeciale;
friend ostream& operator<<(ostream&, const Mostro&);

private:
    int energia;
    int salute_max;
    int salute_attuale;
    map<string, int> stats;
    vector<string> tipo;
    int rango;
    bool megaevoluto;

    static int sogliaStat; //da aggiungere da qualche parte come valore statico comune a tutti i mostri.. in questo modo basta modificare questo parametro e non serve cambiare le funzioni
    static int sogliaSaluteMax;
    static int aumentoStatLivello; //di quanto le statistiche vengono incrementate all'aumento del livello
    static int costante_attacco; //formula del danno. da inizializzare
    static int costante_difesa; //formula del danno. da inizializzare
    static int costante_danno; //formula del danno. da inizializzare
    static int sogliaEnergia;
    static int moltiplicatore_energia;
    static int rangoMax;

     //FUNZIONI AUSILIARIE
    double getDannoBase(int, int) const;
    static double getRandom();

public:
    //COSTRUTTORI
    Mostro(int salute_max, int salute_attuale, vector<int> statistiche, int energia, vector<string> tipi, int rango, bool megaevoluto=0);

    //METODI DI SET
    void modificaSalute(int valore);
    void modificaSalutePerc(int valore);
    void modificaSaluteMaxPercentuale(int valore);
    void modificaStatPercentuale(string statistica, int valore);
    void modificaTutteStatistichePerc(int valore);
    void modificaEnergia(int valore);

    //METODI DI GET

    bool isSaluteMax() const;
    bool isDead() const;
    int getSaluteAttuale() const;
    int getSaluteMax() const;

    map<string, int> getStatistiche() const;
    bool statisticaPresente(string) const;

    int getEnergia() const;
    int energiaNecessaria() const;

    int getRango() const;
    bool isMegaevoluto() const;
    bool checkTipo(string tipo) const;
    vector<string> getTipo() const;

    QMap<QString, QString> toMap() const;
    static int getSogliaSaluteMax();
    static int getSogliaStat();
    static int getRangoMax();
    static int getSogliaEnergia();

    //FUNZIONI
    Mostro* clone() const;
    void evolvi();
    void evolvi(Pietra* pietra);
    Mostro* fusione(Mostro* mostro);
    void attacca(vector<Mostro*> difensori, int mol=1) const;
    void attacca(vector<Mostro*> difensori, Ambiente* ambiente) const;
    void megaMossa(vector<Mostro*> difensori);
    void sacrificio(Mostro* sacrificio);
};

#endif // MOSTRO_H
