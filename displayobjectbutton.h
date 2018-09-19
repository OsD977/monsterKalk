#ifndef DISPLAYOBJECTBUTTON_H
#define DISPLAYOBJECTBUTTON_H
#include "displayobject.h"
#include "typebutton.h"
#include <QString>
#include <QMap>
#include <QPushButton>
#include "oggetto.h"
class DisplayObjectButton:public DisplayObject{
    Q_OBJECT
private:
    QPushButton* b1;
    QPushButton* b2;
    Oggetto* oggetto;

public:
    DisplayObjectButton(QString path1, QString path2, Oggetto* oggetto,bool salvati, QPixmap icon, QMap<QString,QString> map, QWidget* parent=nullptr);
    ~DisplayObjectButton();

signals:
    void nuovoAttuale(pair<Oggetto*, QPixmap>);
    void nuovoSalvato(pair<Oggetto*, QPixmap>);
    void eliminaSalvato(pair<DisplayObjectButton*,Oggetto*>);
public slots:
    //emette un clone dell'oggetto ospitato
    void emettiAttuali();

    void emettiSalva();

    void emettiEliminaSalvati();
};

#endif // DISPLAYOBJECTBUTTON_H
