#ifndef DISPLAY_H
#define DISPLAY_H
#include <QScrollArea>
#include "displayobject.h"
#include <QLayout>
#include <vector>
class Display:public QScrollArea{
    Q_OBJECT
private:
    std::vector<QWidget*> widgets;
    QFrame* frame;
    QVBoxLayout* layout;
    QBoxLayout* box;
public:
    Display(QFlags<Qt::Orientation> orientation,QWidget* parent=nullptr);
    ~Display();
    void add(DisplayObject* oggetto);
    void add(std::string errore);
    void clear();
    QWidget* removeLast();
    void removeWidget(QWidget*);
signals:
    void reStart();
};

#endif // DISPLAY_H
