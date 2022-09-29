#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SelectedDraw(int d)
{
    qDebug() << d;
    typeOfDraw = d;
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    switch (typeOfDraw)
    {
    case 0:
        break;
    case 1:

        painter.drawRect(30,30,40,20);
        break;
    case 2:
        painter.drawEllipse(30,30,30,30);
        break;
    }
}
