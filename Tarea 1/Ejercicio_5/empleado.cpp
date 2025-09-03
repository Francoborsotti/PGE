#include "empleado.h"

Empleado::Empleado(const QString &id, const QString &nombre, double salarioBase)
    : m_id(id), m_nombre(nombre), m_salarioBase(salarioBase) {}

QString Empleado::getId() const
{
    return m_id;
}

QString Empleado::getNombre() const
{
    return m_nombre;
}
