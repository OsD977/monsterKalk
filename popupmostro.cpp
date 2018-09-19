#include "popupmostro.h"
#include <QGridLayout>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include "eccezionemostro.h"
#include <QGroupBox>
#include "imagebutton.h"
PopUpMostro::PopUpMostro(int smax, int sogliaStatMax, int energiaMax, int rangoMax, QWidget *parent):PopUp(parent){

    //CARATTERISTICHE GENERALI POPUP
    setWindowTitle(QString("Creazione mostro"));
    setMinimumSize(680,600);
    QGridLayout* layout = new QGridLayout();

    //SCELTA DELLA SPRITE

    QPixmap p1= QPixmap(":/Icons/mostro1.png");
    QPixmap p2= QPixmap(":/Icons/mostro2.png");
    QPixmap p3= QPixmap(":/Icons/mostro3.png");

    QPixmap p4= QPixmap(":/Icons/mostro4.png");
    QPixmap p5= QPixmap(":/Icons/mostro5.png");
    QPixmap p6= QPixmap(":/Icons/mostro6.png");

    QPixmap p7= QPixmap(":/Icons/mostro7.png");
    QPixmap p8= QPixmap(":/Icons/mostro8.png");
    QPixmap p9= QPixmap(":/Icons/mostro9.png");

    vector<QPixmap> pix={p1,p2,p3,p4,p5,p6,p7,p8,p9};

    sprite= new ImageMenu(pix, QString::fromStdString("mostro"),this);

    QGroupBox* imm = new QGroupBox("Seleziona l'icona per il mostro",this);
    QHBoxLayout* layoutimm = new QHBoxLayout();
    layoutimm->addWidget(sprite);
    imm->setLayout(layoutimm);


    //CARATTERISTICHE

    salute_max = new SliderValue(QString("Salute massima"),0,smax,this);
    salute_attuale = new SliderValue(QString("Salute attuale"),0,smax,this);
    attacco = new SliderValue(QString("Attacco"),0,sogliaStatMax,this);
    difesa = new SliderValue(QString("Difesa"),0,sogliaStatMax,this);
    attacco_speciale = new SliderValue(QString("Attacco speciale"),0,sogliaStatMax,this);
    difesa_speciale = new SliderValue(QString("Difesa speciale"),0,sogliaStatMax,this);
    energia = new SliderValue(QString("Energia"),0,energiaMax,this);
    rango = new SliderValue(QString("Rango"),1,rangoMax,this);


    QGroupBox* st = new QGroupBox("Seleziona le statistiche del mostro",this);
    QGridLayout* layoutst = new QGridLayout();

    QHBoxLayout* form = new QHBoxLayout();
    QLabel* lab = new QLabel("Megaevoluto: ",this);

    b1 = new QRadioButton("Si");
    b2 = new QRadioButton("No");
    b2->setChecked(true);
    gruppo= new QButtonGroup();
    gruppo->addButton(b1, 1);
    gruppo->addButton(b2, 0);

    form->addWidget(lab);
    form->addWidget(b1);
    form->addWidget(b2);

    layoutst->addWidget(salute_max,0,0);
    layoutst->addWidget(salute_attuale,0,1);
    layoutst->addWidget(attacco,1,0);
    layoutst->addWidget(difesa,1,1);
    layoutst->addWidget(attacco_speciale,2,0);
    layoutst->addWidget(difesa_speciale,2,1);
    layoutst->addWidget(energia,3,0);
    layoutst->addWidget(rango,3,1);
    layoutst->addLayout(form,4,0);

    st->setLayout(layoutst);


    QGroupBox* tp = new QGroupBox("Scegli i tipi del mostro",this);
    QHBoxLayout* layouttp = new QHBoxLayout();
    tipi = new WidgetTipo(this);
    layouttp->addWidget(tipi);
    tp->setLayout(layouttp);


    //INSERIMENTO NEL LAYOUT

    layout->addWidget(imm,1,1);
    layout->addWidget(st,0,0,1,2);
    layout->addWidget(tp,1,0);
    layout->addLayout(box,2,1,1,1,Qt::AlignRight);

    setLayout(layout);

}

PopUpMostro::~PopUpMostro(){
    delete salute_max;
    delete salute_attuale;
    delete attacco;
    delete attacco_speciale;
    delete difesa;
    delete difesa_speciale;
    delete energia;
    delete rango;
    delete tipi;
    delete b1;
    delete b2;
    delete gruppo;
    delete sprite;
}

void PopUpMostro::conferma(){
    //prepara il mostro ed emette un signal con mostro *
    vector<int> stat;
    stat.push_back(attacco->getValue());//attacco
    stat.push_back(difesa->getValue());//difesa
    stat.push_back(attacco_speciale->getValue());//attacco speciale
    stat.push_back(difesa_speciale->getValue());//difesa speciale
    try{
        Mostro* ris= new Mostro(salute_max->getValue(), salute_attuale->getValue(), stat, energia->getValue(), tipi->getTypes(), rango->getValue(), gruppo->checkedId());
        emit emetti(pair<Oggetto*,QPixmap>(ris,sprite->getImg()));
    }
    catch(const EccezioneMostro& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (const Eccezione& e){
        emit emettiEccezione(e.getMessaggio());
    }
    catch (...){
        emit emettiEccezione("errore generico da popupmostro");
    }
    close();

}


