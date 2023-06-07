#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include <QWebEngineView>
#include <QKeyEvent>
#include <QBoxLayout>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

//#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebEngineView *webEngineV = new QWebEngineView();
    webEngineV->resize(300, 300);
    QUrl url = QUrl("http://192.168.1.106:8080/?action=stream");
    webEngineV->load(url);
    webEngineV->setParent(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_disconnect_button_clicked()
{
    ro.disConnect();
}


void MainWindow::on_connectButton_clicked()
{
    ro.doConnect();
}

unsigned  short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);


void MainWindow::on_avancerButton_pressed()
{
    // read the data from the socket
    qDebug() << "avance____";
    ro.DataToSend[0] = 0xFF;
    ro.DataToSend[1] = 0x07;
    ro.DataToSend[2] = 150;    //Vitesse roue gauche
    ro.DataToSend[3] = 0;    //Vitesse roue gauche
    ro.DataToSend[4] = 150;    //Vitesse roue droite
    ro.DataToSend[5] = 0;    //Vitesse roue droite
    ro.DataToSend[6] = 80;    //Direction 80 droit,  64 droite, 16 gauche, 0 reculer

    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);
}


unsigned short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;

    Crc = 0xFFFF;
    Polynome = 0xA001;

    for(CptOctet = 1 ; CptOctet < Taille_max ; CptOctet ++)
    {
        Crc ^= *(Adresse_tab + CptOctet);
            for(CptBit =  0; CptBit <= 7 ; CptBit ++)
        {
            Parity = Crc;
            Crc >>=1;
            if(Parity%2 == true) Crc ^= Polynome;
        }
    }
    return Crc;
}


void MainWindow::on_gaucheButton_pressed()
{
    qDebug() << "gauche____";
    // read the data from the socket
    ro.DataToSend[0] = 0xFF;
    ro.DataToSend[1] = 0x07;
    ro.DataToSend[2] = 150;    //Vitesse roue gauche
    ro.DataToSend[3] = 0;    //Vitesse roue gauche
    ro.DataToSend[4] = 150;    //Vitesse roue droite
    ro.DataToSend[5] = 0;    //Vitesse roue droite
    ro.DataToSend[6] = 16;
    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);

}


void MainWindow::on_reculerButton_pressed()
{
    //qDebug() << "recule____";
    // read the data from the socket
    ro.DataToSend[0] = 0xFF;
    ro.DataToSend[1] = 0x07;
    ro.DataToSend[2] = 150;    //Vitesse roue gauche
    ro.DataToSend[3] = 0;    //Vitesse roue gauche
    ro.DataToSend[4] = 150;    //Vitesse roue droite
    ro.DataToSend[5] = 0;    //Vitesse roue droite
    ro.DataToSend[6] = 0;    //Direction 80 droit,  64 droite, 16 gauche, 0 reculer
    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);
}

void MainWindow::on_droiteButton_pressed()
{
    //qDebug() << "droite____";
    // read the data from the socket
    ro.DataToSend[0] = 0xFF;
    ro.DataToSend[1] = 0x07;
    ro.DataToSend[2] = 150;    //Vitesse roue gauche
    ro.DataToSend[3] = 0;    //Vitesse roue gauche
    ro.DataToSend[4] = 150;    //Vitesse roue droite
    ro.DataToSend[5] = 0;    //Vitesse roue droite
    ro.DataToSend[6] = 64;    //Direction 80 droit,  64 droite, 16 gauche, 0 reculer
    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);
}



void MainWindow::stop() {
    ro.DataToSend[2] = 0;    //Vitesse roue gauche
    ro.DataToSend[3] = 0;    //Vitesse roue gauche
    ro.DataToSend[4] = 0;    //Vitesse roue droite
    ro.DataToSend[5] = 0;    //Vitesse roue droite
    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);
}

void MainWindow::on_avancerButton_released()
{
    stop();
}


void MainWindow::on_droiteButton_released()
{
    stop();
}


void MainWindow::on_gaucheButton_released()
{
    stop();
}


void MainWindow::on_reculerButton_released()
{
    stop();
}





void MainWindow::keyPressEvent( QKeyEvent * event )
{
    if( event->key() == Qt::Key_A )
    {
        ro.DataToSend[0] = 0xFF;
        ro.DataToSend[1] = 0x07;
        ro.DataToSend[2] = 150;    //Vitesse roue gauche
        ro.DataToSend[3] = 0;    //Vitesse roue gauche
        ro.DataToSend[4] = 150;    //Vitesse roue droite
        ro.DataToSend[5] = 0;    //Vitesse roue droite
        ro.DataToSend[6] = 16;
        unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
        ro.DataToSend[7] = (unsigned char)crc;
        ro.DataToSend[8] = (unsigned char)(crc >> 8);
    }
}



void MainWindow::on_cameraGauche_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}


void MainWindow::on_cameraHaut_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
}


void MainWindow::on_cameraDroite_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}


void MainWindow::on_cameraBas_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
}

