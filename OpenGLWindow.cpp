#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(QWidget *parent)
    :QOpenGLWidget(parent)
{
    currentMode = 0;
    currentPointSize = 5;
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0, 1.0, 1.0,1.0);
    glPointSize(currentPointSize);
    glColor3d(1.0,0.0,0.0);
}

void OpenGLWindow::paintGL()
{
    glBegin(GL_POINTS);
    for(std::vector<std::pair<double, double>>::iterator ite = points.begin(); ite != points.end(); ite++)
    {
        glVertex3d((*ite).first, (*ite).second, 0);
    }
    glEnd();
}

void OpenGLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, this->size().width(), 0, this->size().height());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLWindow::mousePressEvent(QMouseEvent *event)
{
    int loc_x = event->localPos().x();
    int loc_y = this->size().height() - event->localPos().y();
    if(event->button() == Qt::LeftButton && currentMode == 0)
    {
        points.push_back(std::make_pair(loc_x, loc_y));
    }
    else if(currentMode == 1)
    {
        if(event->button() == Qt::LeftButton)
        {
            if(tempPoints.size() < 2)
            {
                tempPoints.push_back(std::make_pair(loc_x, loc_y));
            }
            else if(tempPoints.size() == 2)
            {
                int tmpx = (*(tempPoints.begin())).first;
                int tmpy = (*(tempPoints.begin())).second;
                tempPoints.pop_back();
                tempPoints.pop_back();
                tempPoints.push_back(std::make_pair(tmpx, tmpy));
                tempPoints.push_back(std::make_pair(loc_x, loc_y));
            }
        }
        else if(event->button() == Qt::RightButton && tempPoints.size() == 2)
        {
            drawLine((*(tempPoints.begin())).first, (*(tempPoints.begin())).second, (*(++tempPoints.begin())).first, (*(++tempPoints.begin())).second);
            cleanTempPoints();
        }
    }

    update();
}

void OpenGLWindow::drawPoint(int x, int y)
{
    points.push_back(std::make_pair(x, y));
}

void OpenGLWindow::drawLine(double x1, double y1, double x2, double y2)
{
    drawPoint(x1, y1);
    drawPoint(x2, y2);
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int flag = (dx >= dy) ? 0 : 1;
    int a = (x2 > x1) ? 1 : -1;
    int b = (y2 > y1) ? 1 : -1;
    int x = x1;
    int y = y1;
    if(flag){
            int temp = dx;
            dx = dy;
            dy = temp;
    }
    int h = 2 * dy - dx;
    for (int i = 1; i <= dx; ++i) {
            drawPoint(x, y);
            if (h >= 0) {
                    if (!flag)
                            y += b;
                    else
                            x += a;
                    h -= 2 * dx;
            }
            if (!flag)
                    x += a;
            else
                    y += b;
            h += 2 * dy;
    }
}
