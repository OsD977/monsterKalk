#ifndef POPUPDANNOSPECIALE_H
#define POPUPDANNOSPECIALE_H
#include <QDialog>
#include "widgettipo.h"
#include "slidervalue.h"
#include <QRadioButton>
#include "imagemenu.h"
#include "dannospeciale.h"
#include <QButtonGroup>
#include "popup.h"
class PopUpDannoSpeciale:public PopUp{
    Q_OBJECT
private:
    WidgetTipo* tipo;
    SliderValue* precisione;
    SliderValue* potenza;
    SliderValue* energia_richiesta;
    QButtonGroup* gruppo;
    QRadioButton* areasi;
    QRadioButton* areano;
    ImageMenu* sprite;
public:
    PopUpDannoSpeciale(int sogliaEnergia, QWidget* parent=0);
    ~PopUpDannoSpeciale();

public slots:
    void conferma();
};

#endif // POPUPDANNOSPECIALE_H
