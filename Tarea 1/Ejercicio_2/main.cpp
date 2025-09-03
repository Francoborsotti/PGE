#include <QCoreApplication>
#include <QDebug>
#include "aerolinea.h"
#include "vuelo.h"
#include "pasajero.h"
#include "reserva.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "--- Iniciando Simulación Simplificada de Vuelos ---";

    Aerolinea miAerolinea;

    miAerolinea.agregarVuelo(new Vuelo("AR1500"));
    miAerolinea.agregarVuelo(new Vuelo("IB6849"));
    miAerolinea.registrarPasajero(new Pasajero("Lionel Messi", "30123456"));
    miAerolinea.registrarPasajero(new Pasajero("Bizarrap", "41987654"));

    qDebug() << "\n--- Realizando Reservas ---";

    Vuelo* vueloAChequear = miAerolinea.buscarVuelo("AR1500");
    if(vueloAChequear) {
        vueloAChequear->mostrarAsientosDisponibles();
    }

    Reserva* reserva1 = miAerolinea.realizarReserva("30123456", "AR1500", "1A");
    if (reserva1) {
        qDebug() << reserva1->getConfirmacion();
    }

    qDebug() << "\n--- Intentando reservar asiento ya ocupado ---";
    miAerolinea.realizarReserva("41987654", "AR1500", "1A");


    qDebug() << "\n--- Realizando segunda reserva exitosa ---";
    Reserva* reserva2 = miAerolinea.realizarReserva("41987654", "AR1500", "2C");
    if(reserva2) {
        qDebug() << reserva2->getConfirmacion();
    }

    qDebug() << "\n--- Estado final de los asientos ---";
    if(vueloAChequear) {
        vueloAChequear->mostrarAsientosDisponibles();
    }

    qDebug() << "\n--- Simulación Finalizada ---";

    return 0;
}
