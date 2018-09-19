#ifndef WIDGETTIPO_H
#define WIDGETTIPO_H
#include <QWidget>
#include <vector>
#include "typebutton.h"

class WidgetTipo: public QWidget{
    Q_OBJECT
private:
     std::vector<std::string> types;
     TypeButton* butdrag;
     TypeButton* butelec;
     TypeButton* butfight;
     TypeButton* butfire;
     TypeButton* butflying;
     TypeButton* butghost;
     TypeButton* butgrass;
     TypeButton* butsteel;
     TypeButton* butwater;
public:
     ~WidgetTipo();
     WidgetTipo(QWidget* parent=0);
     std::vector<std::string> getTypes() const;
     void bound(WidgetTipo* w) const;
     bool vuoto() const;
public slots:
     void insert(std::string);
     void remove(std::string);
};

#endif // WIDGETTIPO_H
