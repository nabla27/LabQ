#include "plot3d.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Plot3D w;
    w.show();
    return a.exec();
}
