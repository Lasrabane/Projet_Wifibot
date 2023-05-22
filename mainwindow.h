#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "myrobot.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyRobot ro;
    void Camera();

private slots:
    //Modifier les noms
    void on_disconnect_button_clicked();
    void on_connectButton_clicked();
    void on_avancerButton_pressed();
    void on_reculerButton_pressed();
    void on_gaucheButton_pressed();
    void on_droiteButton_pressed();
};
#endif // MAINWINDOW_H
