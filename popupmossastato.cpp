#include "popupmossastato.h"
#include <QGroupBox>
#include <QPushButton>
#include <vector>
#include <QGroupBox>
#include "imagebutton.h"

PopUpMossaStato::PopUpMossaStato(QWidget *parent):PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione mossa stato"));
    setMinimumSize(650,500);
    QGridLayout* layout = new QGridLayout();



    //SCELTA DELLA SPRITE
    QPixmap p1= QPixmap(":/Icons/mossa-stato1.png");

    vector<QPixmap> pix={p1};
    QGroupBox* imm = new QGroupBox("Scegli l'icona per la mossa fisica",this);
    QVBoxLayout* layoutimm = new QVBoxLayout();
    sprite= new ImageMenu(pix, QString::fromStdString("mossa-stato"),this);
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);



    //CARATTERISTICHE

    tipo= new WidgetTipo(this);
    precisione = new SliderValue("Precisione: ",0,100,this);
    delta = new SliderValue("Percentuale modifica statistica: ",-100,100,this);
    stats = new WidgetStats(this);


    QGroupBox* mossa = new QGroupBox("Scegli soltanto un tipo per la mossa: ",this);
    QHBoxLayout* b1 = new QHBoxLayout();
    b1->addWidget(tipo);
    mossa->setLayout(b1);


    QGroupBox* caratt = new QGroupBox("Scegli le caratteristiche della mossa fisica",this);
    QVBoxLayout* layoutcar = new QVBoxLayout();

    QLabel* text = new QLabel("Colpisce se stessi: ");
    selfsi = new QRadioButton("Si");
    selfno = new QRadioButton("No");
    selfno->setChecked(true);

    QHBoxLayout* form = new QHBoxLayout();

    gruppo= new QButtonGroup();
    gruppo->addButton(selfsi, 1);
    gruppo->addButton(selfno, 0);

    form->addWidget(text);
    form->addWidget(selfsi);
    form->addWidget(selfno);


    QGroupBox* st = new QGroupBox("Scegli le statistiche da potenziare: ",this);
    QHBoxLayout* layoutst = new QHBoxLayout();
    layoutst->addWidget(stats);
    st->setLayout(layoutst);

    layoutcar->addWidget(precisione);
    layoutcar->addWidget(st);
    layoutcar->addWidget(delta);
    layoutcar->addLayout(form);

    caratt->setLayout(layoutcar);

    //INSERIMENTO NEL LAYOUT
    layout->addWidget(imm,0,0);
    layout->addWidget(mossa,1,0);
    layout->addWidget(caratt,0,1,2,1);
    layout->addLayout(box,2,1,Qt::AlignRight);
    setLayout(layout);

}

PopUpMossaStato::~PopUpMossaStato(){
    delete tipo;
    delete stats;
    delete precisione;
    delete delta;
    delete gruppo;
    delete selfsi;
    delete selfno;
    delete sprite;
}

void PopUpMossaStato::conferma(){
    //prepara la pozione formato e salute
    //prendo il formato dalla groupbox
    try{
        if(tipo->vuoto())
            throw EccezioneMossa("Non è stato selezionato alcun tipo");
        Stato* ris= new Stato(tipo->getTypes()[0], precisione->getValue(), stats->getStats(), delta->getValue(), gruppo->checkedId());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch (const EccezioneMossa& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popupstato");
    }
    close();

}
