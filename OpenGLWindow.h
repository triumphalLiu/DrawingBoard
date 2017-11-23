#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QColor>
#include <QDebug>
#include <QGLWidget>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QString>
#include <iostream>
#include <windows.h>
#include <glut.h>
#include <vector>
#include <cmath>
#include <cstdlib>

struct Edge{
    int ymax;
    double x;
    double dx;
    Edge *next;
};

struct Entity{
    double x;
    double y;
    double color[3];
    unsigned size;
    unsigned pid;
    bool chosen;
};

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    unsigned currentID;
    int currentMode;
    unsigned currentPointSize;
    double currentColor[3];

    bool isLeftButtonPressed;
    bool isChoosingPoints;

public:
    OpenGLWindow(QWidget *parent = 0);
    ~OpenGLWindow();

    std::vector<Entity> points;
    std::vector<Entity> trashPoints;
    //std::vector<Entity> chosenPoints;
    std::vector<std::pair<double, double>> tempPoints;

    void cleanTempPoints(){while(!tempPoints.empty()) {tempPoints.pop_back();}}
    void cleanTrashPoints(){while(!trashPoints.empty()) {trashPoints.pop_back();}} //清除Redo轨迹
    void cleanPoints(){while(!points.empty()) {points.pop_back();}}

    void debugPoints(){
        for(std::vector<Entity>::iterator ite = points.begin(); ite != points.end(); ite++)
            qDebug() << (*ite).x << (*ite).y << (*ite).color[0] << (*ite).color[1] << (*ite).color[2] << (*ite).size << (*ite).pid;
    }

    void changeMode(int m){currentMode = m;}
    int getMode(){return currentMode;}

    void setCurrentColor(double r, double g, double b){currentColor[0] = r; currentColor[1] = g; currentColor[2] = b; glColor3d(r, g, b);}
    void setCurrentPointSize(int x){currentPointSize = x; glPointSize(currentPointSize);}

    void drawPoint(double x, double y);
    void drawLine(double x1, double y1, double x2, double y2);
    void drawCruve();
    void drawCircle(double xc, double yc, double r);
    void drawEllipse(double x0, double y0, double a, double b);
    void drawRect(double x1, double y1, double x2, double y2);
    void drawFilledRect(double x1, double y1, double x2, double y2);
    void drawPoligon();
    void drawFilledPoligon();

    void chooseRect(double x1, double y1, double x2, double y2);
    void choosePoligon();
    void chooseCancel(){
        for(std::vector<Entity>::iterator ite = points.begin(); ite != points.end(); ite++)
            (*ite).chosen = false;
        isChoosingPoints = false;
    }
    bool isPointInPoligon(double x, double y);
    void chooseInvert(){
        for(std::vector<Entity>::iterator ite = points.begin(); ite != points.end(); ite++)
            (*ite).chosen = !((*ite).chosen);
        update();
    }

    void saveToFile(char *filepath);
    void openFile(char *filepath);

    void traceUndo();
    void traceRedo();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // OPENGLWINDOW_H
