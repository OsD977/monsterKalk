#ifndef PIETRA_H
#define PIETRA_H
#include "oggetto.h"
#include "strumento.h"
#include "ambiente.h"
#include "pozione.h"

class MegaPietra;

class Pietra: public Oggetto{
friend ostream& operator <<(ostream&, const Pietra&);

private:
    //FUNZIONI AUSILIARIE
    bool testRottura() const;

protected:
    int lucentezza;
    int rischio_rottura;
    bool rotta;
    static int minLuc;
    static int maxLuc;
    static int sogliaMegaEv;

public:
    //COSTRUTTORI
    Pietra(int lucentezza, int rischio_rottura, bool rotta);
    Pietra(Strumento* str1, Strumento* str2);

    //METODI DI GET
    QMap<QString, QString> toMap() const;
    int getLucentezza() const;
    int getRischioRottura() const;
    bool getRotta() const;
    static int getMinLuc();
    static int getMaxLuc();

    //FUNZIONI
    Pietra* clone() const;
    void lucida();
    void lucida(Pozione* pozione);
    virtual MegaPietra* raffina();
    virtual MegaPietra* raffina(Ambiente* ambiente);
};

#endif // PIETRA_H
