#include "popupetere.h"
#include "eccezionestrumento.h"
#include <QGridLayout>
#include <QComboBox>
#include "slidervalue.h"
#include <QPushButton>
#include <vector>
#include <QGroupBox>
#include "imagebutton.h"

PopUpEtere::PopUpEtere(int maxAum, QWidget *parent): PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione etere"));
    setMinimumSize(430,600);
    QGridLayout* layout = new QGridLayout();


    //SCELTA DELLA SPRITE

    QPixmap p1= QPixmap(":/Icons/etere1.png");
    vector<QPixmap> pix={p1};

    QGroupBox* imm = new QGroupBox("Scegli l'icona per l'etere",this);
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("etere"),this);

    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //CARATTERISTICHE
    formati = new WidgetFormato(this);
    aum = new SliderValue("Percentuale di aumento statistica: ",1,maxAum,this);
    stats = new WidgetStats(this);

    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche dell'etere",this);
    QVBoxLayout* layoutcar = new QVBoxLayout();

    QGroupBox* st = new QGroupBox("Scegli una o più statistiche da potenziare",this);
    QVBoxLayout* layoutstat = new QVBoxLayout();
    layoutstat->addWidget(stats);
    st->setLayout(layoutstat);

    layoutcar->addWidget(formati);
    layoutcar->addWidget(st);
    layoutcar->addWidget(aum);

    caratt->setLayout(layoutcar);

    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(caratt,1,0);
    layout->addLayout(box,2,0,Qt::AlignRight);
    setLayout(layout);


}


PopUpEtere::~PopUpEtere(){
    delete formati;
    delete aum;
    delete stats;
    delete sprite;
}


void PopUpEtere::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{

        Etere* ris= new Etere(formati->getSelected(), stats->getStats(),aum->getValue());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch(const EccezioneStrumento& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popupetere");
    }
    close();

}

