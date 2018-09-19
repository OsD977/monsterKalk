#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QMap>
#include "ambiente.h"
#include "mostro.h"
#include "stato.h"
#include "revitalizzante.h"
#include "pozione.h"
#include "etere.h"
#include "pietra.h"
#include "megapietra.h"
#include "bacca.h"
#include "caramella.h"
#include "dannofisico.h"
#include "dannospeciale.h"
class Model{

private:
    vector<Oggetto*> attuali;   //gli oggetti che al momento sono nel display
    vector<Oggetto*> salvati;   //gli oggetti nella pila dei salvati
    vector<Oggetto*> risultati; //gli oggetti risultato dell'operazione eseguita dal display
public:
    Model();
    ~Model();
    //deve essere possibile prendere fare il pop dalle varie pile/vector

    //GESTIONE PILE
    void freeAttuali();
    void freeSalvati();
    void freeRisultati();
    void reset();

    //METODI DI GET
    QMap<QString, QString> getStringFromAttributes(Oggetto* oggetto);
    int getSizeAttuali() const;
    //METODI DI INSERT OBJECT: inseriscono cose nel vector chiesto
    void inserisciAttuali(Oggetto* oggetto);
    void inserisciRisultati(Oggetto* oggetto);
    void inserisciSalvati(Oggetto* oggetto);

    void deleteFromSalvati(Oggetto* oggetto);
    void deleteLastAttuali();
    Oggetto* getLastAttuali() const;
    Oggetto* popFirstAttuali();


};

#endif // MODEL_H
