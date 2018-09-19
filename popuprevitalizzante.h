#ifndef POPUPREVITALIZZANTE_H
#define POPUPREVITALIZZANTE_H
#include <QDialog>
#include "widgetformato.h"
#include "slidervalue.h"
#include "imagemenu.h"
#include  "revitalizzante.h"
#include "popup.h"
class PopUpRevitalizzante:public PopUp{
    Q_OBJECT
private:
    WidgetFormato* formati;
    SliderValue* vita;
    ImageMenu* sprite;
public:
    PopUpRevitalizzante(QWidget* parent=nullptr);
    ~PopUpRevitalizzante();

public slots:
    void conferma();
};

#endif // POPUPREVITALIZZANTE_H
