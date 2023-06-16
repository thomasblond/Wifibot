#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include <iostream>
#include <QUrl>

const int maxBatValue = 129;

/**
 * @brief Constructeur de la fenêtre principale de l'application.
 *
 * Ce constructeur crée une instance de la classe MyRobot et configure l'interface utilisateur de la fenêtre.
 * Il établit également une connexion entre le signal "updateUI" émis par l'objet robot et le slot "updateUi" de la classe MainWindow.
 * Ensuite, il crée une instance de QWebEngineView pour afficher un flux vidéo provenant d'une URL spécifique.
 *
 * @param parent Le widget parent de la fenêtre (par défaut nullptr).
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    robot = new MyRobot();
    ui->setupUi(this);

    connect(robot, SIGNAL(updateUI()), this, SLOT(updateUi()) );

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

/**
 * @brief Slot appelé lorsque la valeur du curseur vertical est modifiée.
 *
 * Cette fonction est appelée lorsque la valeur du curseur vertical (verticalSlider) est modifiée dans l'interface graphique de la fenêtre principale.
 * Elle affiche la nouvelle valeur dans la console en utilisant la sortie standard (std::cout).
 * Ensuite, elle appelle la fonction `changeSpeed` de l'objet `robot` pour mettre à jour la vitesse du robot en fonction de la nouvelle valeur du curseur.
 *
 * @param value La nouvelle valeur du curseur vertical.
 * @return Aucune valeur de retour.
 */
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

