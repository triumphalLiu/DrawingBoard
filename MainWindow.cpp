#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    ui->statusBar->setSizeGripEnabled(false);
    ui->statusBar->showMessage(tr("就绪-移动所选区域"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCheck_triggered()
{
    ui->openGLWidget->debugPoints();
}

void MainWindow::on_drawPoint_triggered()
{
    ui->openGLWidget->setCurrentMode(0);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-画点"));
}

void MainWindow::on_drawLine_triggered()
{
    ui->openGLWidget->setCurrentMode(1);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-画线"));
}

void MainWindow::on_drawCurve_triggered()
{
    ui->openGLWidget->setCurrentMode(2);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-画曲线"));
}

void MainWindow::on_drawCircle_triggered()
{
    ui->openGLWidget->setCurrentMode(3);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-画圆"));
}

void MainWindow::on_drawEllipse_triggered()
{
    ui->openGLWidget->setCurrentMode(4);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-画椭圆"));
}

void MainWindow::on_drawRect_triggered()
{
    ui->openGLWidget->setCurrentMode(5);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-画矩形"));
}

void MainWindow::on_drawFilledRect_triggered()
{
    ui->openGLWidget->setCurrentMode(6);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-填充矩形"));
}

void MainWindow::on_drawPoligon_triggered()
{
    ui->openGLWidget->setCurrentMode(7);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-多边形"));
}

void MainWindow::on_drawFilledPoligon_triggered()
{
    ui->openGLWidget->setCurrentMode(8);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-填充多边形"));
}

void MainWindow::on_ButtonChooseColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white);
    if(color.isValid()){
        int r, g, b;
        color.getRgb(&r, &g, &b);
        ui->openGLWidget->setCurrentColor(r/255.0, g/255.0, b/255.0);
    }
}

void MainWindow::on_Point_clicked()
{
    on_drawPoint_triggered();
}

void MainWindow::on_Line_clicked()
{
    on_drawLine_triggered();
}

void MainWindow::on_Curve_clicked()
{
    on_drawCurve_triggered();
}

void MainWindow::on_Circle_clicked()
{
    on_drawCircle_triggered();
}

void MainWindow::on_Ellipse_clicked()
{
    on_drawEllipse_triggered();
}

void MainWindow::on_Rect_clicked()
{
    on_drawRect_triggered();
}

void MainWindow::on_FilledRect_clicked()
{
    on_drawFilledRect_triggered();
}

void MainWindow::on_Poligon_clicked()
{
    on_drawPoligon_triggered();
}

void MainWindow::on_FilledPoligon_clicked()
{
    on_drawFilledPoligon_triggered();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "另存为...", ".", ("png图像文件(*.png)"));
    if(fileName.length() == 0) return;
    QByteArray bytearray = fileName.toLocal8Bit();
    char *temp = bytearray.data();
    ui->openGLWidget->saveToFile(temp);
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "打开文件", ".", ("png图像文件(*.png)"));
    if(fileNames.size() == 0) return;
    for(int i = 0; i < fileNames.size(); ++i)
    {
        QByteArray bytearray = fileNames[i].toLocal8Bit();
        char *temp = bytearray.data();
        if(temp == NULL) continue;
        ui->openGLWidget->openFile(temp);
    }
}

void MainWindow::on_newPaint_triggered()
{
    QMessageBox mb( "重建画布", "正在尝试重建画布，是否保存画布内容？", QMessageBox::Information, QMessageBox::Yes | QMessageBox::Default, QMessageBox::No, QMessageBox::Cancel | QMessageBox::Escape );
    mb.setButtonText( QMessageBox::Yes, "保存" );
    mb.setButtonText( QMessageBox::No, "不保存" );
    mb.setButtonText( QMessageBox::Cancel, "取消" );
    switch(mb.exec()) {
        case QMessageBox::Yes:
            on_actionSave_triggered();
        case QMessageBox::No:
            ui->openGLWidget->cleanPoints();
            ui->openGLWidget->cleanTempPoints();
            ui->openGLWidget->cleanTrashPoints();
            ui->openGLWidget->cleanChosenPoints();
            break;
        case QMessageBox::Cancel:
            break;
    }
}

