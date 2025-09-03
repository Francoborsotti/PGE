#include <QCoreApplication>
#include <QList>
#include <QDebug>
#include "gerente.h"
#include "desarrollador.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "===== Sistema de Gestión de RRHH =====";

    Gerente gerente1("G001", "Ana Gomez", 5000.0, 10000.0);
    Desarrollador dev1("D001", "Juan Perez", 2500.0, "C++");
    dev1.setHorasExtras(20);

    Desarrollador dev2("D002", "Maria Luz", 2600.0, "Python");

    QList<Empleado*> listaEmpleados;
    listaEmpleados.append(&gerente1);
    listaEmpleados.append(&dev1);
    listaEmpleados.append(&dev2);

    qDebug() << "\n--- Procesando Nómina de todos los Empleados ---";
    for (Empleado* emp : listaEmpleados) {
        emp->mostrarDetalles();
    }

    qDebug() << "\n===== Simulación Finalizada =====";

    return 0;
}
