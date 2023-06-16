#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QLineEdit>

/**
 * @brief Classe représentant le robot.
 *
 * La classe MyRobot est responsable de la communication avec le robot et de la gestion de ses actions.
 */
class MyRobot : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructeur de la classe MyRobot.
     * @param parent Le QObject parent (par défaut 0).
     */
    explicit MyRobot(QObject *parent = 0);
    /**
     * @brief Établit la connexion avec le robot.
     */
    void doConnect();
    /**
     * @brief Ferme la connexion avec le robot.
     */
    void disConnect();
    QByteArray DataToSend; /**< Données à envoyer au robot. */
    QByteArray DataReceived; /**< Données reçues du robot. */
    QMutex Mutex; /**< Mutex pour la synchronisation. */

    int speed; /**< Vitesse du robot. */

signals:
    void updateUI();
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    

    //Directions pour le robot
    void Forward();
    void Backward();
    void Left();
    void Right();
    void ForwardLeft();
    void ForwardRight();
    void BackwardLeft();
    void BackwardRight();
    void Stop();

    /**
     * @brief Modifie la vitesse du robot.
     * @param value La nouvelle valeur de vitesse.
     */
    void changeSpeed(int value);
    /**
     * @brief Calcule le CRC16 d'un tableau d'octets.
     * @param Adresse_tab Le tableau d'octets.
     * @param Taille_max La taille maximale du tableau.
     * @return La valeur du CRC16.
     */
    short Crc16(unsigned char *Adresse_tab , unsigned char Taille_max);


private:
    QTcpSocket *socket; /**< Socket pour la communication avec le robot. */
    QTimer *TimerEnvoi; /**< Timer pour l'envoi périodique des commandes. */
    /**
     * @brief Énumération représentant les différentes directions du robot.
     */
    typedef enum
    {
        FORWARD,
        BACKWARD,
        RIGHT,
        LEFT,
        FORWARDRIGHT,
        FORWARDLEFT,
        BACKWARDRIGHT,
        BACKWARDLEFT
    }direction;
    direction state;
};

#endif // MYROBOT_H
