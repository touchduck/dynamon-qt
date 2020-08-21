#include "DataWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataWindow w;
    //w.resize(800, 480);
    w.show();

    return a.exec();
}
