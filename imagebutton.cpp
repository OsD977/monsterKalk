#include "imagebutton.h"
#include "QPixmap"
ImageButton::ImageButton(QString text, QString path, QSize size, QWidget* parent):QPushButton(parent){
    QPixmap pix(path);

    //setStyleSheet("QToolButton {border: 1px solid #8f8f91;}");
    setStyleSheet("text-align:center;font-size: 12px;");

    //setPushButtonStyle(Qt::PushButtonTextUnderIcon);
    setLayoutDirection(Qt::LeftToRight);
    setIcon(pix);
    QSize sizeicon(size.width()-22, size.height()-22);
    setIconSize(sizeicon);
    setText(text);
    setFixedSize(size);

    //setObjectName(text); se serve

}


