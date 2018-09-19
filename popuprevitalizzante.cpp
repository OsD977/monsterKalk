#include "popuprevitalizzante.h"
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <vector>
#include <QGroupBox>
#include "imagebutton.h"
PopUpRevitalizzante::PopUpRevitalizzante(QWidget* parent): PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione revitalizzante"));
    setMinimumSize(350,480);
    QGridLayout* layout = new QGridLayout();


    //CARATTERISTICHE

    formati = new WidgetFormato();
    vita = new SliderValue("Percentuale vita da curare: ",1,100);

    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche del revitalizzante");
    QVBoxLayout* layoutcar = new QVBoxLayout();
    layoutcar->addWidget(formati);
    layoutcar->addWidget(vita);
    caratt->setLayout(layoutcar);


    //SCELTA DELLA SPRITE
    QPixmap p1= QPixmap(":/Icons/revitalizzante1.png");

    vector<QPixmap> pix={p1};

    QGroupBox* imm = new QGroupBox("Scegli l'icona per il revitalizzante");
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("revitalizzante"));
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(caratt,1,0);
    layout->addLayout(box,2,0,Qt::AlignRight);
    setLayout(layout);

}

PopUpRevitalizzante::~PopUpRevitalizzante(){
    delete formati;
    delete vita;
    delete sprite;
}


void PopUpRevitalizzante::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        Revitalizzante* ris= new Revitalizzante(formati->getSelected(), vita->getValue());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezioneStrumento& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popuprevitalizzante");
    }
    close();
}

