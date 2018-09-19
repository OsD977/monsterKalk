#include <QApplication>
#include "monsterkalk.h"
#include"model.h"
#include"controller.h"
#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    //Controller* controller=new Controller();
    MonsterKalk* kalk= new MonsterKalk();
    kalk->show();
    return app.exec();
    delete kalk;

}
