#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include <iostream>
#include <QUrl>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    robot = new MyRobot();
    robot->doConnect();
    ui->setupUi(this);

    QWebEngineView *view = this->ui->frame;
    view->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    view->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_6_clicked()
{
    robot->Stop();
}


void MainWindow::on_pushButton_3_clicked()
{
    robot->Left();
}


void MainWindow::on_pushButton_2_clicked()
{
    robot->Right();
}


void MainWindow::on_pushButton_clicked()
{
    robot->Forward();
    qDebug() << "forward";
}


void MainWindow::on_pushButton_4_clicked()
{
    robot->ForwardLeft();
}


void MainWindow::on_pushButton_5_clicked()
{
    robot->ForwardRight();
}


void MainWindow::on_pushButton_8_clicked()
{
    robot->Backward();
}

void MainWindow::on_pushButton_10_clicked()
{
    robot->BackwardLeft();
}


void MainWindow::on_pushButton_7_clicked()
{
    robot->BackwardRight();
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    std::cout << value << std::endl;
    qDebug() << "forward2";
    robot->changeSpeed(value);
    qDebug() << "forward3";
}


void MainWindow::on_verticalSlider_actionTriggered(int value)
{
}


void MainWindow::on_pushButton_9_clicked()
{
    camera->moveUp();
}


void MainWindow::on_pushButton_11_clicked()
{
    camera->moveDown();
}


void MainWindow::on_pushButton_12_clicked()
{
    camera->moveLeft();
}



void MainWindow::on_pushButton_13_clicked()
{
    camera->moveRight();
}

