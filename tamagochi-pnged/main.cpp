#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setFixedSize(750,750);
    w.setMouseTracking(true);
    w.show();
    return a.exec();
}
