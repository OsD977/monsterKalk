#ifndef WIDGETFORMATO_H
#define WIDGETFORMATO_H
#include <QWidget>
#include <QComboBox>
class WidgetFormato:public QWidget{
private:
    QComboBox* formati;
public:
    WidgetFormato(QWidget* parent = nullptr);
    ~WidgetFormato();
    std::string getSelected() const;
};

#endif // WIDGETFORMATO_H
