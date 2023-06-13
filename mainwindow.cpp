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
    robot->changeSpeed(value);
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyPressed = event->key();
    switch(keyPressed){

        case Qt::Key_Z:

            robot->Forward();
            break;

        case Qt::Key_S:

            robot->Backward();
            break;

        case Qt::Key_D:

            robot->Right();
            break;

        case Qt::Key_Q:

            robot->Left();
            break;
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z || event->key() == Qt::Key_S ||
        event->key() == Qt::Key_D || event->key() == Qt::Key_Q)
    {
        robot->Stop();
    }
}


void MainWindow::on_pushButton_14_clicked()
{
    robot->doConnect();
    qDebug() << "Connected !";
}


void MainWindow::on_pushButton_15_clicked()
{
    robot->disConnect();
    qDebug() << "Disconnected !";
}

