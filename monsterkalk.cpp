#include "monsterkalk.h"
#include <QGridLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QFormLayout>
#include <QTextEdit>
#include <QGroupBox>
#include "popupbacca.h"
#include "popupcaramella.h"
#include "popupmostro.h"
#include "popupambiente.h"
#include "popuppozione.h"
#include "popupetere.h"
#include "popuppietra.h"
#include "popupmegapietra.h"
#include "popupdannofisico.h"
#include "popupdannospeciale.h"
#include "popuprevitalizzante.h"
#include "popupmossastato.h"
#include "slidervalue.h"
#include <QToolButton>
#include "widgettipo.h"
#include "mostro.h"
#include "displayobject.h"
#include "eccezionegestione.h"
#include "mostro.h"
#include <QDebug>
#include "functionbutton.h"
#include <QScreen>
#include <QGuiApplication>
MonsterKalk::MonsterKalk(QWidget* parent): QWidget(parent), controller(new Controller(this)){

    //DEFINISCO DIMENSIONI

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    int height = screenGeometry.height()-100;
    int width = screenGeometry.width()-100;

    setMinimumSize(width,height);
    setStyleSheet("#fix{border:1px solid lightgray; border-radius: 4px;}");

    //CREO I PULSANTI
    QSize size = QSize(width/13, height/18);

    //COSTRUTTORE DI IMAGEBUTTON(testo, icona, q*size);

    pozione = new ImageButton(QString("Pozione"),QString(":/Icons/pozione1.png"),size);
    pozione->setToolTip("Questa è una pozione");
    revitalizzante = new ImageButton("Revitalizzante",":/Icons/revitalizzante.png",size);
    etere = new ImageButton("Etere",":/Icons/etere.png",size);
    bacca= new ImageButton("Bacca",":Icons/bacca.png",size);
    caramella = new ImageButton("Caramella",":/Icons/caramella.png",size);

    pietra = new ImageButton("Pietra",":/Icons/pietra.png",size);
    megapietra = new ImageButton("MegaPietra",":/Icons/megapietra.png",size);

    dannof = new ImageButton("Mossa fisica",":/Icons/mossa-fisica.png",size);
    dannos = new ImageButton("Mossa speciale",":/Icons/mossa-speciale.png",size);
    stato = new ImageButton("Mossa stato",":/Icons/mossa-stato.png",size);

    mostro = new ImageButton("Mostro",":/Icons/mostro1.png",size);
    ambiente = new ImageButton("Ambiente",":/Icons/ambiente1.png",size);

    usa = new FunctionButton("Usa",":/Icons/usa.png",size, "usa");
    usa->setToolTip("Utilizza una pozione, etere o revitalizzante su un mostro bersaglio. \nOrdine: mostro-strumento.");
    spremi = new FunctionButton("Spremi",":/Icons/spremi.png",size,"spremi");
    spremi->setToolTip("Spreme una bacca per ottenere una pozione \noppure una caramella per ottenere un etere.");
    cucina = new FunctionButton("Cucina",":/Icons/cucina.png",size, "cucina");
    cucina->setToolTip("Cucina una bacca/caramella con uno strumento o una bacca/caramella per ottenere una caramella. \nOrdine: bacca/caramella-strumento.");
    esponi = new FunctionButton("Esponi",":/Icons/esponi.png",size, "esponi");
    esponi->setToolTip("Espone una bacca/caramella ad un ambiente per potenziarne le statistiche. \nOrdine: bacca/caramella-ambiente.");
    unisci = new FunctionButton("Unisci",":/Icons/unisci.png",size, "unisci");
    unisci->setToolTip("Unisce due strumenti per ottenere una pietra. \nOrdine: strumento-strumento.");

    lucida = new FunctionButton("Lucida",":/Icons/lucida.png",size, "lucida");
    lucida->setToolTip("Lucida un pietra/megapietra per aumentare la lucentezza. \nOrdine: pietra/megapietra.");
    raffina = new FunctionButton("Raffina",":/Icons/raffina.png",size, "raffina");
    raffina->setToolTip("Raffina una pietra o una megapietra per ottenere una megapietra. \nOrdine: pietra/megapietra.");
    frammenta = new FunctionButton("Frammenta",":/Icons/frammenta.png",size, "frammenta");
    frammenta->setToolTip("Frammenta una megaPietra per ottenere un revitalizzante.");

    attacca = new FunctionButton("Attacca",":/Icons/attacca.png",size,"attacca");
    attacca->setToolTip("Consente ad un mostro di attaccare altri mostri. L'aggiunta di un ambiente è opzionale.\nOrdine: mostro attaccante-ambiente-mostri bersaglio.");
    megamossa = new FunctionButton("Megamossa",":/Icons/megamossa.png",size, "megamossa");
    megamossa->setToolTip("Consente ad un mostro di eseguire una megamossa.\nOrdine: mostro attaccante-mostri bersaglio.");
    evolvi = new FunctionButton("Evolvi",":/Icons/evolvi.png",size, "evolvi");
    evolvi->setToolTip("Evolve un mostro bersaglio. L'utilizzo di una pietra/megaPietra è opzionale.\nOrdine: mostro-pietra/megapietra.");
    sacrifica = new FunctionButton("Sacrifica",":/Icons/sacrifica.png",size, "sacrifica");
    sacrifica->setToolTip("Sacrifica un mostro per potenziarne un altro.\nOrdine: mostro-mostro da sacrificare");

    esegui = new FunctionButton("Esegui",":/Icons/esegui.png",size, "esegui");
    esegui->setToolTip("Consente di eseguire una mossa su mostri bersaglio. L'ambiente è opzionale.\nOrdine:mostro attaccante-mossa-ambiente-mostri bersaglio.");

    inverti = new FunctionButton("Inverti",":/Icons/inverti.png",size, "inverti");
    inverti->setToolTip("Inverte le statistiche di un ambiente.");
    fusione = new FunctionButton("Fusione",":/Icons/fusione.png",size, "fusione");
    fusione->setToolTip("Consente di fondere due mostri o due ambienti per crearne uno nuovo.\nOrdine: mostro-mostro/ambiente-ambiente.");


    annulla = new ImageButton("Annulla",":/Icons/indietro.png",size);
    annulla->setToolTip("Annulla l'ultima operazione inserita nel display principale.");
    reset = new ImageButton("Reset",":/Icons/reset.png",size);
    reset->setToolTip("Azzera i tre display della calcolatrice ritornando allo stato inziale.");
    conferma = new ImageButton("Conferma",":/Icons/conferma.png",size);
    conferma->setToolTip("Conferma l'operazione sullo schermo.");


    gr= new QButtonGroup();
    gr->addButton(usa);
    gr->addButton(spremi);
    gr->addButton(cucina);
    gr->addButton(esponi);
    gr->addButton(unisci);
    gr->addButton(lucida);
    gr->addButton(raffina);
    gr->addButton(frammenta);
    gr->addButton(attacca);
    gr->addButton(megamossa);
    gr->addButton(evolvi);
    gr->addButton(sacrifica);
    gr->addButton(esegui);
    gr->addButton(inverti);
    gr->addButton(fusione);


//////////////////

    //LAYOUT GENERALE DELLA CALCOLATRICE
    QGridLayout* layout = new QGridLayout();


    //DEFINISCO STRUMENTI
    QGroupBox* strumenti = new QGroupBox("Strumenti",this);
    QGridLayout * strgrid = new QGridLayout();

    strgrid->addWidget(pozione,0,0);
    strgrid->addWidget(revitalizzante,0,1);
    strgrid->addWidget(etere,0,2);
    strgrid->addWidget(bacca,1,0,1,2,Qt::AlignCenter);
    strgrid->addWidget(caramella,1,1,1,3,Qt::AlignCenter);

    strumenti->setLayout(strgrid);


    //DEFINISCO PIETRE
    QGroupBox* pietre = new QGroupBox("Pietre",this);
    QGridLayout* ptrgrid = new QGridLayout();

    ptrgrid->addWidget(pietra,0,0);
    ptrgrid->addWidget(megapietra,0,1);

    pietre->setLayout(ptrgrid);


    //DEFINISCO MOSSE
    QGroupBox* mosse = new QGroupBox("Mosse",this);
    QGridLayout* mossegrid = new QGridLayout();
    mossegrid->addWidget(dannof,0,0);
    mossegrid->addWidget(dannos,0,1);
    //mossegrid->addWidget(stato,1,0,1,2,Qt::AlignCenter);
    mossegrid->addWidget(stato,0,2);
    mosse->setLayout(mossegrid);


    //DEFINISCO MOSTRO E AMBIENTE
    QGridLayout* mostroamb = new QGridLayout();

    QGroupBox* mgroup = new QGroupBox("Mostro",this);
    QHBoxLayout* mh = new QHBoxLayout();
    mh->addWidget(mostro);
    mgroup->setLayout(mh);

    QGroupBox* ambgroup = new QGroupBox("Ambiente",this);
    QHBoxLayout* ambh = new QHBoxLayout();
    ambh->addWidget(ambiente);
    ambgroup->setLayout(ambh);


    mostroamb->addWidget(mgroup,0,0);
    mostroamb->addWidget(ambgroup,0,1);
///////////////////////


    //DEFINISCO FUNZIONI

    //DEFINISCO FUNZIONI STRUMENTI

    QGroupBox* funstr = new QGroupBox("Strumenti",this);

    QGridLayout*  funstrgrid = new QGridLayout();
    funstrgrid->addWidget(usa,0,0);
    funstrgrid->addWidget(spremi,0,1);
    funstrgrid->addWidget(cucina,0,2);
//    funstrgrid->addWidget(esponi,1,0,1,2,Qt::AlignCenter);
//    funstrgrid->addWidget(unisci,1,1,1,2,Qt::AlignCenter);
    funstrgrid->addWidget(esponi,0,3);
    funstrgrid->addWidget(unisci,1,0,1,4,Qt::AlignCenter);

    funstr->setLayout(funstrgrid);

    //DEFINISCO FUNZIONI MOSTRO

    QGroupBox* funmostro = new QGroupBox("Mostro",this);

    QGridLayout* funmostrogrid = new QGridLayout();
    funmostrogrid->addWidget(attacca,0,0);
    funmostrogrid->addWidget(megamossa,0,1);
    funmostrogrid->addWidget(evolvi,0,2);
    //funmostrogrid->addWidget(sacrifica,1,0,1,3,Qt::AlignCenter);
    funmostrogrid->addWidget(sacrifica,0,3);

    funmostro->setLayout(funmostrogrid);

    //DEFINISCO FUNZIONI PIETRA

    QGroupBox* funpietra = new QGroupBox("Pietra",this);

    QGridLayout* funpietragrid = new QGridLayout();
    funpietragrid->addWidget(lucida,0,0);
    funpietragrid->addWidget(raffina,0,1);
    funpietragrid->addWidget(frammenta,0,2);

    funpietra->setLayout(funpietragrid);

    //DEFINISCO FUNZIONI MOSSA E AMBIENTE
    QGridLayout* funmossaamb = new QGridLayout();

    QGroupBox* funmossa = new QGroupBox("Mossa",this);
    QHBoxLayout* funmossabox = new QHBoxLayout();
    funmossabox->addWidget(esegui);
    funmossa->setLayout(funmossabox);

    QGroupBox* funamb = new QGroupBox("Ambiente",this);
    QHBoxLayout* funambbox = new QHBoxLayout();
    funambbox->addWidget(inverti);
    funamb->setLayout(funambbox);

    QGroupBox* funmostroamb = new QGroupBox("Mostro e Ambiente",this);
    QHBoxLayout* funmostroambbox = new QHBoxLayout();
    funmostroambbox->addWidget(fusione);
    funmostroamb->setLayout(funmostroambbox);


    funmossaamb->addWidget(funmossa,0,0);
    funmossaamb->addWidget(funamb,0,1);
    funmossaamb->addWidget(funmostroamb,0,2);


    //DEFINISCO I PULSANTI DI GESTIONE

    QGroupBox* gestione = new QGroupBox("Gestione",this);

    QGridLayout* gestgrid = new QGridLayout();
    gestgrid->addWidget(annulla,0,0);
    gestgrid->addWidget(reset,0,1);
    gestgrid->addWidget(conferma,0,2);

    gestione->setLayout(gestgrid);

    //DEFINISCO IL DISPLAY

    display = new Display(Qt::Orientation::Vertical);

    QGroupBox* ris = new QGroupBox("Risultati",this);

    risultati = new Display(Qt::Orientation::Horizontal);

    QHBoxLayout* risbox = new QHBoxLayout();
    risbox->addWidget(risultati);

    ris->setLayout(risbox);

    QGroupBox* salv = new QGroupBox("Salvati",this);

    salvati = new Display(Qt::Orientation::Horizontal);
    QHBoxLayout* salvbox = new QHBoxLayout();
    salvbox->addWidget(salvati);
    salv->setLayout(salvbox);


    //DEFINISCO LA LEGENDA
    QGroupBox* leg = new QGroupBox(this);

    QGridLayout* leglayout = new QGridLayout();
    QLabel* title = new QLabel("<b>Guida per l'uso</b>");
    QLabel* text = new QLabel("<b>Le funzioni nella colonna di destra possono essere inserite in qualsiasi ordine.</b>");
    text->setWordWrap(true);


    QLabel* l1 = new QLabel();
    l1->setPixmap(QPixmap(":/Icons/salva.png").scaled(30,30));

    QLabel* l2 = new QLabel("Serve per salvare un oggetto e inserirlo nel display dei salvati.",this);
    QHBoxLayout* b1 = new QHBoxLayout();
    b1->addWidget(l1);
    b1->addWidget(l2,Qt::AlignLeft);

    QLabel* l3 = new QLabel();
    l3->setPixmap(QPixmap(":/Icons/elimina.png").scaled(30,30));

    QLabel* l4 = new QLabel("Serve per eliminare un oggetto e rimuoverlo dai salvati.");
    QHBoxLayout* b2 = new QHBoxLayout();
    b2->addWidget(l3);
    b2->addWidget(l4,Qt::AlignLeft);

    QLabel* l5 = new QLabel();
    l5->setPixmap(QPixmap(":/Icons/riutilizza.png").scaled(30,30));

    QLabel* l6 = new QLabel("Serve per riutilizzare un oggetto per un nuovo calcolo.");
    QHBoxLayout* b3 = new QHBoxLayout();
    b3->addWidget(l5);
    b3->addWidget(l6,Qt::AlignLeft);


    leglayout->addWidget(title,0,0,Qt::AlignCenter);
    leglayout->addWidget(text,1,0);
    leglayout->addLayout(b1,2,0);
    leglayout->addLayout(b2,3,0);
    leglayout->addLayout(b3,4,0);

    leg->setLayout(leglayout);



    //CREO LA CALCOLATRICE

    //PARTE SINISTRA
    layout->addWidget(strumenti,0,0);
    layout->addWidget(pietre,1,0);
    layout->addWidget(mosse,2,0);
    layout->addLayout(mostroamb,3,0);

    //PARTE CENTRALE
    layout->addWidget(display,0,1,4,1);
    layout->addWidget(ris,4,0,1,2);
    layout->addWidget(salv,5,0,1,2);


    //PARTE DESTRA
    layout->addWidget(funstr,0,2);
    layout->addWidget(funmostro,1,2);
    layout->addWidget(funpietra,2,2);
    layout->addLayout(funmossaamb,3,2);

    layout->addWidget(gestione,4,2);
    layout->addWidget(leg,5,2);

    setLayout(layout);

    //PARTE DI SIGNAL E SLOT

    //CREAZIONE OGGETTI
    connect(mostro, SIGNAL(pressed()), this, SLOT(newPopUpMostro()));
    connect(ambiente, SIGNAL(pressed()), this, SLOT(newPopUpAmbiente()));
    connect(etere, SIGNAL(pressed()), this, SLOT(newPopUpEtere()));
    connect(pozione, SIGNAL(pressed()), this, SLOT(newPopUpPozione()));
    connect(revitalizzante, SIGNAL(pressed()), this, SLOT(newPopUpRevitalizzante()));
    connect(bacca, SIGNAL(pressed()), this, SLOT(newPopUpBacca()));
    connect(caramella, SIGNAL(pressed()), this, SLOT(newPopUpCaramella()));
    connect(pietra, SIGNAL(pressed()), this, SLOT(newPopUpPietra()));
    connect(megapietra, SIGNAL(pressed()), this, SLOT(newPopUpMegaPietra()));
    connect(dannof, SIGNAL(pressed()), this, SLOT(newPopUpDannoFisico()));
    connect(dannos, SIGNAL(pressed()), this, SLOT(newPopUpDannoSpeciale()));
    connect(stato, SIGNAL(pressed()), this, SLOT(newPopUpMossaStato()));

    //SEGNALI FUNZIONE
    connect(reset, SIGNAL(pressed()), this, SLOT(resetS()));

    connect(usa, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(spremi, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(cucina, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(esponi, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(unisci, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(lucida, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(raffina, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(frammenta, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(attacca, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(megamossa, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(evolvi, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(sacrifica, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(esegui, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(inverti, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));
    connect(fusione, SIGNAL(funzionePremuta(string)), this, SLOT(catturaFunzione(string)));


    connect(annulla, SIGNAL(pressed()), this, SLOT(indietro()));
    connect(display, SIGNAL(reStart()), this, SLOT(reStartView()));
    connect(conferma, SIGNAL(pressed()), this, SLOT(toResult()));

    connect(this, SIGNAL(oggettoRisultato(pair<Oggetto*,QPixmap>)), this, SLOT(catturaRisultati(pair<Oggetto*,QPixmap>)));
    connect(this, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
}

MonsterKalk::~MonsterKalk(){

    delete controller;

    delete pozione;
    delete revitalizzante;
    delete etere;
    delete bacca;
    delete caramella;

    delete pietra;
    delete megapietra;

    delete dannof;
    delete dannos;
    delete stato;

    delete mostro;
    delete ambiente;

    delete usa;
    delete spremi;
    delete cucina;
    delete esponi;
    delete unisci;

    delete lucida;
    delete raffina;
    delete frammenta;

    delete attacca;
    delete megamossa;
    delete evolvi;
    delete sacrifica;

    delete esegui;
    delete inverti;
    delete fusione;

    delete annulla;
    delete reset;
    delete conferma;
    delete gr;
    delete display;
    delete risultati;
    delete salvati;



}

void MonsterKalk::disabilita(){
    QList<QAbstractButton*> lista= gr->buttons();
    for(auto it=lista.begin(); it<lista.end();it++){
        dynamic_cast<ImageButton*>(*it)->setEnabled(false);
    }
}


void MonsterKalk::abilita(){
    QList<QAbstractButton*> lista= gr->buttons();
    for(auto it=lista.begin(); it<lista.end();it++){
        dynamic_cast<ImageButton*>(*it)->setEnabled(true);
    }
}


//FUNZIONI
Oggetto* MonsterKalk::getLastAttuali() const{
    return controller->getLastAttuali();
}

//settare tutti i signal e slot, più specifici per ogni widget, tipo per ambiente..

void MonsterKalk::newPopUpMostro(){
    PopUpMostro* p= new PopUpMostro(Mostro::getSogliaSaluteMax(),Mostro::getSogliaStat(),Mostro::getSogliaEnergia(),Mostro::getRangoMax(), this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpAmbiente(){
    PopUpAmbiente* p= new PopUpAmbiente(this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpPozione(){
    PopUpPozione* p= new PopUpPozione(Mostro::getSogliaSaluteMax(), this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));

    p->setModal(true);
    p->exec();
    delete p;

}

void MonsterKalk::newPopUpEtere(){
    PopUpEtere* p= new PopUpEtere(Etere::getAumentoMax(),this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));

    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpRevitalizzante(){
    PopUpRevitalizzante* p= new PopUpRevitalizzante(this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}


void MonsterKalk::newPopUpBacca(){
    PopUpBacca* p= new PopUpBacca(Bacca::getMinCal(),Bacca::getMaxCal(),this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpCaramella(){
    PopUpCaramella* p= new PopUpCaramella(Caramella::getMinCal(),Caramella::getMaxCal(), Caramella::getMinQual(), Caramella::getMaxQual(),this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpPietra(){
    PopUpPietra* p= new PopUpPietra(Pietra::getMinLuc(), Pietra::getMaxLuc(),this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpMegaPietra(){
    PopUpMegaPietra* p= new PopUpMegaPietra(MegaPietra::getMinLuc(), Pietra::getMaxLuc(),this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpDannoFisico(){
    PopUpDannoFisico* p= new PopUpDannoFisico(this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpDannoSpeciale(){
    PopUpDannoSpeciale* p= new PopUpDannoSpeciale(Mostro::getSogliaEnergia(), this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

void MonsterKalk::newPopUpMossaStato(){
    PopUpMossaStato* p= new PopUpMossaStato(this);
    connect(p, SIGNAL(emetti(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(p, SIGNAL(emettiEccezione(string)), this, SLOT(catturaEccezione(string)));
    p->setModal(true);
    p->exec();
    delete p;
}

//deve invocare reset sul model e pulire display, risultati e salvati

void MonsterKalk::cleanDisplay(){
    display->clear();
    controller->freeAttuali();
}

void MonsterKalk::resetS(){
    abilita(); //abilita i bottoni delle funzioni
    display->clear();
    risultati->clear();
    salvati->clear();
    controller->reset();
}

//chiamata quando viene inserito un oggetto in stato di finale, deve cancellare ed eliminare gli attuali
void MonsterKalk::reStartView(){
    controller->reStart();
}

void MonsterKalk::reStart(){
    abilita();
    display->clear();
}
//tutti i metodi di set diventano un metodo unico
void MonsterKalk::setFunzione(string nome){
    controller->addFunzione(nome);
    disabilita(); 
}

void MonsterKalk::displayAdd(DisplayObject *oggetto){
    display->add(oggetto);
}
void MonsterKalk::salvatiAdd(DisplayObjectButton* oggetto){
    salvati->add(oggetto);
    connect(oggetto, SIGNAL(nuovoAttuale(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(oggetto, SIGNAL(eliminaSalvato(pair<DisplayObjectButton*, Oggetto*>)),this, SLOT(deletefromSalvati(pair<DisplayObjectButton*,Oggetto*>)));

}
void MonsterKalk::risultatiAdd(DisplayObjectButton* oggetto){
    risultati->add(oggetto);
    connect(oggetto, SIGNAL(nuovoAttuale(pair<Oggetto*,QPixmap>)), this, SLOT(catturaAttuali(pair<Oggetto*,QPixmap>)));
    connect(oggetto, SIGNAL(nuovoSalvato(pair<Oggetto*,QPixmap>)), this, SLOT(catturaSalvati(pair<Oggetto*,QPixmap>)));
}


void MonsterKalk::catturaAttuali(pair<Oggetto*,QPixmap> pair){
    controller->addAttuali(pair.first, pair.second);
}

void MonsterKalk::catturaSalvati(pair<Oggetto*,QPixmap> pair){
    controller->addSalvati(pair.first,pair.second);
}

void MonsterKalk::catturaRisultati(pair<Oggetto*,QPixmap> pair){
    controller->addRisultati(pair.first, pair.second);
}
void MonsterKalk::deletefromSalvati(pair<DisplayObjectButton*, Oggetto *> pair){
    //salvati->remove(pair.first);

    controller->deleteFromSalvati(pair.second);
    salvati->removeWidget(pair.first);
}

void MonsterKalk::indietro(){
    /*deve cancellare l'ultimo elemento che è stato aggiunto al display
     * -se questo è un oggetto allora deve eliminare questo oggetto dalla lista deglia attuali
     * -altrimenti deve settare invocare freeFlags e riattivare tutti i bottoni
     *
     */
    //non faccio nulla se sono in stato finale o se sullo schermo non c'è nulla
    if(!controller->getFlag("finale")){
        try{
            //c'è qulcosa in attuali ed è o un oggetto o  una funzione
            DisplayObject* rimosso= dynamic_cast<DisplayObject*>(display->removeLast());
            if(rimosso){
                 //non dealloca
                //rimosso dal display
                if(rimosso->isFunction()){
                    //allora è una funzione
                    controller->freeFlag();
                    //abilita i pulsanti funzione
                    abilita();
                }
                else{
                    //allora è un oggetto
                    controller->deleteFromAttuali(controller->getLastAttuali());

                }
                delete rimosso;
            }
            else{
                throw EccezioneGestione("nulla da cancellare");
            }
        }
        catch(const Eccezione& e){
            emit emettiEccezione(e.getMessaggio());
        }
        catch(...){
            emit emettiEccezione("errore di indietro");
        }
      }
}
////cattura le eccezioni che vengono spedite dalle varie parti
void MonsterKalk::catturaEccezione(std::string errore){
    display->add(errore);
    controller->setFlag("finale");
}


void MonsterKalk::catturaFunzione(string s){
    //riceve la flag del pulsante premuto
    controller->addFunzione(s);
    disabilita();
}



void MonsterKalk::toResult(){
    //deve ripulire i risultati, controllare quale flag di funzione è settata
    //controllare se il vector di attuali rispetta le precondizioni per attuare la funzione
    //ed in caso lanciare le eccezioni

    //se non è presente nessuna funzione, allora restituisce come risultati gli oggetti negli attuali
    //altrimenti ritorna i risultati delle funzioni, tutti sotto forma di signal.

    //setta finale a true

    if(!controller->getFlag("finale")){

        risultati->clear();
        controller->freeRisultati();

        vector<pair<Oggetto*, QPixmap>> ris;

        try{
            ris=controller->toResult();
        }
        catch(const EccezioneGestione& e){
            emit emettiEccezione(e.getMessaggio());
        }
        catch(const Eccezione& e){
            emit emettiEccezione(e.getMessaggio());
        }
        catch(...){
            emit emettiEccezione("eccezione toResult");
        }

        for(unsigned int i=0; i<ris.size();i++){
            emit oggettoRisultato(ris[i]);
        }
     }

    controller->setFlag("finale");
    abilita();
}






