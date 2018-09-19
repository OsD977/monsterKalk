#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "model.h"
#include <QMap>
#include <QString>
#include <QPixmap>
class MonsterKalk;
class Controller
{
private:
    Model* modello;
    MonsterKalk* view;
    map<string, bool>flag;
    QMap<Oggetto*,QPixmap> mappa_attuali;
    QMap<Oggetto*,QPixmap> mappa_salvati;
    QMap<Oggetto*,QPixmap> mappa_risultati;


    //FLAG per gestire le operazioni
public:
    Controller(MonsterKalk* view);
    ~Controller();

    Oggetto* getLastAttuali() const;


    void reset();
    void reStart();
    void freeAttuali();
    void freeSalvati();
    void freeRisultati();
    void addFunzione(string nome);

    void addAttuali(Oggetto* oggetto, QPixmap img);
    void addSalvati(Oggetto* oggetto, QPixmap img);
    void addRisultati(Oggetto* oggetto, QPixmap img);

    void deleteFromSalvati(Oggetto* oggetto);
    void deleteFromAttuali(Oggetto* oggetto);

    //gestione flag
    void freeFlag();
    void setFlag(string nome, bool stato=true);
    bool getFlag(string nome) const;

    vector<pair<Oggetto*, QPixmap>> toResult() const;

    QPixmap getPixmap(Oggetto*) const;

    int getSizeAttuali() const;

};

#endif // CONTROLLER_H
