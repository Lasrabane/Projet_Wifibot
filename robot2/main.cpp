#include "mainwindow.h"
#include "myrobot.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MyRobot ro = MyRobot();
    ro.doConnect();
    return a.exec();
}
