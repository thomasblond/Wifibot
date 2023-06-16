#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myrobot.h"
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaContent>
#include <qpushbutton.h>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();
    void updateUi();

private:
    Ui::MainWindow *ui;
    QWidget *cadre{};
    MyRobot r;

    void setBat(float value);
    void setIr(unsigned short avGauche, unsigned short avDroite, unsigned short arGauche, unsigned short arDroite);

};
#endif // MAINWINDOW_H
