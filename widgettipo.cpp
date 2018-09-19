#include "widgettipo.h"
#include <QGridLayout>
#include <iostream>
#include "eccezionemostro.h"
WidgetTipo:: WidgetTipo(QWidget* parent): QWidget(parent){

    QString dragon(":/Icons/dragon.png");
    QString electric(":/Icons/electric.png");
    QString fighting(":/Icons/fighting.png");
    QString fire(":/Icons/fire.png");
    QString flying(":/Icons/flying.png");
    QString ghost(":/Icons/ghost.png");
    QString grass(":/Icons/grass.png");
    QString steel(":/Icons/steel.png");
    QString water(":/Icons/water.png");

    setStyleSheet("TypeButton {border:none;}");
    int altezza=64;
    int larghezza=64;
    QSize a(altezza, larghezza);


    butdrag = new TypeButton("Drago", dragon, a);
    butelec = new TypeButton("Elettro", electric, a);
    butfight = new TypeButton("Lotta", fighting, a);
    butfire = new TypeButton("Fuoco", fire, a);
    butflying = new TypeButton("Volante", flying, a);
    butghost = new TypeButton("Spettro", ghost, a);
    butgrass = new TypeButton("Erba", grass, a);
    butsteel = new TypeButton("Acciaio", steel, a);
    butwater = new TypeButton("Acqua", water, a);

    //collegati allo slot per aggiornare questo vettore

    connect(butdrag, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(butelec, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(butfight, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));

    connect(butfire, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(butflying, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(butghost, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));

    connect(butgrass, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(butsteel, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(butwater, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));

    connect(butdrag, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));
    connect(butelec, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));
    connect(butfight, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));

    connect(butfire, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));
    connect(butflying, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));
    connect(butghost, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));

    connect(butgrass, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));
    connect(butsteel, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));
    connect(butwater, SIGNAL(removeValue(std::string)), this, SLOT(remove(std::string)));

    QGridLayout* layout = new QGridLayout();


    layout->addWidget(butgrass,0,0);
    layout->addWidget(butfire,0,1);
    layout->addWidget(butwater,0,2);

    layout->addWidget(butsteel,1,0);
    layout->addWidget(butelec,1,1);
    layout->addWidget(butghost,1,2);

    layout->addWidget(butflying,2,0);
    layout->addWidget(butfight,2,1);
    layout->addWidget(butdrag,2,2);
    setLayout(layout);
}

WidgetTipo::~WidgetTipo(){
    delete butgrass;
    delete butfire;
    delete butwater;
    delete butsteel;
    delete butelec;
    delete butghost;
    delete butflying;
    delete butfight;
    delete butdrag;
}

void WidgetTipo::insert(std::string s){
    types.push_back(s);
}
void WidgetTipo::remove(std::string s){
    for(auto it=types.begin(); it!=types.end(); ++it){
        if(*it==s){
            it=types.erase(it); //non serve usare la delete perché è una stringa
            it--;
        }
    }
}

std::vector<std::string> WidgetTipo::getTypes() const{
    return types;
}

void WidgetTipo::bound(WidgetTipo* w) const{
    connect(butgrass, SIGNAL(pressed()), w->butgrass, SLOT(resetButton()));
    connect(butfire, SIGNAL(pressed()), w->butfire, SLOT(resetButton()));
    connect(butwater, SIGNAL(pressed()), w->butwater, SLOT(resetButton()));

    connect(butsteel, SIGNAL(pressed()), w->butsteel, SLOT(resetButton()));
    connect(butelec, SIGNAL(pressed()), w->butelec, SLOT(resetButton()));
    connect(butghost, SIGNAL(pressed()), w->butghost, SLOT(resetButton()));

    connect(butflying, SIGNAL(pressed()), w->butflying, SLOT(resetButton()));
    connect(butfight, SIGNAL(pressed()), w->butfight, SLOT(resetButton()));
    connect(butdrag, SIGNAL(pressed()), w->butdrag, SLOT(resetButton()));
}

bool WidgetTipo::vuoto() const{
    return types.size()==0;
}
