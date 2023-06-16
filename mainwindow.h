#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "myrobot.h"
#include "camera.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Classe représentant la fenêtre principale de l'application.
 *
 * La classe MainWindow est la fenêtre principale de l'application et gère les interactions avec l'utilisateur.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe MainWindow.
     * @param parent Le widget parent (par défaut nullptr).
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Destructeur de la classe MainWindow.
     */
    ~MainWindow();

private slots:

    // Les slots correspondant aux actions de l'utilisateur

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_7_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void updateUi();

protected:

    /**
     * @brief Gère l'événement d'appui sur une touche du clavier.
     * @param event L'événement clavier.
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief Gère l'événement de relâchement d'une touche du clavier.
     * @param event L'événement clavier.
     */
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui; /**< Interface utilisateur. */
    MyRobot *robot; /**< Robot. */
    Camera *camera; /**< Caméra. */
    /**
     * @brief Définit le niveau de la batterie.
     * @param value La valeur du niveau de la batterie.
     */
    void setBat(float value);
    /**
     * @brief Définit les valeurs des capteurs infrarouges.
     * @param avGauche La valeur du capteur infrarouge avant gauche.
     * @param avDroite La valeur du capteur infrarouge avant droit.
     * @param arGauche La valeur du capteur infrarouge arrière gauche.
     * @param arDroite La valeur du capteur infrarouge arrière droit.
     */
    void setIr(unsigned short avGauche, unsigned short avDroite, unsigned short arGauche, unsigned short arDroite);

    void setOdometry(long left, long right);

    void setVitesse();
};
#endif // MAINWINDOW_H
