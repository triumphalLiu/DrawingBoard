#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QDebug>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include <QColor>
#include <QPainter>
#include <QPaintEvent>
#include <iostream>
#include <windows.h>
#include <glut.h>
#include <vector>
class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    int currentMode;
    unsigned currentPointSize;

public:
    OpenGLWindow(QWidget *parent = 0);
    ~OpenGLWindow();

    void changeMode(int m){currentMode = m;}
    std::vector<std::pair<double, double>> points;
    std::vector<std::pair<double, double>> tempPoints;
    void cleanTempPoints(){while(!tempPoints.empty()) tempPoints.pop_back();}
    void debugPoints(){
        for(std::vector<std::pair<double, double>>::iterator ite = points.begin(); ite != points.end(); ite++)
            qDebug() << (*ite).first << " " << (*ite).second;
    }
    void drawPoint(int x, int y);
    void drawLine(double x1, double y1, double x2, double y2);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
};

#endif // OPENGLWINDOW_H
