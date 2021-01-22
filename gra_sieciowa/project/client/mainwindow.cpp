#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QThread>
#include <QHostAddress>
#include <QTimer>

#include "serversocket.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sock = new ServerSocket(QHostAddress::LocalHost,12345, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send() {
    sock->sendData(QByteArray("k00****"));
}

void MainWindow::on_pushButton_clicked()
{
//    QTimer *timer = new QTimer(this);

//    connect(timer, SIGNAL(timeout()), this, SLOT(send()));
//    timer->start(1000);
    PlayerAction gracz{.actions=moveLeft,.posX = 2, .posY = 3 };
    sock->sendPlayerAction(gracz);
}
