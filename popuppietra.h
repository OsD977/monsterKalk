#ifndef POPUPPIETRA_H
#define POPUPPIETRA_H
#include <QDialog>
#include "slidervalue.h"
#include "imagemenu.h"
#include "pietra.h"
#include "popup.h"

class PopUpPietra: public PopUp{
    Q_OBJECT
private:
    SliderValue* lucentezza;
    SliderValue* rischio_rottura;
    ImageMenu* sprite;
public:
    PopUpPietra(int minLuc, int maxLuc, QWidget* parent=0);
    ~PopUpPietra();

public slots:
    void conferma();
};

#endif // POPUPPIETRA_H
