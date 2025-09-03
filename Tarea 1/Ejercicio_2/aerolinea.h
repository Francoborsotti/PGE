#ifndef AEROLINEA_H
#define AEROLINEA_H

#include <QList>
#include <QString>

class Vuelo;
class Pasajero;
class Reserva;

class Aerolinea
{
public:
    // Constructor
    Aerolinea();

    // Destructor
    ~Aerolinea();

    // Métodos para añadir nuevos objetos al sistema
    void agregarVuelo(Vuelo* vuelo);
    void registrarPasajero(Pasajero* pasajero);

    Reserva* realizarReserva(const QString &dniPasajero, const QString &numeroVuelo, const QString &numeroAsiento);

    // Método de búsqueda
    Vuelo* buscarVuelo(const QString &numeroVuelo);

private:
    // Método de búsqueda privado
    Pasajero* buscarPasajero(const QString &dni);

    // Listas que almacenan punteros a todos los objetos del sistema.
    QList<Vuelo*> m_vuelos;
    QList<Pasajero*> m_pasajeros;
    QList<Reserva*> m_reservas;
};

#endif // AEROLINEA_H
