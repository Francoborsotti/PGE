#include "gerente.h"

Gerente::Gerente(const QString &id, const QString &nombre, double salarioBase, double bonoGestion)
    : Empleado(id, nombre, salarioBase), m_bonoGestion(bonoGestion) {}

double Gerente::calcularSalarioAnual() const
{
    return (m_salarioBase * 12) + m_bonoGestion;
}

void Gerente::mostrarDetalles() const
{
    qDebug() << "--- Detalles del Gerente ---";
    qDebug() << "ID:" << m_id;
    qDebug() << "Nombre:" << m_nombre;
    qDebug() << "Rol: Gerente";
    qDebug() << "Salario Anual:" << calcularSalarioAnual();
    qDebug() << "--------------------------";
}
