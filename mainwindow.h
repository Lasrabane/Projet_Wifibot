#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "myrobot.h"

#include <QMainWindow>
#include <QWebEngineView>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

#include <QLabel>

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
    MyRobot ro; // Création de l'objet de type robot
    void avancer(); // Fonction faisant avancer le robot
    void reculer(); // Fonction faisant reculer le robot
    void droite(); // Fonction faisant tourner le robot à droite
    void gauche(); // Fonction faisant tourner le robot à gauche
    void stop(); // Fonction arrêtant le robot

    // Évènements attachés aux touches du clavier
    void keyPressEvent( QKeyEvent * event );
    void keyReleaseEvent( QKeyEvent * event );

private slots:
    // Attache les boutons de l'interface aux fonctions
    void on_disconnect_button_clicked();
    void on_connectButton_clicked();
    void on_avancerButton_pressed();
    void on_reculerButton_pressed();
    void on_gaucheButton_pressed();
    void on_droiteButton_pressed();
    void on_avancerButton_released();
    void on_droiteButton_released();
    void on_gaucheButton_released();
    void on_reculerButton_released();

    void on_cameraBas_clicked();
    void on_cameraGauche_clicked();
    void on_cameraHaut_clicked();
    void on_cameraDroite_clicked();

    // Récupère les valeurs des capteurs
    void captors_data(const QByteArray Data);
    };
#endif // MAINWINDOW_H
