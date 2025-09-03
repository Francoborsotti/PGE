#include "pasajero.h"

Pasajero::Pasajero(const QString &nombre, const QString &dni)
    : m_nombre(nombre), m_dni(dni)
{
}

QString Pasajero::getNombre() const
{
    return m_nombre;
}

QString Pasajero::getDni() const
{
    return m_dni;
}
