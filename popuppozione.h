#ifndef POPUPPOZIONE_H
#define POPUPPOZIONE_H
#include <QDialog>
#include "widgetformato.h"
#include "slidervalue.h"
#include "imagemenu.h"
#include "pozione.h"
#include "imagebutton.h"
#include "popup.h"

class PopUpPozione:public PopUp{
    Q_OBJECT
private:
    WidgetFormato* formati;
    SliderValue* salute;
    ImageMenu* sprite;
public:
    PopUpPozione(int sogliaMax, QWidget* parent=nullptr);
    ~PopUpPozione();

public slots:
    void conferma();


};

#endif // POPUPPOZIONE_H
