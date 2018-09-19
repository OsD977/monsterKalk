#ifndef SLIDERVALUE_H
#define SLIDERVALUE_H
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <vector>

class SliderValue: public QWidget{
    friend class PopUpMostro;
private:
    QSlider slider;
    std::vector<std::string> tipi;
public:
    SliderValue(QString testo, int min, int max, QWidget* parent=0);
    //SliderValue(){}
    QSpinBox spinner;
    QLabel label;
    int getValue() const;
    void setSlider(int min, int max);
};

#endif // SLIDERVALUE_H
