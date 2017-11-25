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
    double dx; //斜率
    Edge *next; //下条边
};

struct Entity{ //每个点的属性
    double x; //x坐标 左下角为0，0 下同
    double y; //y坐标
    double color[3]; //画笔颜色
    unsigned size; //画笔粗细
    unsigned pid; //图元编号
    bool chosen; //是否被选定
};

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    unsigned currentID; //当前图元编号
    int currentMode; //当前画图模式
    unsigned currentPointSize; //当前画笔粗细
    double currentColor[3]; //当前画笔颜色

    double originX; //记录鼠标起始点位置x
    double originY; //记录鼠标起始点位置y

    bool isLeftButtonPressed; //左键是否被按下
    bool isRightButtonPressed; //右键是否被按下
    bool isChoosingPoints; //是否正在选择区域
    bool isNewChosen; //是否新选择了一块区域
    bool isDrawPoligonJustNow; //是否刚画了多边形

    std::vector<Entity*> points; //画布上所有点的集合
    std::vector<Entity*> trashPoints; //被撤销的点的集合
    std::vector<Entity*> chosenPoints; //被选取点的集合
    std::vector<std::pair<double, double>> tempPoints; //用户画图的顶点集合

public:
    OpenGLWindow(QWidget *parent = 0);
    ~OpenGLWindow();

    void debugPoints() //debug专用 输出画布上所有的点
    {
        qDebug() << "------------------Debug Begins!";
        qDebug() << currentID << isChoosingPoints << isNewChosen;
        qDebug() << "--this is points";
        for(std::vector<Entity*>::iterator ite = points.begin(); ite != points.end(); ite++)
            qDebug() << (*ite)->x << (*ite)->y << (*ite)->color[0] << (*ite)->color[1] << (*ite)->color[2] << (*ite)->size << (*ite)->pid << (*ite)->chosen;
        qDebug() << "--this is ChosenPoints";
        for(std::vector<Entity*>::iterator ite = chosenPoints.begin(); ite != chosenPoints.end(); ite++)
            qDebug() << (*ite)->x << (*ite)->y << (*ite)->color[0] << (*ite)->color[1] << (*ite)->color[2] << (*ite)->size << (*ite)->pid << (*ite)->chosen;
        qDebug() << "--this is TrashPoints";
        for(std::vector<Entity*>::iterator ite = trashPoints.begin(); ite != trashPoints.end(); ite++)
            qDebug() << (*ite)->x << (*ite)->y << (*ite)->color[0] << (*ite)->color[1] << (*ite)->color[2] << (*ite)->size << (*ite)->pid << (*ite)->chosen;
        qDebug() << "------------------Debug End!";
    }

    void cleanTempPoints(){while(!tempPoints.empty()) {tempPoints.pop_back();}} //清空tempPoints
    void cleanTrashPoints(){while(trashPoints.size() > 0){delete trashPoints[trashPoints.size()-1];trashPoints.pop_back();}} //清空trashPoints 撤销后一旦开始画图即清空
    void cleanPoints(){while(points.size() > 0){delete points[points.size()-1];points.pop_back();}currentID = 0;} //清空points
    void cleanChosenPoints(){while(chosenPoints.size() > 0){delete chosenPoints[chosenPoints.size()-1];chosenPoints.pop_back();}} //清空chosenPoints 在chooseCancel中会被调用

    unsigned getPosByPID(unsigned id); //通过PID从points中
    int getMode(){return currentMode;} //获取画图模式
    int getTrashPointsAmounts(); //获取TrashPoints的ID数量

    void setCurrentMode(int m){currentMode = m; cleanTempPoints(); isDrawPoligonJustNow = false;} //修改画图模式获取插入位置
    void setCurrentColor(double r, double g, double b){currentColor[0] = r; currentColor[1] = g; currentColor[2] = b; glColor3d(r, g, b);} //设置画笔颜色
    void setCurrentPointSize(int x){currentPointSize = x; glPointSize(currentPointSize);} //设置画笔粗细

    void drawPoint(double x, double y); //画点
    void drawLine(double x1, double y1, double x2, double y2); //画线
    void drawCruve(); //画曲线
    void drawCircle(double xc, double yc, double r); //画圆
    void drawEllipse(double x0, double y0, double a, double b); //画椭圆
    void drawRect(double x1, double y1, double x2, double y2); //画矩形
    void drawFilledRect(double x1, double y1, double x2, double y2); //画填充矩形
    void drawPoligon(); //画多边形
    void drawFilledPoligon(); //画填充多边形

    void chooseRect(double x1, double y1, double x2, double y2); //选择一块矩形区域
    void choosePoligon(); //选择一块多边形区域
    bool isPointInPoligon(double x, double y); //判断点是否在tempPoint的顶点群组成的多边形内
    void chooseCancel() //取消选择
    {
        for(std::vector<Entity*>::iterator ite = points.begin(); ite != points.end(); ite++)
            (*ite)->chosen = false;
        isChoosingPoints = false;
        cleanChosenPoints();
        update();
    }
    void chooseInvert() //反向选择
    {
        cleanChosenPoints();
        for(std::vector<Entity*>::iterator ite = points.begin(); ite != points.end(); ite++)
        {
            (*ite)->chosen = !((*ite)->chosen);
            if((*ite)->chosen == true)
            {
                isChoosingPoints = true;
                isNewChosen = true;
            }
        }
        update();
    }

    void moveChosenZone(double offsetX, double offsetY); //移动所选区域
    void rotateChosenZone(double angle); //旋转所选区域
    void zoomChosenZone(double pix); //缩放所选区域
    void deleteChosenZone(); //删除所选区域
    void pickChosenPoints(); //从points中提取出被选中的点

    void saveToFile(char *filepath); //将画布内容保存到文件 TODO
    void openFile(char *filepath); //打开文件并画到画布 TODO

    void traceUndo(); //撤销
    void traceRedo(); //恢复

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // OPENGLWINDOW_H
