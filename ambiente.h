#include "oggetto.h"

#ifndef AMBIENTE_H
#define AMBIENTE_H

//DICHIARAZIONI INCOMPLETE E OVERLOADING
class Ambiente;
ostream& operator<<(ostream&, const Ambiente&);


class Ambiente: public Oggetto{
friend ostream& operator<<(ostream&, const Ambiente&);
private:
    vector<string> potenziati;
    vector<string> depotenziati;
    int percentuale_aumento;
    int percentuale_decremento;

public:
    //COSTRUTTORI
    Ambiente(vector<string> potenziati ,vector<string> depotenziati,int percentuale_aumento, int percentuale_decremento);

    //FUNZIONI DI GET
    QMap<QString, QString> toMap() const;
    int getPercAumento() const;
    int getPercDecremento() const;
    vector<string> getPotenziati() const;
    vector<string> getDepotenziati() const;

    //FUNZIONI
    Ambiente* clone() const;
    void inverti();
    double fattoreAmbienteDanno(vector<string> tipi);
    Ambiente* fusione(Ambiente* ambiente);

};

#endif // AMBIENTE_H
