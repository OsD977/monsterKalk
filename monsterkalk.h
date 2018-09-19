#ifndef MONSTERKALK_H
#define MONSTERKALK_H
#include <QWidget>
#include "controller.h"
#include <QTextEdit>
#include <QHBoxLayout>
#include <QButtonGroup>
#include "imagebutton.h"
#include "display.h"
#include "displayobjectbutton.h"

class MonsterKalk: public QWidget{
    Q_OBJECT
private:
    Controller* controller;
    //PULSANTI STRUMENTI
    ImageButton* pozione;
    ImageButton* revitalizzante;
    ImageButton* etere;
    ImageButton* bacca;
    ImageButton* caramella;

    //PULSANTI PIETRE
    ImageButton* pietra;
    ImageButton* megapietra;

    //PULSANTI MOSSE
    ImageButton* dannof;
    ImageButton* dannos;
    ImageButton* stato;

    //PULSANTE MOSTRO
    ImageButton* mostro;

    //PULSANTE AMBIENTE
    ImageButton* ambiente;

    //PULSANTI FUNZIONE STRUMENTO
    ImageButton* usa;
    ImageButton* spremi;
    ImageButton* cucina;
    ImageButton* esponi;
    ImageButton* unisci;

    //PULSANTI FUNZIONE PIETRE
    ImageButton* lucida;
    ImageButton* raffina;
    ImageButton* frammenta;

    //PULSANTI FUNZIONE MOSTRO
    ImageButton* attacca;
    ImageButton* megamossa;
    ImageButton* evolvi;
    ImageButton* sacrifica;

    //PULSANTI FUNZIONE MOSSA
    ImageButton* esegui;

    //PULSANTI FUNZIONE AMBIENTE
    ImageButton* inverti;

    //PULSANTI FUNZIONE AMBIENTE E MOSTRO
    ImageButton* fusione;

    //PULSANTI DI GESTIONE
    ImageButton* annulla;
    ImageButton* reset;
    ImageButton* conferma;

    QButtonGroup* gr;

    Display* display;
    Display* risultati;
    Display* salvati;



public:
    MonsterKalk(QWidget* parent=nullptr);
    ~MonsterKalk();
    Oggetto* getLastAttuali() const;
    void disabilita();
    void abilita();
    void cleanDisplay();
    void reStart();
signals:
    void emettiEccezione(string);
    void oggettoRisultato(pair<Oggetto*, QPixmap>);
public slots:
    void newPopUpMostro();
    void newPopUpAmbiente();
    void newPopUpPozione();
    void newPopUpEtere();
    void newPopUpBacca();
    void newPopUpCaramella();
    void newPopUpRevitalizzante();
    void newPopUpPietra();
    void newPopUpMegaPietra();
    void newPopUpDannoFisico();
    void newPopUpDannoSpeciale();
    void newPopUpMossaStato();
    //GESTIONE
    void resetS();
    void reStartView();
    void setFunzione(string nome);

    void catturaAttuali(pair<Oggetto*,QPixmap>);
    void catturaSalvati(pair<Oggetto*,QPixmap>);
    void catturaRisultati(pair<Oggetto*,QPixmap>);
    void catturaEccezione(string);
    void catturaFunzione(string);


    void displayAdd(DisplayObject* oggetto);
    void salvatiAdd(DisplayObjectButton* oggetto);
    void risultatiAdd(DisplayObjectButton* oggetto);

    void indietro();

    void deletefromSalvati(pair<DisplayObjectButton*, Oggetto*>);

    void toResult();


};

#endif // MONSTERKALK_H
