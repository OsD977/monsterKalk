#ifndef POPUPMOSTRO_H
#define POPUPMOSTRO_H
#include <QDialog>
#include <QVector>
#include "slidervalue.h"
#include "widgettipo.h"
#include "mostro.h"
#include <QButtonGroup>
#include <QRadioButton>
#include "imagemenu.h"
#include <QPixmap>
#include "popup.h"
class PopUpMostro:public PopUp{
    Q_OBJECT
private:
    QVector<QString> types; // il vettore in cui aggiungo
    SliderValue* salute_max;
    SliderValue* salute_attuale;
    SliderValue* attacco;
    SliderValue* difesa;
    SliderValue* attacco_speciale;
    SliderValue* difesa_speciale;
    SliderValue* energia;
    SliderValue* rango;
    WidgetTipo* tipi;
    QRadioButton* b1;
    QRadioButton* b2;
    QButtonGroup * gruppo;
    ImageMenu* sprite;
public:
    PopUpMostro(int smax=1, int sogliaStatMa=1, int energiaMax=1, int rangoMax=1,QWidget *parent=nullptr);
    ~PopUpMostro();

public slots:
    void conferma();

};

#endif // POPUPMOSTRO_H
