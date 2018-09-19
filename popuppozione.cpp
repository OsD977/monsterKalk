#include "popuppozione.h"
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
PopUpPozione::PopUpPozione(int sogliamax,QWidget *parent):PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione pozione"));
    setMinimumSize(350,450);
    QGridLayout* layout = new QGridLayout();

    //SCELTA DELLA SPRITE

    QPixmap p1= QPixmap(":/Icons/pozione1.png");
    QPixmap p2= QPixmap(":/Icons/pozione2.png");
    QPixmap p3= QPixmap(":/Icons/pozione3.png");

    vector<QPixmap> pix={p1,p2,p3};

    QGroupBox* imm = new QGroupBox("Scegli l'icona per la pozione");
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("pozione"));
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);



    //CARATTERISTICHE
    formati = new WidgetFormato();
    salute = new SliderValue("Salute da curare: ",1,sogliamax);

    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche della pozione");
    QVBoxLayout* layoutcar = new QVBoxLayout();
    layoutcar->addWidget(formati);
    layoutcar->addWidget(salute);
    caratt->setLayout(layoutcar);


    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(caratt,1,0);
    layout->addLayout(box,2,0,Qt::AlignRight);
    setLayout(layout);

}

PopUpPozione::~PopUpPozione(){
    delete formati;
    delete salute;
    delete sprite;
}

void PopUpPozione::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        Pozione* ris= new Pozione(formati->getSelected(), salute->getValue());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezioneStrumento& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popuppozione");
    }
    close();

}


