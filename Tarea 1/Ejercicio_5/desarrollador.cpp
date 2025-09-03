#include "desarrollador.h"

Desarrollador::Desarrollador(const QString &id, const QString &nombre, double salarioBase, const QString &lenguaje)
    : Empleado(id, nombre, salarioBase), m_lenguajePrincipal(lenguaje), m_horasExtras(0), m_tarifaHoraExtra(50.0) {}

void Desarrollador::setHorasExtras(int horas)
{
    m_horasExtras = horas;
}

double Desarrollador::calcularSalarioAnual() const
{
    return (m_salarioBase * 12) + (m_horasExtras * m_tarifaHoraExtra);
}

void Desarrollador::mostrarDetalles() const
{
    qDebug() << "--- Detalles del Desarrollador ---";
    qDebug() << "ID:" << m_id;
    qDebug() << "Nombre:" << m_nombre;
    qDebug() << "Rol: Desarrollador";
    qDebug() << "Lenguaje Principal:" << m_lenguajePrincipal;
    qDebug() << "Salario Anual:" << calcularSalarioAnual();
    qDebug() << "--------------------------------";
}
