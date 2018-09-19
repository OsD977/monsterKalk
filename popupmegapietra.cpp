#include "popupmegapietra.h"
#include "eccezionepietra.h"
#include <QPushButton>
#include <QGroupBox>
#include <vector>
#include "imagebutton.h"
PopUpMegaPietra::PopUpMegaPietra(int minLuc, int maxLuc, QWidget* parent):PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione megapietra"));
    setMinimumSize(400,670);
    QGridLayout* layout = new QGridLayout();

    //SCELTA DELLA SPRITE

    QPixmap p1= QPixmap(":/Icons/megapietra1.png");

    vector<QPixmap> pix={p1};
    QGroupBox* imm = new QGroupBox("Scegli l'icona per la megapietra");
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("megapietra"));
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //CARATTERISTICHE

    lucentezza= new SliderValue("Lucentezza: ", checkBounds(1,maxLuc,minLuc), maxLuc,this);
    rischio_rottura = new SliderValue("Rischio rottura: ",0, 100,this);

    QGroupBox* mossa = new QGroupBox("Scegli soltanto un tipo per la megapietra",this);
    tipo= new WidgetTipo(this);
    QHBoxLayout* b1 = new QHBoxLayout();
    b1->addWidget(tipo);
    mossa->setLayout(b1);

    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche della megapietra");
    QVBoxLayout* layoutcar = new QVBoxLayout();
    layoutcar->addWidget(lucentezza);
    layoutcar->addWidget(rischio_rottura);
    caratt->setLayout(layoutcar);


    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(mossa,1,0);
    layout->addWidget(caratt,2,0);
    layout->addLayout(box,3,0,Qt::AlignRight);
    setLayout(layout);

}

PopUpMegaPietra::~PopUpMegaPietra(){
    delete tipo;
    delete lucentezza;
    delete rischio_rottura;
    delete sprite;
}


void PopUpMegaPietra::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        if(tipo->vuoto())
            throw EccezionePietra("Non è stato selezionato alcun tipo");
        MegaPietra* ris= new MegaPietra(lucentezza->getValue(), rischio_rottura->getValue(), false, tipo->getTypes()[0]);
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezionePietra& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popupmegapietra");
    }
    close();

}
