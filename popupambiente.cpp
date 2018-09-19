#include "popupambiente.h"
#include "eccezioneambiente.h"
#include <QGridLayout>
#include "slidervalue.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <vector>
#include "imagebutton.h"
PopUpAmbiente::PopUpAmbiente(QWidget *parent): PopUp(parent){


    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione ambiente"));
    setMinimumSize(600,800);
    QGridLayout* layout = new QGridLayout();


    //SCELTA DELLA SPRITE
    QPixmap p1= QPixmap(":/Icons/ambiente1.png");
    QPixmap p2= QPixmap(":/Icons/ambiente2.png");
    QPixmap p3= QPixmap(":/Icons/ambiente3.png");
    QPixmap p4= QPixmap(":/Icons/ambiente4.png");
    QPixmap p5= QPixmap(":/Icons/ambiente5.png");
    QPixmap p6= QPixmap(":/Icons/ambiente6.png");
    QPixmap p7= QPixmap(":/Icons/ambiente7.png");

    vector<QPixmap> pix={p1,p2,p3,p4,p5,p6,p7};
    QGroupBox* imm = new QGroupBox("Scegli l'icona per l'ambiente",this);
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("ambiente"),this);
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);



    //CARATTERISTICHE

    potenziati = new WidgetTipo();
    depotenziati = new WidgetTipo();

    //DA SISTEMARE COSTRUTTORE DI AMBIENTE E AVERE UN MASSIMO PER LA PERCENTUALE
    percentuale_aum = new SliderValue("Percentuale incremento: ",0,100,this);
    percentuale_dec = new SliderValue("Percentuale decremento",0,100,this);
    potenziati->bound(depotenziati);
    depotenziati->bound(potenziati);


    QGroupBox* pot = new QGroupBox("Scegli i tipi da potenziare:",this);
    QHBoxLayout* b1 = new QHBoxLayout();
    b1->addWidget(potenziati);
    b1->addWidget(percentuale_aum);
    pot->setLayout(b1);

    QGroupBox* dep = new QGroupBox("Scegli i tipi da depotenziare:",this);
    QHBoxLayout* b2 = new QHBoxLayout();
    b2->addWidget(depotenziati);
    b2->addWidget(percentuale_dec);
    dep->setLayout(b2);


    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(pot,1,0);
    layout->addWidget(dep,2,0);
    layout->addLayout(box,3,0,Qt::AlignRight);
    setLayout(layout);

}

PopUpAmbiente::~PopUpAmbiente(){
    delete potenziati;
    delete depotenziati;
    delete percentuale_aum;
    delete percentuale_dec;
    delete sprite;
}


void PopUpAmbiente::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        Ambiente* ris=new Ambiente(potenziati->getTypes(), depotenziati->getTypes(), percentuale_aum->getValue(), percentuale_dec->getValue());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch(const EccezioneAmbiente& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popupambiente");
    }
    close();

}
