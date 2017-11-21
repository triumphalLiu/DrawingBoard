#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow(QWidget *parent)
    :QOpenGLWidget(parent)
{
    currentMode = 0;
    currentPointSize = 5;
    currentID = 0;
    currentColor[0] = 1;
    currentColor[1] = 0;
    currentColor[2] = 0;
}

OpenGLWindow::~OpenGLWindow()
{

}

void OpenGLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0, 1.0, 1.0,1.0);
    glPointSize(currentPointSize);
    glColor3d(currentColor[0], currentColor[1], currentColor[2]);
}

void OpenGLWindow::paintGL()
{
    for(std::vector<Entity>::iterator ite = points.begin(); ite != points.end(); ite++)
    {
        glColor3d((*ite).color[0], (*ite).color[1], (*ite).color[2]);
        glPointSize((*ite).size);
        glBegin(GL_POINTS);
        glVertex3d((*ite).x, (*ite).y, 0);
        glEnd();
    }
    glColor3d(currentColor[0], currentColor[1], currentColor[2]);
    glPointSize(currentPointSize);
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
    if(event->button() == Qt::LeftButton && currentMode == 0) //point
    {
        drawPoint(loc_x, loc_y);
        currentID++;
    }
    else if(currentMode == 1) //line
    {
        if(event->button() == Qt::LeftButton)
        {
            if(tempPoints.size() == 0)
            {
                tempPoints.push_back(std::make_pair(loc_x, loc_y));
            }
            else if(tempPoints.size() == 1)
            {
                tempPoints.push_back(std::make_pair(loc_x, loc_y));
                drawLine((*(tempPoints.begin())).first, (*(tempPoints.begin())).second, (*(++tempPoints.begin())).first, (*(++tempPoints.begin())).second);
                cleanTempPoints();
                currentID++;
            }
        }
    }
    else if(currentMode == 2) //cruve
    {
        if(event->button() == Qt::LeftButton && tempPoints.size() < 3)
        {
            tempPoints.push_back(std::make_pair(loc_x, loc_y));
        }
        else if(event->button() == Qt::LeftButton && tempPoints.size() == 3)
        {
            tempPoints.push_back(std::make_pair(loc_x, loc_y));
            drawCruve();
            cleanTempPoints();
            currentID++;
        }
    }
    else if(currentMode == 3) //circle
    {
        if(event->button() == Qt::LeftButton && tempPoints.size() == 0)
        {
            tempPoints.push_back(std::make_pair(loc_x, loc_y));
        }
        else if(event->button() == Qt::LeftButton && tempPoints.size() == 1)
        {
            double CircleRadius = sqrt(pow((loc_x - tempPoints[0].first), 2) + pow((loc_y - tempPoints[0].second), 2));
            drawCircle(tempPoints[0].first, tempPoints[0].second, CircleRadius);
            cleanTempPoints();
            currentID++;
        }
    }
    else if(currentMode == 4) // ellipse
    {
        if(event->button() == Qt::LeftButton && tempPoints.size() < 2)
        {
            tempPoints.push_back(std::make_pair(loc_x, loc_y));
        }
        else if(event->button() == Qt::LeftButton && tempPoints.size() == 2)
        {
            tempPoints.push_back(std::make_pair(loc_x, loc_y));
            double ra = sqrt(pow((tempPoints[1].first - tempPoints[0].first), 2) + pow((tempPoints[1].second - tempPoints[0].second), 2));
            double rb = sqrt(pow((loc_x - tempPoints[0].first), 2) + pow((loc_y - tempPoints[0].second), 2));
            drawEllipse(tempPoints[0].first, tempPoints[0].second, ra, rb);
            cleanTempPoints();
            currentID++;
        }
    }
    else if(currentMode == 5 || currentMode == 6) //rect
    {
        if(event->button() == Qt::LeftButton && tempPoints.size() == 0)
        {
            tempPoints.push_back(std::make_pair(loc_x, loc_y));
        }
        else if(event->button() == Qt::LeftButton && tempPoints.size() == 1)
        {
            tempPoints.push_back(std::make_pair(loc_x, loc_y));
            if(currentMode == 5)
                drawRect(tempPoints[0].first, tempPoints[0].second, tempPoints[1].first, tempPoints[1].second);
            else if(currentMode == 6)
                drawFilledRect(tempPoints[0].first, tempPoints[0].second, tempPoints[1].first, tempPoints[1].second);
            cleanTempPoints();
            currentID++;
        }
    }
    else if(currentMode == 7 || currentMode == 8) //poligon
    {
        if(event->button() == Qt::LeftButton)
            tempPoints.push_back(std::make_pair(loc_x, loc_y));
        else if(event->button() == Qt::RightButton)
        {
            if(currentMode == 7)
                drawPoligon();
            else if(currentMode == 8)
                drawFilledPoligon();
            cleanTempPoints();
            currentID++;
        }
    }
    update();
}

void OpenGLWindow::traceUndo()
{
    if(points.size() == 0) return;
    qDebug() << "Undo";
    currentID -= 1;
    std::vector<Entity>::iterator ite = points.end() - 1;
    while((*ite).pid == currentID)
    {
        trashPoints.push_back(*ite);
        points.pop_back();
        if(points.size() > 0)
            ite = points.end() - 1;
        else break;
    }
    update();
}

