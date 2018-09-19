#include "display.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QFlags>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
Display::Display(QFlags<Qt::Orientation> orientation, QWidget *parent):QScrollArea(parent){

    setWidgetResizable(true);
    layout = new QVBoxLayout();
    frame = new QFrame();

    //DISPLAY ORIZZONTALE: RISULTATI E SALVATI
    if (orientation == Qt::Horizontal){
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        box = new QHBoxLayout();
        frame->setLayout(box);
        frame->setStyleSheet("QFrame, QLabel {background-color: white;font-size: 10px;}");
        box->setAlignment(Qt::AlignLeft);
        setWidget(frame);
        setLayout(layout);
    }
    //DISPLAY VERTICALE: ATTUALI
    else{
        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        box = new QVBoxLayout();
        frame->setLayout(box);
        frame->setStyleSheet("QFrame, QLabel {background-color: white;font-size: 10px;}");
        box->setAlignment(Qt::AlignTop);
        setWidget(frame);
        setLayout(layout);
    }
}

Display::~Display(){
    delete frame;
    delete layout;
    delete box;

    for (unsigned int i =0; i<widgets.size(); i++){
        delete widgets[i];
    }
}


void Display::add(DisplayObject* obj){
    widgets.push_back(obj);
    widget()->layout()->addWidget(obj);
}


void Display::add(std::string text){
    QLabel* testo = new QLabel(QString::fromStdString(text),this);
    testo->setWordWrap(true);
    testo->setStyleSheet("font-size: 12px; border:1px solid lightgray; border-radius: 4px;");

    widgets.push_back(testo);
    widget()->layout()->addWidget(testo);
}


QWidget *Display::removeLast(){
    //deve rimuovere l'ultimo oggetto inserito e ritornarlo
    if(widgets.size()==0)
        return nullptr;
    QWidget* ris= widgets[widgets.size()-1];
    widget()->layout()->removeWidget(ris);
    widgets.erase(--widgets.end());
    return ris;
}


void Display::clear(){
    for(auto it=widgets.begin(); it!=widgets.end();++it){
        widget()->layout()->removeWidget(*it);
        delete *it;
        it=widgets.erase(it);
        it--;
    }
}


void Display::removeWidget(QWidget* w){
    widget()->layout()->removeWidget(w);
    for (std::vector<QWidget*>::iterator it= widgets.begin(); it!= widgets.end(); ++it){
        if(*it==w){
            delete *it;
            it=widgets.erase(it);
            it--;
        }
    }
}


