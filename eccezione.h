#include <iostream>
#include <string>

#ifndef ECCEZIONE_H
#define ECCEZIONE_H

class Eccezione{
private:
    std::string messaggio;
public:
    //COSTRUTTORE
    Eccezione(std::string messaggio="");

    //METODI DI GET

    virtual std::string getMessaggio() const;
};

#endif // ECCEZIONE_H
