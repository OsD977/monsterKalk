#include "widgetgusto.h"
#include <QHBoxLayout>
WidgetGusto::WidgetGusto(QWidget *parent): QWidget(parent){

    QHBoxLayout* box = new QHBoxLayout(this);
    gusti=new QComboBox(this);
    gusti->addItem("Dolce");
    gusti->addItem("Salato");
    gusti->addItem("Pepato");
    gusti->addItem("Aspro");
    gusti->addItem("Amaro");

    box->addWidget(gusti);

    setLayout(box);

}

WidgetGusto::~WidgetGusto(){
    delete gusti;
}

std::string WidgetGusto::getGusto() const{
    return (gusti->currentText()).toStdString();
}
