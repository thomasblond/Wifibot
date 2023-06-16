#ifndef CAMERA_H
#define CAMERA_H
#include <QGridLayout>
#include <QWebEngineView>
#include <QMainWindow>

/**
 * @brief Classe représentant une caméra.
 *
 * La classe Camera permet de contrôler les mouvements de la caméra en utilisant la classe QWebEngineView pour afficher la vue de la caméra et la classe QMainWindow pour la fenêtre principale.
 */
class Camera {

private:
    QWebEngineView *view; /**< Vue de la caméra. */
    QMainWindow *mainWindow; /**< Fenêtre principale. */

public:

    /**
     * @brief Constructeur par défaut de la classe Camera.
     */
    Camera();

    //Mouvements caméra
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};

#endif // CAMERA_H