void MainWindow::on_PointSize_currentIndexChanged(int index)
{
    ui->openGLWidget->setCurrentPointSize(index+1);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Z)) //撤销
    {
        ui->openGLWidget->traceUndo();
    }
    else if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_Y)) //恢复
    {
        ui->openGLWidget->traceRedo();
    }
    else if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_A)) //保存
    {
        on_actionSave_triggered();
    }
    else if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_O)) //打开
    {
        on_actionOpen_triggered();
    }
    else if((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_W)) //重建
    {
        on_newPaint_triggered();
    }
}

void MainWindow::on_chooseRect_triggered()
{
    on_ChooseRect_clicked();
}

void MainWindow::on_ChooseRect_clicked()
{
    ui->openGLWidget->setCurrentMode(9);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-选取矩形区域"));
}

void MainWindow::on_choosePologon_triggered()
{
    on_ChoosePoligon_clicked();
}

void MainWindow::on_ChoosePoligon_clicked()
{
    ui->openGLWidget->setCurrentMode(10);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-选取多边形区域"));
}

void MainWindow::on_chooseInvert_triggered()
{
    on_ChooseInvert_clicked();
}

void MainWindow::on_ChooseInvert_clicked()
{
    ui->openGLWidget->chooseInvert();
}

void MainWindow::on_Move_clicked()
{
    ui->openGLWidget->setCurrentMode(-1);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-移动所选区域"));
}

void MainWindow::on_move_triggered()
{
    on_Move_clicked();
}

void MainWindow::on_Rotate_clicked()
{
    QString text = QInputDialog::getText(NULL, tr("旋转所选区域"), tr("请输入旋转角度[-180°~180°]："));
    if(text == NULL)
        return;
    double angle = text.toDouble();
    if(angle < -180 || angle > 180)
        QMessageBox::information(NULL, "数据非法", "旋转角度区间[-180°~180°]", QMessageBox::Ok, QMessageBox::Ok);
    else ui->openGLWidget->rotateChosenZone(angle);
}

void MainWindow::on_rotate_triggered()
{
    on_Rotate_clicked();
}

void MainWindow::on_Zoom_clicked()
{
    QString text = QInputDialog::getText(NULL, tr("缩放所选区域"), tr("请输入缩放倍数(0~1000](%)："));
    if(text == NULL)
        return;
    double zoom = text.toDouble();
    if(zoom <= 0 || zoom > 1000)
        QMessageBox::information(NULL, "数据非法", "缩放区间(0~1000](%)", QMessageBox::Ok, QMessageBox::Ok);
    else ui->openGLWidget->zoomChosenZone(zoom/100.0);
}

void MainWindow::on_zoom_triggered()
{
    on_Zoom_clicked();
}

void MainWindow::on_Undo_clicked()
{
    ui->openGLWidget->traceUndo();
}

void MainWindow::on_Redo_clicked()
{
    ui->openGLWidget->traceRedo();
}

void MainWindow::on_undo_triggered()
{
    ui->openGLWidget->traceUndo();
}

void MainWindow::on_redo_triggered()
{
    ui->openGLWidget->traceRedo();
}

void MainWindow::on_actionViewCode_triggered()
{
    ShellExecute(NULL, TEXT("open"), TEXT("https://github.com/triumphalLiu/DrawingBoard"),
        NULL, NULL, SW_MINIMIZE);
}

void MainWindow::on_Delete_clicked()
{
    ui->openGLWidget->deleteChosenZone();
}

void MainWindow::on_deleteZone_triggered()
{
    ui->openGLWidget->deleteChosenZone();
}

void MainWindow::on_chooseByPid_triggered()
{
    ui->openGLWidget->setCurrentMode(11);
    ui->openGLWidget->cleanTempPoints();
    ui->statusBar->showMessage(tr("就绪-选取一个图元"));
}

void MainWindow::on_Choose_clicked()
{
    on_chooseByPid_triggered();
}
