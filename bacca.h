#ifndef BACCA_H
#define BACCA_H
#include "mostro.h"
#include "cura.h"
#include "strumento.h"
#include "eccezionebacca.h"
#include "pozione.h"

//DICHIARAZIONI INCOMPLETE E OVERLOADING
class Pozione;
class Caramella;

class Bacca: public Cura{
friend ostream& operator<<(ostream&, const Bacca&);

private:
    static int minCalorie;
    static int maxCalorie;
    static map<string, int> init_gusti();

protected:
    static map<string, int> Gusti;
    int calorie;
    string gusto;

public:
    //COSTRUTTORI
    Bacca(string gusto, int calorie);

    //METODI DI GET
    string getGusto() const;
    int getCalorie() const;
    int getValoreGusto() const;
    static string getGustofromValore(int valore);
    static int getMinCal();
    static int getMaxCal();
    QMap<QString, QString> toMap() const;

    //METODI DI SET
    void checkCalorie(); //DA GLOBALIZZARE
    void setCaloriePerc(int percentuale);

    //FUNZIONI
    Bacca* clone() const;
    void usa(Mostro* mostro) const;
    Pozione* spremi();
    virtual Caramella* cucina(Cura *cura);
    virtual void esponi(Ambiente* ambiente);

};

#endif // BACCA_H
