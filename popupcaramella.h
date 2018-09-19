#ifndef POPUPCARAMELLA_H
#define POPUPCARAMELLA_H
#include <QDialog>
#include "slidervalue.h"
#include "widgetgusto.h"
#include "caramella.h"
#include "imagemenu.h"
#include "popup.h"
class PopUpCaramella:public PopUp{
    Q_OBJECT
private:
    SliderValue* calorie;
    SliderValue* qualita;
    WidgetGusto* gusto;
    ImageMenu* sprite;
public:
    PopUpCaramella(int minCal, int maxCal, int minQual, int maxQual, QWidget *parent=nullptr);
    ~PopUpCaramella();

public slots:
    void conferma();
};

#endif // POPUPCARAMELLA_H
