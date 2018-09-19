#ifndef WIDGETGUSTO_H
#define WIDGETGUSTO_H
#include <QWidget>
#include <QComboBox>
class WidgetGusto:public QWidget{
private:
    QComboBox* gusti;
public:
    WidgetGusto(QWidget* parent = nullptr);
    ~WidgetGusto();
    std::string getGusto() const;
};

#endif // WIDGETGUSTO_H
