#include "popupbacca.h"
#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include <QGroupBox>
#include "imagebutton.h"
PopUpBacca::PopUpBacca(int minCal, int maxCal, QWidget *parent): PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle("Creazione bacca");
    setMinimumSize(350,450);
    QGridLayout* layout = new QGridLayout();

    //SCELTA DELLA SPRITE

    QPixmap p1= QPixmap(":/Icons/bacca1.png");

    vector<QPixmap> pix={p1};

    QGroupBox* imm = new QGroupBox("Scegli l'icona per la pozione");
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("bacca"),this);
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //CARATTERISTICHE

    gusto = new WidgetGusto(this);
    calorie = new SliderValue("Calorie: ",minCal,maxCal,this);

    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche della bacca");
    QVBoxLayout* layoutcar = new QVBoxLayout();
    layoutcar->addWidget(gusto);
    layoutcar->addWidget(calorie);
    caratt->setLayout(layoutcar);


    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(caratt,1,0);
    layout->addLayout(box,2,0,Qt::AlignRight);
    setLayout(layout);


}

PopUpBacca::~PopUpBacca(){
    delete calorie;
    delete gusto;
    delete sprite;
}

void PopUpBacca::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        Bacca* ris= new Bacca(gusto->getGusto(), calorie->getValue());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezioneBacca& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch(...){
        emit emettiEccezione("errore generico da popupbacca");
    }
    close();

}
