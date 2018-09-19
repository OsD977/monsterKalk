#ifndef POPUPMEGAPIETRA_H
#define POPUPMEGAPIETRA_H
#include <QDialog>
#include "widgettipo.h"
#include "slidervalue.h"
#include "megapietra.h"
#include "imagemenu.h"
#include "popup.h"
class PopUpMegaPietra:public PopUp{
    Q_OBJECT
private:
    WidgetTipo* tipo;
    SliderValue* lucentezza;
    SliderValue* rischio_rottura;
    ImageMenu* sprite;
public:
    PopUpMegaPietra(int minLuc, int maxLuc, QWidget *parent=nullptr);
    ~PopUpMegaPietra();

public slots:
    void conferma();
};

#endif // POPUPMEGAPIETRA_H
