#include <QApplication>
#include "ventanainventario.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaInventario w;
    w.show();
    return a.exec();
}
