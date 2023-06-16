// myrobot.cpp

#include "myrobot.h"
#include "mainwindow.h"


MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}

/**
 * @brief Fonction pour établir une connexion avec le robot via TCP/IP.
 *
 * Cette fonction crée un socket TCP/IP et établit une connexion avec le robot en utilisant l'adresse IP et le port spécifiés.
 * Elle configure également les connexions de signaux et slots pour gérer les événements liés à la connexion.
 * Si la connexion n'est pas établie avec succès dans les 5 secondes, une erreur est affichée.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);
}

/**
 * @brief Fonction pour se déconnecter du robot.
 *
 * Cette fonction arrête le timer d'envoi et ferme la connexion avec le robot en fermant le socket.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

/**
 * @brief Fonction pour gérer l'événement d'écriture de données.
 *
 * Cette fonction est appelée lorsque des données sont écrites avec succès sur la connexion du socket.
 * Elle affiche le nombre de bytes écrits dans la console de débogage.
 *
 * @param bytes Le nombre de bytes écrits.
 * @return Aucune valeur de retour.
 */
void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

/**
 * @brief Fonction pour gérer l'événement de lecture de données.
 *
 * Cette fonction est appelée lorsque des données sont prêtes à être lues à partir de la connexion du socket.
 * Elle lit les données à partir du socket dans la variable `DataReceived`.
 * Ensuite, elle émet un signal `updateUI()` pour informer d'autres parties du code qu'il y a de nouvelles données disponibles.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI();
}

/**
 * @brief Fonction pour gérer l'événement du temporisateur.
 *
 * Cette fonction est appelée à chaque déclenchement du temporisateur.
 * Elle envoie les données contenues dans `DataToSend` sur la connexion du socket.
 * Un mutex est utilisé pour éviter les accès simultanés aux données.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

/**
 * @brief Fonction pour faire avancer le robot.
 *
 * Cette fonction prépare les données à envoyer au robot pour le faire avancer.
 * Elle définit les valeurs appropriées dans le tableau de données `DataToSend`.
 * La vitesse de déplacement est spécifiée par la variable `speed`.
 * La fonction calcule également le CRC des données pour l'intégrité du message.
 * Enfin, elle met à jour l'état du robot à FORWARD.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::Forward() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = (short)speed;
    DataToSend[3] = 0;
    DataToSend[4] = (short)speed;
    DataToSend[5] = 0;
    DataToSend[6] = 0b01010000;
    short mycrcsend = Crc16((unsigned char *)(DataToSend.data()),7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
    state = FORWARD;
    qDebug() << "Avancer";
}

/**
 * @brief Fonction pour faire reculer le robot.
 *
 * Cette fonction prépare les données à envoyer au robot pour le faire reculer.
 * Elle définit les valeurs appropriées dans le tableau de données `DataToSend`.
 * La vitesse de déplacement est spécifiée par la variable `speed`.
 * La fonction calcule également le CRC des données pour l'intégrité du message.
 * Enfin, elle met à jour l'état du robot à BACKWARD.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::Backward() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed;
    DataToSend[3] = 0;
    DataToSend[4] = speed;
    DataToSend[5] = 0;
    DataToSend[6] = 0b00000000;
    short mycrcsend = Crc16((unsigned char *)DataToSend.data(),7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
    state = BACKWARD;
    qDebug() << "Arriere";
}

/**
 * @brief Fonction pour faire tourner le robot vers la gauche.
 *
 * Cette fonction prépare les données à envoyer au robot pour le faire tourner vers la gauche.
 * Elle définit les valeurs appropriées dans le tableau de données `DataToSend`.
 * La vitesse de déplacement est spécifiée par la variable `speed`.
 * La fonction calcule également le CRC des données pour l'intégrité du message.
 * Enfin, elle met à jour l'état du robot à LEFT.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::Left() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed;
    DataToSend[3] = 0;
    DataToSend[4] = speed;
    DataToSend[5] = 0;
    DataToSend[6] = 0b00010000;
    short mycrcsend = Crc16((unsigned char *)DataToSend.data(),7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
    state = LEFT;
    qDebug() << "gauche";
}

/**
 * @brief Fonction pour faire tourner le robot vers la droite.
 *
 * Cette fonction prépare les données à envoyer au robot pour le faire tourner vers la droite.
 * Elle définit les valeurs appropriées dans le tableau de données `DataToSend`.
 * La vitesse de déplacement est spécifiée par la variable `speed`.
 * La fonction calcule également le CRC des données pour l'intégrité du message.
 * Enfin, elle met à jour l'état du robot à RIGHT.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::Right() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed;
    DataToSend[3] = 0;
    DataToSend[4] = speed;
    DataToSend[5] = 0;
    DataToSend[6] = 0b01000000;
    short mycrcsend = Crc16((unsigned char *)DataToSend.data(),7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
    state = RIGHT;
    qDebug() << "droite";
}

/**
 * @brief Fonction pour faire avancer le robot en tournant légèrement vers la gauche en avant.
 *
 * Cette fonction prépare les données à envoyer au robot pour le faire avancer en tournant légèrement vers la gauche.
 * Elle définit les valeurs appropriées dans le tableau de données `DataToSend`.
 * La vitesse de déplacement est spécifiée par la variable `speed`, et la vitesse du moteur gauche est ajustée en fonction de la variable `this->speed`.
 * La fonction calcule également le CRC des données pour l'intégrité du message.
 * Enfin, elle met à jour l'état du robot à FORWARDLEFT.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::ForwardLeft() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = speed*this->speed/100;
    DataToSend[5] = 0;
    DataToSend[6] = 0b01010000;
    short mycrcsend = Crc16((unsigned char *)DataToSend.data(),7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
    state = FORWARDLEFT;
}

/**
 * @brief Fonction pour faire avancer le robot en tournant légèrement vers la droite en avant.
 *
 * Cette fonction prépare les données à envoyer au robot pour le faire avancer en tournant légèrement vers la droite.
 * Elle définit les valeurs appropriées dans le tableau de données `DataToSend`.
 * La vitesse de déplacement est spécifiée par la variable `speed`, et la vitesse du moteur droit est ajustée en fonction de la variable `this->speed`.
 * La fonction calcule également le CRC des données pour l'intégrité du message.
 * Enfin, elle met à jour l'état du robot à FORWARDRIGHT.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::ForwardRight() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed*this->speed/100;
    DataToSend[3] = 0;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 0b01010000;
    short mycrcsend = Crc16((unsigned char *)DataToSend.data(),7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
    state = FORWARDRIGHT;
}

/**
 * @brief Fonction pour faire reculer le robot en tournant légèrement vers la gauche en arrière.
 *
 * Cette fonction prépare les données à envoyer au robot pour le faire reculer en tournant légèrement vers la gauche.
 * Elle définit les valeurs appropriées dans le tableau de données `DataToSend`.
 * La vitesse de déplacement est spécifiée par la variable `speed`, et la vitesse du moteur gauche est ajustée en fonction de la variable `this->speed`.
 * La fonction calcule également le CRC des données pour l'intégrité du message.
 * Enfin, elle met à jour l'état du robot à BACKWARDLEFT.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::BackwardLeft() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = speed*this->speed/100;
    DataToSend[5] = 0;
    DataToSend[6] = 0b00000000;
    short mycrcsend = Crc16((unsigned char *)DataToSend.data(),7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
    state = BACKWARDLEFT;
}

/**
 * @brief Fonction pour faire reculer le robot en tournant légèrement vers la droite en arrière.
 *
 * Cette fonction prépare les données à envoyer au robot pour le faire reculer en tournant légèrement vers la droite.
 * Elle définit les valeurs appropriées dans le tableau de données `DataToSend`.
 * La vitesse de déplacement est spécifiée par la variable `speed`.
 * La fonction calcule également le CRC des données pour l'intégrité du message.
 * Enfin, elle met à jour l'état du robot à BACKWARDRIGHT.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::BackwardRight() {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = speed;
    DataToSend[3] = 0;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 0b00000000;
    short mycrcsend = Crc16((unsigned char *)DataToSend.data(),7);
    DataToSend[7] = mycrcsend;
    DataToSend[8] = mycrcsend >> 8;
    state = BACKWARDRIGHT;
}

/**
 * @brief Fonction pour arrêter le robot.
 *
 * Cette fonction met à zéro les valeurs dans le tableau de données `DataToSend` pour arrêter le robot.
 * Les variables correspondantes à la vitesse et aux commandes de mouvement sont mises à zéro.
 * Enfin, un message de débogage est affiché pour indiquer que le robot est arrêté.
 *
 * @param Aucun.
 * @return Aucune valeur de retour.
 */
