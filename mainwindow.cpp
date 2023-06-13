#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"

// Construction de la fenêtre parent
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Création de la fenêtre pour afficher la caméra
    QWebEngineView *webEngineV = new QWebEngineView();
    webEngineV->resize(300, 300);
    //Récupération de l'URL de la caméra pour le stream
    QUrl url = QUrl("http://192.168.1.106:8080/?action=stream");
    //Chargement de l'URL
    webEngineV->load(url);
    // Ajout de la caméra dans la fenêtre
    webEngineV->setParent(this);

    CaptorTimer = new QTimer();
    connect(CaptorTimer, SIGNAL(timeout()), this, SLOT(captor_recup()));
    CaptorTimer->start(1000);

}

// Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

// Bouton Connect
void MainWindow::on_connectButton_clicked()
{
    // Appel de la méthode doConnect() de la classe myrobot
    ro.doConnect();
}

// Bouton Disconnect
void MainWindow::on_disconnect_button_clicked()
{
    // Appel de la méthode disConnect() de la classe myrobot
    ro.disConnect();
}


//Fonction calculant le CRC
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


unsigned  short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);

void MainWindow::avancer()
{
    // Fonction faisant avancer le robot en envoyant des valeurs spécifiques sous forme d'un tableau
    ro.DataToSend[0] = 0xFF;
    ro.DataToSend[1] = 0x07;
    ro.DataToSend[2] = 150;  // Vitesse roue gauche
    ro.DataToSend[3] = 0;    // Vitesse roue gauche
    ro.DataToSend[4] = 150;  // Vitesse roue droite
    ro.DataToSend[5] = 0;    // Vitesse roue droite
    ro.DataToSend[6] = 80;   // Direction 8 : 0 -> droit

    // Calcul du CRC pour retourner la valeur dans le tableau
    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);
}

void MainWindow::on_avancerButton_pressed()
{
    // Appel de la fonction avancer() lors de l'appui sur un bouton
    avancer();
}


void MainWindow::gauche()
{
    // Fonction faisant tourner le robot à gauche en envoyant des valeurs spécifiques sous forme d'un tableau
    ro.DataToSend[0] = 0xFF;
    ro.DataToSend[1] = 0x07;
    ro.DataToSend[2] = 150;  // Vitesse roue gauche
    ro.DataToSend[3] = 0;    // Vitesse roue gauche
    ro.DataToSend[4] = 150;  // Vitesse roue droite
    ro.DataToSend[5] = 0;    // Vitesse roue droite
    ro.DataToSend[6] = 16;   // Direction : 16 -> gauche
    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);
}

void MainWindow::on_gaucheButton_pressed()
{
    // Appel de la fonction gauche() lors de l'appui sur un bouton
    gauche();
}

void MainWindow::reculer()
{
    // Fonction faisant reculer le robot en envoyant des valeurs spécifiques sous forme d'un tableau
    ro.DataToSend[0] = 0xFF;
    ro.DataToSend[1] = 0x07;
    ro.DataToSend[2] = 150;  // Vitesse roue gauche
    ro.DataToSend[3] = 0;    // Vitesse roue gauche
    ro.DataToSend[4] = 150;  // Vitesse roue droite
    ro.DataToSend[5] = 0;    // Vitesse roue droite
    ro.DataToSend[6] = 0;    // Direction : 0 -> reculer
    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);
}

void MainWindow::on_reculerButton_pressed()
{
    // Appel de la fonction reculer() lors de l'appui sur un bouton
    reculer();
}

void MainWindow::droite()
{
    // Fonction faisant tourner le robot à droite en envoyant des valeurs spécifiques sous forme d'un tableau
    ro.DataToSend[0] = 0xFF;
    ro.DataToSend[1] = 0x07;
    ro.DataToSend[2] = 150;  // Vitesse roue gauche
    ro.DataToSend[3] = 0;    // Vitesse roue gauche
    ro.DataToSend[4] = 150;  // Vitesse roue droite
    ro.DataToSend[5] = 0;    // Vitesse roue droite
    ro.DataToSend[6] = 64;   // Direction : 64 -> droite
    unsigned short crc = Crc16((unsigned char*)(ro.DataToSend.constData()), 7);
    ro.DataToSend[7] = (unsigned char)crc;
    ro.DataToSend[8] = (unsigned char)(crc >> 8);
}
void MainWindow::on_droiteButton_pressed()
{
    // Appel de la fonction droite() lors de l'appui sur un bouton
    droite();
}

