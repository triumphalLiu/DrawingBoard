#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawLine_triggered()
{
    ui->openGLWidget->changeMode(1);
    ui->openGLWidget->cleanTempPoints();
}

void MainWindow::on_drawPoint_triggered()
{
    ui->openGLWidget->changeMode(0);
    ui->openGLWidget->cleanTempPoints();
}

void MainWindow::on_actionCheck_triggered()
{
    ui->openGLWidget->debugPoints();
}
