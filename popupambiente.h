#ifndef POPUPAMBIENTE_H
#define POPUPAMBIENTE_H
#include <QDialog>
#include "widgettipo.h"
#include "slidervalue.h"
#include "imagemenu.h"
#include "ambiente.h"
#include "popup.h"

class PopUpAmbiente:public PopUp{
    Q_OBJECT
private:
    WidgetTipo* potenziati;
    WidgetTipo* depotenziati;
    SliderValue* percentuale_aum;
    SliderValue* percentuale_dec;
    ImageMenu* sprite;
public:
    PopUpAmbiente(QWidget* parent=nullptr);
    ~PopUpAmbiente();

public slots:
    void conferma();
};

#endif // POPUPAMBIENTE_H
