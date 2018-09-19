#ifndef TYPEBUTTON_H
#define TYPEBUTTON_H
#include <QToolButton>

class TypeButton: public QToolButton{
    Q_OBJECT
private:
    std::string testo;
    QPixmap icona;
public:
    TypeButton(std::string tipo, QString icona, QSize size, QWidget* parent=nullptr);
signals:
    void insertValue(std::string);
    void removeValue(std::string);
public slots:
    void changeButton();
    void resetButton();
};

#endif // TYPEBUTTON_H
