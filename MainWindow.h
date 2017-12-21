#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMouseEvent>
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
    void on_newPaint_triggered();
    void on_actionExit_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionCheck_triggered();
    void on_actionViewCode_triggered();

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

    void on_chooseByPid_triggered();
    void on_ChooseByPid_clicked();
    void on_chooseRect_triggered();
    void on_ChooseRect_clicked();
    void on_choosePologon_triggered();
    void on_ChoosePoligon_clicked();
    void on_chooseInvert_triggered();
    void on_ChooseInvert_clicked();
    void on_Move_clicked();
    void on_move_triggered();
    void on_Rotate_clicked();
    void on_rotate_triggered();
    void on_Zoom_clicked();
    void on_zoom_triggered();
    void on_Delete_clicked();
    void on_deleteZone_triggered();

    void on_ButtonChooseColor_clicked();
    void on_PointSize_currentIndexChanged(int index);
    void on_three_d_mode_clicked();
    void on_action_3D_triggered();

    void on_Undo_clicked();
    void on_Redo_clicked();
    void on_undo_triggered();
    void on_redo_triggered();

private:
    Ui::MainWindow *ui;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