void MainWindow::stop()
{
    // Fonction arrêtant le robot en envoyant des valeurs spécifiques (0) sous forme d'un tableau
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
    // Appel de la fonction stop() lors du relâchement du bouton
    stop();
}

void MainWindow::on_droiteButton_released()
{
    // Application de la fonction stop() lors du relâchement du bouton
    stop();
}

void MainWindow::on_gaucheButton_released()
{
    // Application de la fonction stop() lors du relâchement du bouton
    stop();
}

void MainWindow::on_reculerButton_released()
{
    // Application de la fonction stop() lors du relâchement du bouton
    stop();
}

// Déplacement de la caméra vers la gauche
void MainWindow::on_cameraGauche_clicked()
{
    //
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // Récupération de l'URL permettant à la caméra de se déplacer
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}

// Déplacement de la caméra vers le haut
void MainWindow::on_cameraHaut_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
}

// Déplacement de la caméra vers la droite
void MainWindow::on_cameraDroite_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}

// Déplacement de la caméra vers le bas
void MainWindow::on_cameraBas_clicked()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
}




void MainWindow::keyPressEvent( QKeyEvent * event )
{
    if (event->key() == Qt::Key_Q )
    {
        // Appel de la fonction gauche() lors de l'appui sur la key Q
        gauche();
    }
    else if (event->key() == Qt::Key_D )
    {
        // Appel de la fonction droite() lors de l'appui sur la key D
        droite();
    }
    else if (event->key() == Qt::Key_Z )
    {
        // Appel de la fonction avancer() lors de l'appui sur la key Z
        avancer();
    }
    else if (event->key() == Qt::Key_S)
    {
        // Appel de la fonction reculer() lors de l'appui sur la key S
        reculer();
    }

}
void MainWindow::keyReleaseEvent( QKeyEvent * event )
{
    if (event->key() == Qt::Key_Q )
    {
        // Application de la fonction stop() lors du relâchement de la key Q
        stop();
    }
    else if (event->key() == Qt::Key_D )
    {
        // Application de la fonction stop() lors du relâchement de la key D
        stop();
    }
    else if (event->key() == Qt::Key_Z )
    {
        // Application de la fonction stop() lors du relâchement de la key Z
        stop();
    }
    else if (event->key() == Qt::Key_S)
    {
        // Application de la fonction stop() lors du relâchement de la key S
        stop();
    }
}

// Récupération des infos des capteurs auprès du tableau DataReceived[] du robot
void MainWindow::captor_recup() {

    int roueDroite = (int)ro.DataReceived[0]; // Vitesse roue droite
    int roueGauche = (int)ro.DataReceived[9]; // Vitesse roue gauche
    unsigned char batterie_level = (unsigned char)ro.DataReceived[2]; // Niveau de batterie
    unsigned char IR1 = (unsigned char)ro.DataReceived[3]; // Infrarouge droit
    unsigned char IR2 = (unsigned char)ro.DataReceived[4]; // Infrarouge gauche
    float odometrie = (float)ro.DataReceived[5]; // Odométrie

    // Affichage des infos dans la fenêtre en les convertissant dans le bon type
    ui->roue_droite->setText(QString::number(roueDroite)); // Vitesse roue droite
    ui->roue_gauche->setText(QString::number(roueGauche)); // Vitesse roue gauche
    ui->batterie_level_text->setText(QVariant(batterie_level).toString()); // Niveau de batterie
    ui->IR_droit->setText(QVariant(IR1).toString()); // Infrarouge avant droit
    ui->IR_gauche->setText(QVariant(IR2).toString());// Infrarouge avant gauche
    ui->odometrie->setText(QVariant(odometrie).toString());

    //11 12 pour les IR arrières
}

/*void MainWindow::update_captors_data()
{

}*/

void MainWindow::on_capteur_clicked()
{
    captor_recup();
}



