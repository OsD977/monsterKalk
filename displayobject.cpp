#include "displayobject.h"
#include <QLabel>
#include <QPixmap>
#include <QMap>
#include <math.h>
#include <string>
#include <QString>
#include <QPainter>
#include <QStyleOption>

DisplayObject::DisplayObject(QPixmap icon, QMap<QString,QString> map, QWidget* parent): QWidget(parent), icona(icon){

    funzione=false;
    setObjectName("fix");
    layout = new QGridLayout();
    QGridLayout* layoutdx = new QGridLayout();
    QLabel* label = new QLabel();
    label->setPixmap(icon);


    layout->addWidget(label,0,0);

        auto it = map.constBegin();

        for (int j=0; j<ceil(static_cast<double>(map.size())/5); j++){
            for (int i=0; i<5 && it!=map.constEnd(); i++,it++){
                QLabel* valore = new QLabel();
                valore->setText(it.key()+": "+it.value());
                layoutdx->addWidget(valore,i,j,Qt::AlignLeft);
            }
        }

    layout->addLayout(layoutdx,0,1,Qt::AlignLeft);

    setLayout(layout);

}

DisplayObject::DisplayObject(QPixmap icon, QWidget *parent):QWidget(parent){

    funzione=true;

    QGridLayout* layout = new QGridLayout();

    QLabel* label = new QLabel();
    label->setPixmap(icon);

    layout->addWidget(label,0,1,Qt::AlignCenter);

    setLayout(layout);

}

DisplayObject::~DisplayObject(){
    //delete layout;
}


bool DisplayObject::isFunction() const{
    return funzione;
}


QPixmap DisplayObject::getPix() const{
    return icona;
}
