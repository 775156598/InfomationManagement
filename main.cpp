#include "mainwindow.h"
#include <QApplication>
#include "loginin.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginin *lg = new loginin();
    lg->show();
    return a.exec();
}