void MyRobot::Stop(){
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 0;
    DataToSend[7] = 0;
    DataToSend[8] = 0;
    qDebug() << "Stop";
}

/**
 * @brief Fonction pour changer la vitesse de déplacement du robot.
 *
 * Cette fonction permet de modifier la vitesse de déplacement du robot en fonction de la valeur spécifiée.
 * La nouvelle vitesse est affectée à la variable `speed`.
 * Ensuite, en fonction de l'état actuel du robot, la fonction appelle la fonction correspondante pour mettre à jour les données de déplacement avec la nouvelle vitesse.
 *
 * @param value La nouvelle valeur de vitesse.
 * @return Aucune valeur de retour.
 */
void MyRobot::changeSpeed(int value)
{
    this->speed = value;
    if(state == FORWARD){
        this->Forward();
    } else if(state == BACKWARD){
        this->Backward();
    } else if(state == RIGHT){
        this->Right();
    } else if(state == LEFT){
        this->Left();
    } else if(state == FORWARDRIGHT){
        this->ForwardRight();
    } else if(state == FORWARDLEFT){
        this->ForwardLeft();
    } else if(state == BACKWARDRIGHT){
        this->BackwardRight();
    } else if(state == BACKWARDLEFT){
        this->BackwardLeft();
    }
}

/**
 * @brief Fonction de calcul du CRC16.
 *
 * Cette fonction calcule le CRC16 pour les données spécifiées.
 *
 * @param _Adresse_tab Un pointeur vers le tableau de données.
 * @param Taille_Max La taille maximale du tableau de données.
 * @return La valeur CRC16 calculée.
 */
short MyRobot::Crc16(unsigned char *_Adresse_tab, unsigned char Taille_Max){
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;

    Crc = 0xFFFF;
    Polynome = 0xA001;
    for (CptOctet=1; CptOctet<Taille_Max;CptOctet++){
        Crc ^= *(_Adresse_tab + CptOctet);

        for(CptBit=0;CptBit<=7;CptBit++){
            Parity = Crc;
            Crc >>=1;
            if(Parity%2 == true) Crc ^= Polynome;
        }
    }
    return (Crc);
}

