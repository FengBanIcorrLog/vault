#include <QtGui/QApplication>
#include "mainwindow.h"

#include "qtsvgz_plugin.h"

Q_IMPORT_PLUGIN(svgz)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
