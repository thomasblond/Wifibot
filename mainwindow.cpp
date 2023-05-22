#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    robot = new MyRobot();
    robot->doConnect();
    ui->setupUi(this);
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
    robot->Left(200,200);
}


void MainWindow::on_pushButton_2_clicked()
{
    robot->Right(200,200);
}


void MainWindow::on_pushButton_clicked()
{
    robot->Forward(200,200);
}


void MainWindow::on_pushButton_4_clicked()
{
    robot->ForwardLeft(200);
}


void MainWindow::on_pushButton_5_clicked()
{
    robot->ForwardRight(200);
}


void MainWindow::on_pushButton_8_clicked()
{
    robot->Backward(200,200);
}

void MainWindow::on_pushButton_10_clicked()
{
    robot->BackwardLeft(200);
}


void MainWindow::on_pushButton_7_clicked()
{
    robot->BackwardRight(200);
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    std::cout << value << std::endl;
}


void MainWindow::on_verticalSlider_actionTriggered(int action)
{
    robot->speed = value;
}

