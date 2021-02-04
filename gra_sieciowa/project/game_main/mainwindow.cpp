#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "clientgame.h"
#include <QMovie>
#include <QDir>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie("../../../gra_sieciowa/project/animation.gif", QByteArray(), this);
    ui->movieLabel->setMovie(movie);
    movie->start();
    QPixmap *pixmap = new QPixmap("../../../gra_sieciowa/project/background.jpeg");
    QPixmap *pixmap2 = new QPixmap("../../../gra_sieciowa/project/gamepad.png");
    ui->background->setPixmap(*pixmap);
    ui->gamepad_1->setPixmap(*pixmap2);
    ui->gamepad_2->setPixmap(*pixmap2);
    ui->gamepad_3->setPixmap(*pixmap2);
    ui->gamepad_4->setPixmap(*pixmap2);
    ui->gamepad_5->setPixmap(*pixmap2);
    ui->gamepad_6->setPixmap(*pixmap2);
    ui->gamepad_7->setPixmap(*pixmap2);
    ui->gamepad_8->setPixmap(*pixmap2);
    ui->gamepad_9->setPixmap(*pixmap2);
    ui->gamepad_10->setPixmap(*pixmap2);
    ui->gamepad_11->setPixmap(*pixmap2);
    ui->gamepad_12->setPixmap(*pixmap2);

    ui->verticalLayout->addWidget(ui->gamepad_1);
    ui->verticalLayout->addWidget(ui->gamepad_2);
    ui->verticalLayout->addWidget(ui->gamepad_3);
    ui->verticalLayout->addWidget(ui->gamepad_4);
    ui->verticalLayout->addWidget(ui->gamepad_5);
    ui->verticalLayout->addWidget(ui->gamepad_6);

    ui->verticalLayout_2->addWidget(ui->gamepad_7);
    ui->verticalLayout_2->addWidget(ui->gamepad_8);
    ui->verticalLayout_2->addWidget(ui->gamepad_9);
    ui->verticalLayout_2->addWidget(ui->gamepad_10);
    ui->verticalLayout_2->addWidget(ui->gamepad_11);
    ui->verticalLayout_2->addWidget(ui->gamepad_12);

    delete pixmap;
    delete pixmap2;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    const QString serverIpText = ui->textEdit->toPlainText();
    const QString portText = ui->textEdit_2->toPlainText();
    quint16 port = portText.toUShort();
    ClientGame* newGame;
    newGame = new ClientGame();
    newGame->initGame(QHostAddress(serverIpText), port);
    newGame->show();
    newGame->setFocusPolicy(Qt::NoFocus);
    MainWindow::hide();
}
