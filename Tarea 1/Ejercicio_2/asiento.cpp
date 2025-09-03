#include "asiento.h"

Asiento::Asiento(const QString &numero)
    : m_numero(numero), m_disponible(true)
{
}

QString Asiento::getNumero() const
{
    return m_numero;
}

bool Asiento::isDisponible() const
{
    return m_disponible;
}

void Asiento::ocupar()
{
    m_disponible = false;
}

void Asiento::liberar()
{
    m_disponible = true;
}
