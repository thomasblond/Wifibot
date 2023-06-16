#include "camera.h"


/**
 * @brief Classe permettant de contrôler une caméra.
 *
 * La classe Camera utilise un objet QNetworkAccessManager pour envoyer des requêtes HTTP à une adresse IP spécifique afin de contrôler les mouvements de la caméra.
 * Chaque fonction de mouvement envoie une requête GET à une URL différente correspondant à un mouvement spécifique de la caméra.
 */
Camera::Camera()
{
}

QNetworkAccessManager *manager = new QNetworkAccessManager();


/**
 * @brief Déplace la caméra vers le bas.
 *
 * Envoie une requête GET à l'URL spécifiée pour déplacer la caméra vers le bas.
 */
void Camera::moveDown(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
}

/**
 * @brief Déplace la caméra vers le haut.
 *
 * Envoie une requête GET à l'URL spécifiée pour déplacer la caméra vers le haut.
 */
void Camera::moveUp(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
}

/**
 * @brief Déplace la caméra vers la gauche.
 *
 * Envoie une requête GET à l'URL spécifiée pour déplacer la caméra vers la gauche.
 */
void Camera::moveLeft(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}

/**
 * @brief Déplace la caméra vers la droite.
 *
 * Envoie une requête GET à l'URL spécifiée pour déplacer la caméra vers la droite.
 */
void Camera::moveRight(){
    manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}
