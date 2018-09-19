#include "popupdannospeciale.h"
#include <QGroupBox>
#include <QPushButton>
#include <vector>
#include <QGroupBox>
#include "imagebutton.h"
PopUpDannoSpeciale::PopUpDannoSpeciale(int sogliaEnergia, QWidget *parent): PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione mossa speciale"));
    setMinimumSize(400,730);
    QGridLayout* layout = new QGridLayout();


    //SCELTA DELLA SPRITE
    QPixmap p1= QPixmap(":/Icons/mossa-speciale1.png");

    vector<QPixmap> pix={p1};

    QGroupBox* imm = new QGroupBox("Scegli l'icona per la mossa speciale");
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("mossa-speciale"),this);
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //CARATTERISTICHE

    tipo= new WidgetTipo(this);
    precisione = new SliderValue("Precisione: ",0,100,this);
    potenza = new SliderValue("Potenza: ",0,600,this);
    energia_richiesta = new SliderValue("Energia richiesta per la mossa: ",0,sogliaEnergia,this);


    QGroupBox* mossa = new QGroupBox("Scegli il tipo della mossa: ",this);
    QHBoxLayout* b1 = new QHBoxLayout();
    b1->addWidget(tipo);
    mossa->setLayout(b1);


    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche della mossa speciale",this);
    QVBoxLayout* layoutcar = new QVBoxLayout();

    QLabel* text = new QLabel("Mossa ad area: ",this);
    areasi = new QRadioButton("Si");
    areano = new QRadioButton("No");
    areano->setChecked(true);

    gruppo= new QButtonGroup();
    gruppo->addButton(areasi, 1);
    gruppo->addButton(areano, 0);

    QHBoxLayout* form = new QHBoxLayout();
    form->addWidget(text);
    form->addWidget(areasi);
    form->addWidget(areano);

    layoutcar->addWidget(potenza);
    layoutcar->addWidget(precisione);
    layoutcar->addWidget(energia_richiesta);
    layoutcar->addLayout(form);

    caratt->setLayout(layoutcar);


    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(mossa,1,0);
    layout->addWidget(caratt,2,0);
    layout->addLayout(box,3,0,Qt::AlignRight);
    setLayout(layout);


}


PopUpDannoSpeciale::~PopUpDannoSpeciale(){
    delete tipo;
    delete precisione;
    delete potenza;
    delete energia_richiesta;
    delete gruppo;
    delete areasi;
    delete areano;
    delete sprite;
}



void PopUpDannoSpeciale::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        if(tipo->vuoto())
            throw EccezioneMossa("Non è stato selezionato alcun tipo");
        DannoSpeciale* ris= new DannoSpeciale(tipo->getTypes()[0], precisione->getValue(), potenza->getValue(), gruppo->checkedId(), energia_richiesta->getValue());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezioneMossa& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popupdannospeciale");
    }
    close();

}
