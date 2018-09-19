#include "popup.h"

PopUp::PopUp(QWidget *parent):QDialog(parent){

    //PULSANTI DI GESTIONE
    QSize size = QSize(100,40);
    annullaButton= new  ImageButton("Cancella",":Icons/annulla.png",size);
    confermaButton= new ImageButton("Conferma",":/Icons/conferma.png",size);

    box = new QHBoxLayout();
    box->addWidget(annullaButton);
    box->addWidget(confermaButton);

    //SIGNAL E SLOT
    connect(annullaButton, SIGNAL(pressed()), this, SLOT(close()));
    connect(confermaButton, SIGNAL(pressed()), this, SLOT(conferma()));


}

PopUp::~PopUp(){
    delete annullaButton;
    delete confermaButton;
}

