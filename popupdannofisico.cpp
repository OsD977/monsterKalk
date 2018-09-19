#include "popupdannofisico.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include "imagebutton.h"
PopUpDannoFisico::PopUpDannoFisico(QWidget *parent): PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione mossa fisica"));
    setMinimumSize(400,730);
    QGridLayout* layout = new QGridLayout();


    //SCELTA DELLA SPRITE
    QPixmap p1= QPixmap(":/Icons/mossa-fisica1.png");

    vector<QPixmap> pix={p1};
    QGroupBox* imm = new QGroupBox("Scegli l'icona per la mossa fisica",this);
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("mossa-fisica"),this);
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //CARATTERISTICHE

    tipo= new WidgetTipo(this);
    precisione = new SliderValue("Precisione: ",0,100,this);
    potenza = new SliderValue("Potenza: ",0,600,this);
    collaterale = new SliderValue("Percentuale danno collaterale: ",0,100,this);


    QGroupBox* mossa = new QGroupBox("Scegli soltanto un tipo per la mossa: ",this);
    QHBoxLayout* b1 = new QHBoxLayout();
    b1->addWidget(tipo);
    mossa->setLayout(b1);


    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche della mossa fisica",this);
    QVBoxLayout* layoutcar = new QVBoxLayout();


    QLabel* text = new QLabel("Mossa ad area",this);
    QHBoxLayout* form = new QHBoxLayout();
    areasi = new QRadioButton("Si");
    areano = new QRadioButton("No");
    areano->setChecked(true);

    gruppo= new QButtonGroup(this);
    gruppo->addButton(areasi, 1);
    gruppo->addButton(areano, 0);

    form->addWidget(text);
    form->addWidget(areasi);
    form->addWidget(areano);

    layoutcar->addWidget(potenza);
    layoutcar->addWidget(precisione);
    layoutcar->addWidget(collaterale);
    layoutcar->addLayout(form);

    caratt->setLayout(layoutcar);


    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(mossa,1,0);
    layout->addWidget(caratt,2,0);
    layout->addLayout(box,3,0,Qt::AlignRight);
    setLayout(layout);

}

PopUpDannoFisico::~PopUpDannoFisico(){
    delete tipo;
    delete precisione;
    delete potenza;
    delete collaterale;
    delete gruppo;
    delete areasi;
    delete areano;
    delete sprite;
}


void PopUpDannoFisico::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        if(tipo->vuoto())
            throw EccezioneMossa("Non è stato selezionato alcun tipo");
        DannoFisico* ris= new DannoFisico(tipo->getTypes()[0],precisione->getValue(), potenza->getValue(), gruppo->checkedId(),collaterale->getValue());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezioneMossa& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popupdannofisico");
    }
    close();

}
