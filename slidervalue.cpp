#include "slidervalue.h"
#include "funzioni.h"

SliderValue::SliderValue(QString testo, int min, int max, QWidget* parent): QWidget(parent){
    label.setText(testo);
    slider.setRange(min, max);
    spinner.setRange(min,max);
    QObject::connect(&slider, SIGNAL(valueChanged(int)), &spinner, SLOT(setValue(int)));
    QObject::connect(&spinner, SIGNAL(valueChanged(int)), &slider, SLOT(setValue(int)));

    slider.setValue((max+min)/2);
    QGridLayout* layout = new QGridLayout();
    slider.setOrientation(Qt::Horizontal);
    layout->addWidget(&label,0,0);
    layout->addWidget(&slider,0,1,1,1,Qt::AlignLeft);
    layout->addWidget(&spinner,0,2);

    this->setLayout(layout);
}

void SliderValue::setSlider(int min, int max){
    slider.setRange(min,max);
}

int SliderValue::getValue() const{
    return slider.value();
}
