#include "mainwindow.h"

Ui::MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
}

Ui::MainWindow::~MainWindow()
{
    delete ui;
}
