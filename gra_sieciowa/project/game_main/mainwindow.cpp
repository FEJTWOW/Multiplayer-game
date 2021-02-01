#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "game.h"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie("/home/student/oop_2020_gra_sieciowa/gra_sieciowa/project/animation.gif");
    ui->movieLabel->setMovie(movie);
    movie->start();
    setStyleSheet("background-image: /home/student/oop_2020_gra_sieciowa/gra_sieciowa/project/background.jpeg");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Game* newGame;
    newGame = new Game();
    newGame->initGame();
    newGame->show();
    newGame->setFocusPolicy(Qt::NoFocus);
    MainWindow::hide();
}
