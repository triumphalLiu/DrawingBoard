#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionCheck_triggered();

    void on_drawLine_triggered();
    void on_drawPoint_triggered();
    void on_drawCurve_triggered();
    void on_drawCircle_triggered();
    void on_drawEllipse_triggered();
    void on_drawRect_triggered();
    void on_drawFilledRect_triggered();
    void on_drawPoligon_triggered();
    void on_drawFilledPoligon_triggered();

    void on_Point_clicked();
    void on_Line_clicked();
    void on_Curve_clicked();
    void on_Circle_clicked();
    void on_Ellipse_clicked();
    void on_Rect_clicked();
    void on_FilledRect_clicked();
    void on_Poligon_clicked();
    void on_FilledPoligon_clicked();

    void on_ButtonChooseColor_clicked();

    void on_PointSize_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H