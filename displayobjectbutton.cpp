#include "displayobjectbutton.h"
#include <math.h>
DisplayObjectButton::DisplayObjectButton(QString path1, QString path2, Oggetto* obj,bool salvati,QPixmap icon,
                                         QMap<QString,QString> map, QWidget* parent):DisplayObject(icon,map,parent), oggetto(obj){
    QIcon iconb1 = QIcon(path1);
    QIcon iconb2 = QIcon(path2);
    //annulla o salva
    b1 = new QPushButton();
    //riutilizza
    b2 = new QPushButton();
    if (path1==":/Icons/elimina.png")
        b1->setToolTip("Elimina");
    else if (path1==":/Icons/salva.png")
        b1->setToolTip("Salva");
    b2->setToolTip("Riutilizza");

    b1->setIcon(iconb1);
    b2->setIcon(iconb2);

    QHBoxLayout* box = new QHBoxLayout();
    box->addWidget(b1);
    box->addWidget(b2);

    layout->addLayout(box,1,0,1,ceil(static_cast<double>(map.size())/6)+1,Qt::AlignCenter);

    connect(b2, SIGNAL(pressed()), this, SLOT(emettiAttuali()));
    if(salvati)
        connect(b1, SIGNAL(pressed()), this, SLOT(emettiEliminaSalvati()));
    else
        connect(b1, SIGNAL(pressed()), this, SLOT(emettiSalva()));

}

DisplayObjectButton::~DisplayObjectButton(){
    delete b1;
    delete b2;
}

void DisplayObjectButton::emettiAttuali(){
    //deve clonare il mostro e mandarlo sul display
    emit nuovoAttuale(pair<Oggetto*, QPixmap>(oggetto->clone(), getPix()));

}

void DisplayObjectButton::emettiSalva(){
    emit nuovoSalvato(pair<Oggetto*, QPixmap>(oggetto->clone(), getPix()));
}

void DisplayObjectButton::emettiEliminaSalvati(){
   //deve eliminarsi
    emit eliminaSalvato(pair<DisplayObjectButton*, Oggetto*>(this,oggetto));
}
