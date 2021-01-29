#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "game.h"
Game * newGame;

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


void MainWindow::on_pushButton_clicked()
{
    newGame = new Game();
    newGame->initGame();
    //newGame->generateLayoutOne();
    //newGame->addNewPlayer(QPoint(newGame->settings->player_point), QSize(newGame->settings->player_size));
    //newGame->addNewPlayer(QPoint(newGame->settings->player_point), QSize(newGame->settings->player_size));
    newGame->show();
    newGame->setFocusPolicy(Qt::NoFocus);
    MainWindow::hide();
}
