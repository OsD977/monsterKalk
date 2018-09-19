#include "popuppietra.h"
#include "eccezionepietra.h"
#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include <QGroupBox>
#include "imagebutton.h"
PopUpPietra::PopUpPietra(int minLuc, int maxLuc, QWidget *parent):PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione pietra"));
    setMinimumSize(350,450);
    QGridLayout* layout = new QGridLayout();

    //SCELTA DELLA SPRITE
    QPixmap p1= QPixmap(":/Icons/pietra1.png");

    vector<QPixmap> pix={p1};

    QGroupBox* imm = new QGroupBox("Scegli l'icona per la pietra");
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("pietra"));
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //CARATTERISTICHE
    lucentezza= new SliderValue("Lucentezza: ", minLuc, maxLuc,this);
    rischio_rottura = new SliderValue("Rischio rottura: ",0, 100,this);

    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche della pietra");
    QVBoxLayout* layoutcar = new QVBoxLayout();
    layoutcar->addWidget(lucentezza);
    layoutcar->addWidget(rischio_rottura);
    caratt->setLayout(layoutcar);

    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(caratt,1,0);
    layout->addLayout(box,2,0,Qt::AlignRight);
    setLayout(layout);

}


PopUpPietra::~PopUpPietra(){
    delete lucentezza;
    delete rischio_rottura;
    delete sprite;
}

void PopUpPietra::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        Pietra* ris= new Pietra(lucentezza->getValue(), rischio_rottura->getValue(), false);
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezionePietra& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popuppietra");
    }
    close();
}

