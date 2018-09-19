#include "typebutton.h"
#include <QToolTip>
TypeButton::TypeButton(std::string text, QString path, QSize size, QWidget* pa): QToolButton(pa),testo(text){
    setToolTip(QString::fromStdString(text));
    icona= QPixmap(path);
    setIcon(icona);
    setIconSize(size);
    setStyleSheet("QToolButton {border:none;}");
    QObject::connect(this, SIGNAL(pressed()), this, SLOT(changeButton()));

}

void TypeButton::changeButton(){
   setEnabled(false);
   emit insertValue(testo);
}

void TypeButton::resetButton(){
    setEnabled(true);
    emit removeValue(testo);
}
