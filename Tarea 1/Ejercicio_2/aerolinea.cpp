#include "aerolinea.h"
#include "vuelo.h"
#include "pasajero.h"
#include "reserva.h"
#include <QDebug>

Aerolinea::Aerolinea() {}

Aerolinea::~Aerolinea()
{
    qDebug() << "\nLiberando memoria...";
    qDeleteAll(m_vuelos);
    qDeleteAll(m_pasajeros);
    qDeleteAll(m_reservas);
    qDebug() << "Memoria liberada.";
}

void Aerolinea::agregarVuelo(Vuelo* vuelo)
{
    m_vuelos.append(vuelo);
}

void Aerolinea::registrarPasajero(Pasajero* pasajero)
{
    m_pasajeros.append(pasajero);
}

Pasajero* Aerolinea::buscarPasajero(const QString &dni)
{
    for (Pasajero* p : m_pasajeros) {
        if (p->getDni() == dni) {
            return p;
        }
    }
    return nullptr;
}

Vuelo* Aerolinea::buscarVuelo(const QString &numeroVuelo)
{
    for (Vuelo* v : m_vuelos) {
        if (v->getNumeroVuelo() == numeroVuelo) {
            return v;
        }
    }
    return nullptr;
}

Reserva* Aerolinea::realizarReserva(const QString &dniPasajero, const QString &numeroVuelo, const QString &numeroAsiento)
{
    Pasajero* pasajero = buscarPasajero(dniPasajero);
    if (!pasajero) {
        qDebug() << "Error: Pasajero con DNI" << dniPasajero << "no encontrado.";
        return nullptr;
    }

    Vuelo* vuelo = buscarVuelo(numeroVuelo);
    if (!vuelo) {
        qDebug() << "Error: Vuelo" << numeroVuelo << "no encontrado.";
        return nullptr;
    }

    Asiento* asiento = vuelo->getAsiento(numeroAsiento);

    if (!asiento) {
        qDebug() << "Error: El asiento" << numeroAsiento << "no existe en el vuelo" << numeroVuelo;
        return nullptr;
    }

    if (!asiento->isDisponible()) {
        qDebug() << "Error: El asiento" << numeroAsiento << "ya está ocupado.";
        return nullptr;
    }

    asiento->ocupar();
    Reserva* nuevaReserva = new Reserva(pasajero, vuelo, numeroAsiento);
    m_reservas.append(nuevaReserva);

    qDebug() << "Reserva realizada con éxito!";
    return nuevaReserva;
}
