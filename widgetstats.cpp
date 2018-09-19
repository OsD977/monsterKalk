#include "widgetstats.h"
#include <QGridLayout>
#include "typebutton.h"
WidgetStats::WidgetStats(QWidget *parent): QWidget(parent){

    QGridLayout* layout = new QGridLayout();
    QSize size = QSize(100,50);
    TypeButton* attacco = new TypeButton("Attacco",":/Icons/attacco.png",size);
    TypeButton* difesa = new TypeButton("Difesa",":/Icons/difesa.png",size);
    TypeButton* attacco_sp = new TypeButton("Attacco_speciale",":/Icons/attacco_sp.png",size);
    TypeButton* difesa_sp = new TypeButton("Difesa_speciale",":/Icons/difesa_sp.png",size);


    connect(attacco, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(difesa, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(attacco_sp, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));
    connect(difesa_sp, SIGNAL(insertValue(std::string)), this, SLOT(insert(std::string)));


    layout->addWidget(attacco,0,0);
    layout->addWidget(attacco_sp,0,1);
    layout->addWidget(difesa,1,0);
    layout->addWidget(difesa_sp,1,1);

    setLayout(layout);


}

void WidgetStats::insert(std::string s){
    stats.push_back(s);
}

std::vector<std::string> WidgetStats::getStats() const{
    return stats;
}
