#include "persona.h"

Persona::Persona(const QString &nombre, const QString &dni)
    : m_nombre(nombre), m_dni(dni)
{
}

void Persona::setNombre(const QString &nombre)
{
    m_nombre = nombre;
}

QString Persona::getNombre() const
{
    return m_nombre;
}

void Persona::setDni(const QString &dni)
{
    m_dni = dni;
}

QString Persona::getDni() const
{
    return m_dni;
}

void Persona::getInfo() const
{
    qDebug() << "Nombre:" << m_nombre;
    qDebug() << "DNI:" << m_dni;
}
