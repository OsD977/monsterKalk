#include "widgetformato.h"
#include "QComboBox"
#include <QHBoxLayout>
WidgetFormato::WidgetFormato(QWidget *parent): QWidget(parent){

    QHBoxLayout* layout = new QHBoxLayout();
    formati = new QComboBox();

    formati->addItem("Sciroppo");
    formati->addItem("Crema");
    formati->addItem("Polvere");
    formati->addItem("Compressa");

    layout->addWidget(formati);
    setLayout(layout);
}

WidgetFormato::~WidgetFormato(){
    delete formati;
}

std::string WidgetFormato::getSelected() const{
    return (formati->currentText()).toStdString();
}
