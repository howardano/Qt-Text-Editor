#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1100, 800);
   // w.setWindowFlags(Qt::Window | Qt::WindowTitleHint);
    w.setMinimumSize(1195, 780);
    w.setMaximumSize(1195, 780);
    w.show();

    return a.exec();
}
