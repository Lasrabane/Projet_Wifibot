#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"

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


void MainWindow::on_pushButton_pressed()
{
    ro.
}

void MainWindow::on_avancerButton_pressed()
{
    DataToSend[6] = 80;    //Direction 80 droit,  64 droite, 16 gauche, 0 reculer

    short crc = Crc16(*DataToSend+1, 6);
    char crc1 = crc;
    char crc2 = crc >> 8;

    DataToSend[7] = crc1;
    DataToSend[8] = crc2;

    ro.MyTimerSlot();
}

short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;

    Crc = 0xFFFF;
    Polynome = 0xA001;

    for(CptOctet = 0 ; CptOctet < Taille_max ; CptOctet ++)
    {
        Crc ^= *(Adresse_tab + CptOctet);
            for(CptBit = 0 ; CptBit < 7 ; CptBit ++)
        {
            Parity = Crc;
            Crc >>=1;
            if(Parity%2 == true) Crc ^= Polynome;
        }
    }
    return Crc;
}


/*void MainWindow::on_reculerButton_pressed()
{
    DataToSend[6] = 80;    //Direction 80 droit,  64 droite, 16 gauche, 0 reculer

    short crc = Crc16(*DataToSend+1, 6);
    char crc1 = crc;
    char crc2 = crc >> 8;

    DataToSend[7] = crc1;
    DataToSend[8] = crc2;

    ro.MyTimerSlot();
}*/

