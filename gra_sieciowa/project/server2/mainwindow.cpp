#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    newGame = new ServerGame();
    newGame->initGame();
    newGame->generateLayoutOne();
    newGame->show();
    newGame->setFocusPolicy(Qt::NoFocus);
    ui->setupUi(this);
    MainWindow::hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

