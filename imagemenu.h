#ifndef IMAGEMENU_H
#define IMAGEMENU_H
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <vector>
#include <QComboBox>
class ImageMenu: public QWidget{
    Q_OBJECT
private:
    QLabel* act;
    std::vector<QPixmap> immagini;
    QComboBox* myCombo;
    QPixmap attiva;
public:
    ImageMenu(std::vector<QPixmap> immagini, QString prefix, QWidget* parent=nullptr);
    ~ImageMenu();
    QPixmap getImg() const;
public slots:
    void mySlot(int idx);
};

#endif // IMAGEMENU_H
