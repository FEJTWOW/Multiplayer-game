#include "mainwindow.h"
#include "sender.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Sender sender;
    sender.show();
    return app.exec();
}