void OpenGLWindow::traceRedo()
{
    if(trashPoints.size() == 0) return;
    qDebug() << "Redo";
    std::vector<Entity>::iterator ite = trashPoints.end() - 1;
    while((*ite).pid == currentID)
    {
        points.push_back(*ite);
        trashPoints.pop_back();
        if(trashPoints.size() > 0)
            ite = trashPoints.end() - 1;
        else break;
    }
    currentID += 1;
    update();
}

void OpenGLWindow::drawPoint(double x, double y)
{
    cleanTrashPoints();
    Entity *newEntity = new Entity;
    newEntity->x = x;
    newEntity->y = y;
    newEntity->color[0] = currentColor[0];
    newEntity->color[1] = currentColor[1];
    newEntity->color[2] = currentColor[2];
    newEntity->size = currentPointSize;
    newEntity->pid = currentID;
    points.push_back(*newEntity);
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

void OpenGLWindow::drawCruve()
{
    for (GLfloat t = 0; t <= 1.0; t += 0.001) {
        GLfloat x = tempPoints[0].first*pow(1.0f - t, 3) + 3 * tempPoints[1].first*t*pow(1.0f - t, 2) + 3 * tempPoints[2].first*t*t*(1.0f - t) + tempPoints[3].first*pow(t, 3);
        GLfloat y = tempPoints[0].second*pow(1.0f - t, 3) + 3 * tempPoints[1].second*t*pow(1.0f - t, 2) + 3 * tempPoints[2].second*t*t*(1.0f - t) + tempPoints[3].second*pow(t, 3);
        drawPoint(x, y);
    }
}

void OpenGLWindow::drawCircle(double xc, double yc, double r)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    drawPoint(xc + x, yc + y);
    drawPoint(xc - x, yc + y);
    drawPoint(xc + x, yc - y);
    drawPoint(xc - x, yc - y);
    drawPoint(xc + y, yc + x);
    drawPoint(xc - y, yc + x);
    drawPoint(xc + y, yc - x);
    drawPoint(xc - y, yc - x);
    while (x < y){
        if (d < 0)
            d = d + 4 * x + 6;
        else{
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
        drawPoint(xc + x, yc + y);
        drawPoint(xc - x, yc + y);
        drawPoint(xc + x, yc - y);
        drawPoint(xc - x, yc - y);
        drawPoint(xc + y, yc + x);
        drawPoint(xc - y, yc + x);
        drawPoint(xc + y, yc - x);
        drawPoint(xc - y, yc - x);
    }
}

void OpenGLWindow::drawEllipse(double x0, double y0, double a, double b)
{
    double sqa = a*a;
    double sqb = b*b;
    double d = sqb + sqa*(0.25 - b);
    int x = 0;
    int y = b;
    drawPoint((x0 + x), (y0 + y));
    drawPoint((x0 + x), (y0 - y));
    drawPoint((x0 - x), (y0 - y));
    drawPoint((x0 - x), (y0 + y));
    while (sqb*(x + 1) < sqa*(y - 0.5))
    {
        if (d < 0)
            d += sqb*(2 * x + 3);
        else
        {
            d += (sqb*(2 * x + 3) + sqa*((-2)*y + 2));
            --y;
        }
        ++x;
        drawPoint((x0 + x), (y0 + y));
        drawPoint((x0 + x), (y0 - y));
        drawPoint((x0 - x), (y0 - y));
        drawPoint((x0 - x), (y0 + y));
    }
    d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
    while (y > 0)
    {
        if (d < 0)
        {
            d += sqb * (2 * x + 2) + sqa * ((-2) * y + 3);
            ++x;
        }
        else
            d += sqa * ((-2) * y + 3);
        --y;
        drawPoint((x0 + x), (y0 + y));
        drawPoint((x0 + x), (y0 - y));
        drawPoint((x0 - x), (y0 - y));
        drawPoint((x0 - x), (y0 + y));
    }
}

void OpenGLWindow::drawRect(double x1, double y1, double x2, double y2)
{
    drawLine(x1, y1, x1, y2);
    drawLine(x1, y1, x2, y1);
    drawLine(x1, y2, x2, y2);
    drawLine(x2, y1, x2, y2);
}

void OpenGLWindow::drawFilledRect(double x1, double y1, double x2, double y2)
{
    double smallX = (x1 < x2) ? x1 : x2;
    double bigX = (x1 < x2) ? x2 : x1;
    double smallY = (y1 < y2) ? y1 : y2;
    double bigY = (y1 < y2) ? y2 : y1;
    for (double i = smallX; i <= bigX; i += 1)
            for (double j = smallY; j <= bigY; j += 1)
                    drawPoint(i, j);
}

void OpenGLWindow::drawPoligon()
{
    for (unsigned i = 1; i < tempPoints.size(); ++i) {
        drawLine(tempPoints[i - 1].first, tempPoints[i - 1].second, tempPoints[i].first, tempPoints[i].second);
    }
    drawLine(tempPoints[tempPoints.size()-1].first, tempPoints[tempPoints.size()-1].second, tempPoints[0].first, tempPoints[0].second);
}

void OpenGLWindow::drawFilledPoligon()
{
    //Todo:扫描线算法
}

void OpenGLWindow::saveToFile(char *filepath)
{
    //Todo:保存文件
    qDebug() << filepath;
}

void OpenGLWindow::openFile(char *filepath)
{
    //Todo：打开文件
    qDebug() << filepath;
}
