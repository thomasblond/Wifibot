#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;

    int speed;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();
    
    void Forward(short speed1, short speed2);
    void Backward(short speed1, short speed2);
    void Left(short speed1, short speed2);
    void Right(short speed1, short speed2);
    void ForwardLeft(short speed1);
    void ForwardRight(short speed1);
    void BackwardLeft(short speed1);
    void BackwardRight(short speed1);
    void Stop();

    short Crc16(unsigned char *Adresse_tab , unsigned char Taille_max);

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;

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
