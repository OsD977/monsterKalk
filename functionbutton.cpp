#include "functionbutton.h"

FunctionButton::FunctionButton(QString a, QString b , QSize s, std::string flag_, QWidget *parent):ImageButton(a,b,s,parent), flag(flag_) {
    connect(this, SIGNAL(pressed()), this, SLOT(premuto()));
}

void FunctionButton::premuto(){
    emit funzionePremuta(flag);
}
