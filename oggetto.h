//---PREPROCESSORE
#ifndef OGGETTO_H
#define OGGETTO_H

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "funzioni.h"
#include <QMap>
using namespace std;

class Oggetto{
private:
    //--- TIPI SCELTI ---
    // Acqua, Fuoco, Erba, Elettro, Volante, Acciaio, Spettro, Lotta, Psico
    static map<string,map<string, double>> init_tipi();
protected:
    static map<string,map<string, double>> tipi;
    static vector<string> statistiche;

public:
    virtual ~Oggetto()= default;
    virtual Oggetto* clone() const =0;
    virtual QMap<QString, QString> toMap() const =0;
    static vector<string> getTutteStatistiche();
    static vector<string> getTipi();
    static double efficacia(string attaccante, string bersaglio);
    static double getEfficaciaTot(vector<string> attaccante, vector<string> difensore);

};

#endif // OGGETTO_H
