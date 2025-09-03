#include "reserva.h"
#include "pasajero.h"
#include "vuelo.h"
#include <QRandomGenerator>
#include <QDebug>


Reserva::Reserva(Pasajero* pasajero, Vuelo* vuelo, const QString &numeroAsiento)
    : m_pasajero(pasajero), m_vuelo(vuelo), m_numeroAsiento(numeroAsiento)
{
    quint32 randomNum = QRandomGenerator::global()->generate();
    m_codigoReserva = vuelo->getNumeroVuelo().left(2) + QString::number(randomNum).left(4);
}

QString Reserva::getConfirmacion() const
{
    if (!m_pasajero || !m_vuelo) {
        return "Reserva inválida.";
    }
    return QString("Confirmación de Reserva: %1\n  Pasajero: %2 (DNI: %3)\n  Vuelo: %4 Asiento: %5")
        .arg(m_codigoReserva)
        .arg(m_pasajero->getNombre())
        .arg(m_pasajero->getDni())
        .arg(m_vuelo->getNumeroVuelo())
        .arg(m_numeroAsiento);
}
