#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H
#include <QPushButton>

class ImageButton:public QPushButton{
    Q_OBJECT
public:
    ImageButton(QString,QString,QSize,QWidget* parent=nullptr);
signals:
    void insertValue(std::string);
};

#endif // IMAGEBUTTON_H
