#ifndef FUNCTIONBUTTON_H
#define FUNCTIONBUTTON_H
#include "imagebutton.h"
#include <string>
using namespace std;

class FunctionButton: public ImageButton{
    Q_OBJECT
private:
    std::string flag;
public:
    FunctionButton(QString,QString,QSize, std::string flag,QWidget* parent=nullptr);
signals:
    void funzionePremuta(string);
public slots:
    void premuto();
};

#endif // FUNCTIONBUTTON_H
