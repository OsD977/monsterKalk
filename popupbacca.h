#ifndef POPUPBACCA_H
#define POPUPBACCA_H
#include <QDialog>
#include "slidervalue.h"
#include "widgetgusto.h"
#include "imagemenu.h"
#include "bacca.h"
#include "popup.h"
class PopUpBacca: public PopUp{
    Q_OBJECT
private:
    SliderValue* calorie;
    WidgetGusto* gusto;
    ImageMenu* sprite;
public:
    PopUpBacca(int minCal, int maxCal, QWidget* parent=nullptr);
    ~PopUpBacca();


public slots:
    void conferma();
};

#endif // POPUPBACCA_H
