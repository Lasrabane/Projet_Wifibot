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

    connect(&ro, SIGNAL(updateUI(QByteArray)), this, SLOT(captors_data(QByteArray)));
}


/****
 * NOTE :
 * ro représente une objet de type robot, créé dans le mainwindow.h
****/

// Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

// Bouton Connect
void MainWindow::on_connectButton_clicked()
{
    // Appel de la méthode doConnect() de la classe myrobot, permettant de connecter le robot
    ro.doConnect();
}

// Bouton Disconnect
void MainWindow::on_disconnect_button_clicked()
{
    // Appel de la méthode disConnect() de la classe myrobot, permettant de déconnecter le robot
    ro.disConnect();
}


// Fonction calculant le CRC
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

// Permet d'éviter un bug lors du passage des valeurs au robot
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
    // Objet permettant de se connecter à la caméra en envoyant et récupérant des données réseau
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
void MainWindow::captors_data(const QByteArray Data) {
    qDebug() << "update ";

    unsigned char batterie_level = (unsigned char)ro.DataReceived[2]; // Niveau de batterie
    QVariant(batterie_level).toFloat();
    batterie_level = batterie_level/10;

    int SpeedRight=(int)(ro.DataReceived[10] << 8) + ro.DataReceived[9]; // Vitesse roue droite
    if(SpeedRight > 32767) SpeedRight = SpeedRight - 65536;
    if(SpeedRight < 0) {
        SpeedRight += 256;
        SpeedRight = - SpeedRight;
    }
    SpeedRight = QVariant(SpeedRight).toFloat();
    SpeedRight= SpeedRight * 1000 / (50);
    SpeedRight = SpeedRight * 0.0196;


    int SpeedLeft=(int)((ro.DataReceived[1] << 8) + ro.DataReceived[0]); // Vitesse roue gauche
    if(SpeedLeft > 32767) SpeedLeft = SpeedLeft - 65536;
    if(SpeedLeft < 0) {
        SpeedLeft += 256;
        SpeedLeft = - SpeedLeft;
    }
    SpeedLeft = QVariant(SpeedLeft).toFloat();
    SpeedLeft= SpeedLeft * 1000 / (50);
    SpeedLeft = SpeedLeft * 0.0196;


    unsigned char IR_droit_avant = (unsigned char)ro.DataReceived[3]; // Infrarouge droit avant
    QVariant(IR_droit_avant).toFloat();
    IR_droit_avant = IR_droit_avant / 10;

    unsigned char IR_gauche_avant = (unsigned char)ro.DataReceived[4]; // Infrarouge gauche avant
    //QVariant(IR_gauche_avant).toFloat();
    //IR_gauche_avant = IR_gauche_avant / 10;


    unsigned char IR_droit_arriere = (unsigned char)ro.DataReceived[11]; // Infrarouge droit arrière
    //QVariant(IR_droit_arriere).toFloat();
    //IR_droit_arriere = IR_droit_arriere / 10;


    unsigned char IR_gauche_arriere = (unsigned char)ro.DataReceived[12]; // Infrarouge gauche arrière
    //QVariant(IR_gauche_arriere).toFloat();
    //IR_gauche_arriere = IR_gauche_arriere / 10;


    float odometrieL = ((long)ro.DataReceived[8] << 24) + ((long)ro.DataReceived[7] << 16) + ((long)ro.DataReceived[6] << 8) + ((long)ro.DataReceived[5]); // Odométrie X
    odometrieL = odometrieL / 2248;
    float odometrieR = ((long)ro.DataReceived[16] << 24) + ((long)ro.DataReceived[15] << 16) + ((long)ro.DataReceived[14] << 8) + ((long)ro.DataReceived[13]); // Odométrie Y
    odometrieR = odometrieR / 2248;

    // Affichage des infos dans la fenêtre en les convertissant dans le bon type

    ui->roue_droite->setText(QString::number(SpeedRight)); // Vitesse roue droite
    ui->roue_gauche->setText(QString::number(SpeedLeft)); // Vitesse roue gauche
    ui->batterie_level_text->setText(QVariant(batterie_level).toString()); // Niveau de batterie
    ui->IR_droit_avant->setText(QVariant(IR_droit_avant).toString()); // Infrarouge avant droit
    ui->IR_gauche_avant->setText(QVariant(IR_gauche_avant).toString()); // Infrarouge avant gauche
    ui->IR_droit_arriere->setText(QVariant(IR_droit_arriere).toString()); // Infrarouge arrière droit
    ui->IR_gauche_arriere->setText(QVariant(IR_gauche_arriere).toString()); // Infrarouge arrière gauche
    ui->odometrieX->setText(QVariant(odometrieL).toString()); // Odométrie en X
    ui->odometrieY->setText(QVariant(odometrieR).toString()); // Odométrie en Y
}