/**
 * @brief Gestionnaire d'événements pour les pressions de touches du clavier.
 *
 * Cette fonction est appelée lorsque l'utilisateur appuie sur une touche du clavier dans la fenêtre principale.
 * Elle détecte la touche pressée et effectue l'action correspondante en fonction de la touche.
 * Les touches Z, S, D et Q sont associées aux mouvements du robot.
 * Pour chaque touche, un message de débogage est affiché pour indiquer la demande de mouvement du robot.
 * La fonction appelle ensuite la fonction appropriée de l'objet `robot` pour exécuter le mouvement demandé.
 *
 * @param event L'événement clavier contenant les informations sur la touche pressée.
 * @return Aucune valeur de retour.
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyPressed = event->key();
    switch(keyPressed){

        case Qt::Key_Z:
            qDebug() << "Demande avancer";
            robot->Forward();

            break;

        case Qt::Key_S:
            qDebug() << "Demande arriere";
            robot->Backward();

            break;

        case Qt::Key_D:
            qDebug() << "Demande droite";
            robot->Right();

            break;

        case Qt::Key_Q:
            qDebug() << "Demande gauche";
            robot->Left();

            break;
    }

}

/**
 * @brief Gestionnaire d'événements pour les relâchements de touches du clavier.
 *
 * Cette fonction est appelée lorsque l'utilisateur relâche une touche du clavier dans la fenêtre principale.
 * Elle vérifie si la touche relâchée correspond à l'une des touches associées aux mouvements du robot (Z, S, D, Q).
 * Si c'est le cas, un message de débogage est affiché pour indiquer la demande d'arrêt du robot.
 * La fonction appelle ensuite la fonction `Stop` de l'objet `robot` pour arrêter le mouvement du robot.
 *
 * @param event L'événement clavier contenant les informations sur la touche relâchée.
 * @return Aucune valeur de retour.
 */
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Z || event->key() == Qt::Key_S ||
        event->key() == Qt::Key_D || event->key() == Qt::Key_Q)
    {
        qDebug() << "Demande stop";
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

/**
 * Met à jour l'interface utilisateur en fonction des données reçues du robot.
 * Cette fonction est appelée lorsqu'il y a des mises à jour des données du robot.
 */
void MainWindow::updateUi()
{
    qDebug() << (unsigned char)robot->DataReceived[2] << "test";
    // Met à jour l'affichage de la batterie
    setBat((unsigned char)robot->DataReceived[2]);
    // Met à jour l'affichage des capteurs infrarouges
    setIr((unsigned short)robot->DataReceived[3], (unsigned short)robot->DataReceived[11], (unsigned short)robot->DataReceived[12], (unsigned short)robot->DataReceived[4]);
    // Met à jour l'affichage de l'odométrie
    setOdometry(((((long)robot->DataReceived[8] << 24))+(((long)robot->DataReceived[7] <<16))+(((long)robot->DataReceived[6] << 8))+((long)robot->DataReceived[5])), ((((long)robot->DataReceived[16] << 24))+(((long)robot->DataReceived[15] <<16))+(((long)robot->DataReceived[14] << 8))+((long)robot->DataReceived[13])));
    // Met à jour l'affichage de la vitesse
    setVitesse();

}

/**
 * Met à jour l'affichage de la batterie dans l'interface utilisateur.
 * @param value La valeur de la batterie à afficher.
 */
void MainWindow::setBat(float value)
{
    qDebug() << value;
    // Vérifie si la valeur de la batterie dépasse la valeur maximale
    if(value >= maxBatValue)
        value = maxBatValue;
    // Met à jour la valeur de la barre de progression de la batterie
    ui->bat->setValue((value/maxBatValue) * 100);
}

/**
 * Met à jour l'affichage des valeurs des capteurs infrarouges dans l'interface utilisateur.
 * @param avGauche La valeur du capteur infrarouge avant gauche.
 * @param avDroite La valeur du capteur infrarouge avant droite.
 * @param arGauche La valeur du capteur infrarouge arrière gauche.
 * @param arDroite La valeur du capteur infrarouge arrière droite.
 */
void MainWindow::setIr(unsigned short avGauche, unsigned short avDroite, unsigned short arGauche, unsigned short arDroite)
{
    // Met à jour l'affichage des valeurs des capteurs infrarouges dans les affichages numériques correspondants

    //Conversion en voltage
    float vAvDroite = (((float)avDroite)*1.3)/99.0;
    float vArDroite = (((float)arDroite)*1.3)/99.0;
    float vAvGauche = (((float)avGauche)*1.3)/99.0;
    float vArGauche = (((float)arGauche)*1.3)/99.0;
    //Conversion en cm
    float dAvGauche = 16.2537 * pow(vAvGauche, 4) - 129.893 * pow(vAvGauche, 3) + 382.268 * pow(vAvGauche, 2) - 512.611 * vAvGauche + 301.439;
    float dAvDroite = 16.2537 * pow(vAvDroite, 4) - 129.893 * pow(vAvDroite, 3) + 382.268 * pow(vAvDroite, 2) - 512.611 * vAvDroite + 301.439;
    float dArGauche = 16.2537 * pow(vArGauche, 4) - 129.893 * pow(vArGauche, 3) + 382.268 * pow(vArGauche, 2) - 512.611 * vArGauche + 301.439;
    float dArDroite = 16.2537 * pow(vArDroite, 4) - 129.893 * pow(vArDroite, 3) + 382.268 * pow(vArGauche, 2) - 512.611 * vArGauche + 301.439;

    ui->avantGauche->display(dAvGauche);
    ui->avantDroite->display(dAvDroite);
    ui->arriereGauche->display(dArGauche);
    ui->arriereDroite->display(dArDroite);
}

/**
 * Met à jour l'affichage des valeurs d'odométrie dans l'interface utilisateur.
 * @param left La valeur d'odométrie du côté gauche.
 * @param right La valeur d'odométrie du côté droit.
 */
void MainWindow::setOdometry(long left, long right)
{
    ui->odometryG->display(left/2448);
    ui->odometryD->display(right/2448);
}

/**
 * Met à jour l'affichage des valeurs de vitesse dans l'interface utilisateur.
 */
void MainWindow::setVitesse()
{
    // Récupère les valeurs de vitesse du robot depuis les données reçues
    int left = int((robot->DataReceived[1] << 8) + robot->DataReceived[0]);
    if(left < 0){
        left += 256;
    }
    int right = int((robot->DataReceived[10] << 8) + robot->DataReceived[9]);
    if(right < 0){
        right += 256;
    }
    qDebug() << "vtesse";
    qDebug() << left;
    qDebug() << right;

    // Calcule les vitesses à partir des valeurs récupérées
    float vLeft = float(left)*3.142*(20.0*0.14/2448)*3.6;
    float vRight = float(right)*3.142*(20.0*0.14/2448)*3.6;

    // Met à jour l'affichage des valeurs de vitesse dans les affichages numériques correspondants
    ui->vitesseG->display(vLeft);
    ui->vitesseD->display(vRight);

}


