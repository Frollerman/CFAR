#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainWidget_ = new MainWidget(this);
    setCentralWidget(mainWidget_);
}

MainWindow::~MainWindow()
{
    delete mainWidget_;
    delete ui;
}

