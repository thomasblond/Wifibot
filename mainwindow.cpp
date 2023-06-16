#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"

const int maxBatValue = 131;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->r.doConnect();
    ui->setupUi(this);
    connect(&r, SIGNAL(updateUI()), this, SLOT(updateUi()) );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    if(ui->radioButton->isChecked())
    {
        ui->lcd->display(ui->lcd->value()+1);
    }
    else ui->lcd->display(ui->lcd->value()-1);
}

void MainWindow::updateUi()
{
    qDebug() << (unsigned char)r.DataReceived[2] << "test";
    setBat((unsigned char)r.DataReceived[2]);
    setIr((unsigned short)r.DataReceived[3], (unsigned short)r.DataReceived[11], (unsigned short)r.DataReceived[12], (unsigned short)r.DataReceived[4]);
}

void MainWindow::setBat(float value)
{
    if(value >= maxBatValue)
        value = maxBatValue;
    ui->bat->setValue((value/maxBatValue) * 100);
}

void MainWindow::setIr(unsigned short avGauche, unsigned short avDroite, unsigned short arGauche, unsigned short arDroite)
{
    ui->avantGauche->display(avGauche);
    ui->avantDroite->display(avDroite);
    ui->arriereGauche->display(arGauche);
    ui->arriereDroite->display(arDroite);
}
