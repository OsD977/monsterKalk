#ifndef POPUP_H
#define POPUP_H
#include <QDialog>
#include "slidervalue.h"
#include "imagebutton.h"
#include "imagemenu.h"
#include "oggetto.h"
#include <QHBoxLayout>


class PopUp:public QDialog{
    Q_OBJECT
public:
    PopUp(QWidget* parent=nullptr);
    ~PopUp();
    ImageButton* annullaButton;
    ImageButton* confermaButton;
protected:
    QHBoxLayout* box;
signals:
    void emetti(pair<Oggetto*, QPixmap>);
    void emettiEccezione(string);
public slots:
    virtual void conferma()=0;


};

#endif // POPUP_H
