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
#include <QWebEngineHttpRequest>
#include <QtWebEngine>
#include <QtWebEngine/QtWebEngine>
#include <QWebEngineView>
#include <qwebengineview.h>


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

private:
    Ui::MainWindow *ui;
    QWebEngineView webEngine{};
    QWidget *cadre{};
};
#endif // MAINWINDOW_H
