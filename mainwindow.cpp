#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include "Qwebengineview"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
       qDebug() << "g..."; // read the data from the socket
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
    ro.DataToSend[6] = 16;    //Direction 80 droit,  64 droite, 16 gauche, 0 reculer

    short crc = Crc16((unsigned char*)(ro.DataToSend.data())+1, 6);
    char crc1 = crc;
    char crc2 = crc >> 8;

    ro.DataToSend[7] = crc1;
    ro.DataToSend[8] = crc2;

}


void MainWindow::on_reculerButton_pressed()
{
    ro.DataToSend[6] = 0;    //Direction 80 droit,  64 droite, 16 gauche, 0 reculer

    short crc = Crc16((unsigned char*)(ro.DataToSend.data())+1, 6);
    char crc1 = crc;
    char crc2 = crc >> 8;

    ro.DataToSend[7] = crc1;
    ro.DataToSend[8] = crc2;
}


void MainWindow::on_droiteButton_pressed()
{
    ro.DataToSend[6] = 64;    //Direction 80 droit,  64 droite, 16 gauche, 0 reculer

    short crc = Crc16((unsigned char*)(ro.DataToSend.data())+1, 6);
    char crc1 = crc;
    char crc2 = crc >> 8;

    ro.DataToSend[7] = crc1;
    ro.DataToSend[8] = crc2;

}








/*void MainWindow::Camera(){
    this->webEngine->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    this->ui->horizontalLayout->insertWidget(0, this->webEngine);
}*/