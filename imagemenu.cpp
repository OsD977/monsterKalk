#include "imagemenu.h"
#include <QGridLayout>

//passare il prefisso delle immagini, le immagini
ImageMenu::ImageMenu(std::vector<QPixmap> imm, QString prefix, QWidget* par): QWidget(par), immagini(imm){
    act= new QLabel();
    attiva= imm[0];
    act->setPixmap(imm[0]);
    QGridLayout* layout= new QGridLayout();
    myCombo= new QComboBox();
    for(unsigned int i=0; i<imm.size(); ++i){
        QString text= prefix+QString::number(i+1); //controllare se funziona
        myCombo->addItem(imm[i], text);
    }
    //devo collegare il cambiamento dell'opzione al caricamento di un'immagine differente
    QObject::connect (myCombo, SIGNAL(activated(int)), this, SLOT(mySlot(int)));
    layout->addWidget(myCombo,0,0);
    layout->addWidget(act,1,0,Qt::AlignCenter);
    setLayout(layout);
}

ImageMenu::~ImageMenu(){
    delete act;
    delete myCombo;
}

QPixmap ImageMenu::getImg() const{
    return attiva;
}

void ImageMenu::mySlot(int idx){
    QString path=":/Icons/"+myCombo->itemText(idx)+".png";
    attiva= QPixmap(path);
    act->setPixmap(attiva);
}
