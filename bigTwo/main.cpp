#include "mainwindow.h"
#include <QApplication>

Mainwindow * mainwindow;

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    mainwindow = new Mainwindow();
    mainwindow->show();
    return a.exec();
}