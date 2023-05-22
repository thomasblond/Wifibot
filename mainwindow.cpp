#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    MyRobot r;
    r.doConnect();
    ui->setupUi(this);
    webEngine.load(QUrl("http://192.168.1.106:8080/?action=stream"));
    webEngine.setGeometry(100, 100, 200, 200);

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
