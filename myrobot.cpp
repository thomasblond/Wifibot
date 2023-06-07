// myrobot.cpp

#include "myrobot.h"


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

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

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

    qDebug() << "forward end";
}

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
}

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
}

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
}

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


void MyRobot::Stop(){
    DataToSend[2] = 0;
    DataToSend[3] = 0;
    DataToSend[4] = 0;
    DataToSend[5] = 0;
    DataToSend[6] = 0;
    DataToSend[7] = 0;
    DataToSend[8] = 0;
}


void MyRobot::changeSpeed(int value)
{
    this->speed = value;
    if(state == FORWARD){
        qDebug() << "forward4";
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
