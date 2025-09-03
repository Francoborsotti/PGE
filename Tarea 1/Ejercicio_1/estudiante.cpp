#include "estudiante.h"

Estudiante::Estudiante(const QString &nombre, const QString &dni)
    : Persona(nombre, dni)
{
}

void Estudiante::agregarMateria(const QString &materia, double calificacion)
{
    if (!m_materias.contains(materia)) {
        m_materias.append(materia);
    }
    m_calificaciones.insert(materia, calificacion);
}

double Estudiante::getCalificacion(const QString &materia) const
{
    return m_calificaciones.value(materia, -1.0);
}

QList<QString> Estudiante::getMateriasCursadas() const
{
    return m_materias;
}

void Estudiante::getInfo() const
{
    qDebug() << "--- Información del Estudiante ---";
    Persona::getInfo();
    qDebug() << "Materias Cursadas:";
    for (const QString &materia : m_materias) {
        qDebug() << "  -" << materia << "- Calificación:" << getCalificacion(materia);
    }
    qDebug() << "---------------------------------";
}
