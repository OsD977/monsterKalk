#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H
#include <QWidget>
#include <QGridLayout>

class DisplayObject: public QWidget{
private:
    bool funzione;
protected:
    QGridLayout* layout;
    QPixmap icona;
public:
    DisplayObject(QPixmap, QMap<QString,QString>, QWidget*parent=nullptr);
    DisplayObject(QPixmap, QWidget*parent=nullptr);
    virtual ~DisplayObject();
    bool isFunction() const;
    QPixmap getPix() const;
};

#endif // DISPLAYOBJECT_H
