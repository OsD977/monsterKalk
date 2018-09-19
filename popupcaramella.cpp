#include "popupcaramella.h"
#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include <QGroupBox>
#include "imagebutton.h"
PopUpCaramella::PopUpCaramella(int minCal, int maxCal, int minQual, int maxQual, QWidget* parent):PopUp(parent){

    setWindowTitle(QString("Creazione caramella"));
    setMinimumSize(350,450);
    QGridLayout* layout = new QGridLayout();


    //SCELTA DELLA SPRITE

    QPixmap p1= QPixmap(":/Icons/caramella1.png");

    vector<QPixmap> pix={p1};

    QGroupBox* imm = new QGroupBox("Scegli l'icona per la caramella",this);
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("caramella"),this);
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //CARATTERISTICHE

    calorie = new SliderValue("Calorie: ", minCal, maxCal, this);
    qualita = new SliderValue("Qualità: ", minQual, maxQual, this);
    gusto = new WidgetGusto(this);

    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche della caramella",this);
    QVBoxLayout* layoutcar = new QVBoxLayout();
    layoutcar->addWidget(gusto);
    layoutcar->addWidget(calorie);
    layoutcar->addWidget(qualita);
    caratt->setLayout(layoutcar);

    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(caratt,1,0);
    layout->addLayout(box,2,0,Qt::AlignRight);
    setLayout(layout);


}

PopUpCaramella::~PopUpCaramella(){
    delete calorie;
    delete gusto;
    delete qualita;
    delete sprite;
}

void PopUpCaramella::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        Caramella* ris= new Caramella(gusto->getGusto(), calorie->getValue(),qualita->getValue());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezioneBacca& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popupcaramella");
    }
    close();

}

