#ifndef WIDGETSTATS_H
#define WIDGETSTATS_H
#include <QWidget>
#include <vector>
class WidgetStats:public QWidget{
    Q_OBJECT
private:
    std::vector<std::string> stats;
public:
    WidgetStats(QWidget* parent=nullptr);
    std::vector<std::string> getStats() const;
signals:
    void insertValue(std::string);
public slots:
    void insert(std::string);
};

#endif // WIDGETSTATS_H
