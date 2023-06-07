#ifndef CAMERA_H
#define CAMERA_H
#include <QGridLayout>
#include <QWebEngineView>
#include <QMainWindow>

class Camera {

private:
    QWebEngineView *view;
    QMainWindow *mainWindow;

public:
    Camera();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};

#endif // CAMERA_H
