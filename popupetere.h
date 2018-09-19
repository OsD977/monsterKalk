#ifndef POPUPETERE_H
#define POPUPETERE_H
#include <QDialog>
#include "widgetformato.h"
#include "slidervalue.h"
#include "widgetstats.h"
#include "etere.h"
#include "imagemenu.h"
#include "popup.h"
class PopUpEtere:public PopUp{
    Q_OBJECT
private:
    WidgetFormato* formati;
    SliderValue* aum;
    WidgetStats* stats;
    ImageMenu* sprite;
public:
    PopUpEtere(int maxAum, QWidget* parent = nullptr);
    ~PopUpEtere();

public slots:
    void conferma();
};

#endif // POPUPETERE_H
