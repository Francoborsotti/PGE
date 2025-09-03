#ifndef RESERVA_H
#define RESERVA_H

#include <QString>

class Pasajero;
class Vuelo;

class Reserva
{
public:
    Reserva(Pasajero* pasajero, Vuelo* vuelo, const QString &numeroAsiento);

    QString getConfirmacion() const;

private:
    QString m_codigoReserva;
    Pasajero* m_pasajero;
    Vuelo* m_vuelo;
    QString m_numeroAsiento;
};

#endif // RESERVA_H
