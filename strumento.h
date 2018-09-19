#ifndef STRUMENTO_H
#define STRUMENTO_H
#include "cura.h"
#include "eccezionestrumento.h"
#include "mostro.h"

class Mostro;
class Pietra;

class Strumento: public Cura{
friend ostream& operator<<(ostream&, const Strumento&);

private:
    string formato;
    static map<string, int> init_formati();

protected:
    static map<string, int> Formati;

public:
    //COSTRUTTORI
    Strumento(string formato);

    //FUNZIONI DI GET
    int getFormato() const;
    static string getFormatoFromValore(int valore);

    //FUNZIONI
    virtual void usa(Mostro* mostro) const =0;
    static Pietra* unisci(Strumento* str1, Strumento* str2);

};

#endif // STRUMENTO_H
