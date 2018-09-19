#ifndef POPUPMOSSASTATO_H
#define POPUPMOSSASTATO_H
#include <QDialog>
#include <widgettipo.h>
#include <slidervalue.h>
#include <QRadioButton>
#include "widgetstats.h"
#include "imagemenu.h"
#include "stato.h"
#include <QButtonGroup>
#include "popup.h"
class PopUpMossaStato:public PopUp{
     Q_OBJECT
private:
    WidgetTipo* tipo;
    WidgetStats* stats;
    SliderValue* precisione;
    SliderValue* delta;
    QButtonGroup* gruppo;
    QRadioButton* selfsi;
    QRadioButton* selfno;
    ImageMenu* sprite;

public:
    PopUpMossaStato(QWidget* parent=nullptr);
    ~PopUpMossaStato();

public slots:
    void conferma();
};

#endif // POPUPMOSSASTATO_H
