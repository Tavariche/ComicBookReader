#include "CBWindow.h"
#include <QApplication>
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBWindow w;
    w.show();

    return a.exec();
}