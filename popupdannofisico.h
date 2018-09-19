#ifndef POPUPDANNOFISICO_H
#define POPUPDANNOFISICO_H
#include <QDialog>
#include "widgettipo.h"
#include "slidervalue.h"
#include <QRadioButton>
#include "imagemenu.h"
#include "dannofisico.h"
#include <QButtonGroup>
#include "popup.h"
class PopUpDannoFisico:public PopUp{
       Q_OBJECT
private:
    WidgetTipo* tipo;
    SliderValue* precisione;
    SliderValue* potenza;
    SliderValue* collaterale;
    QButtonGroup* gruppo;
    QRadioButton* areasi;
    QRadioButton* areano;
    ImageMenu* sprite;
public:
    PopUpDannoFisico(QWidget* parent=0);
    ~PopUpDannoFisico();

public slots:
    void conferma();
};

#endif // POPUPDANNOFISICO_H
