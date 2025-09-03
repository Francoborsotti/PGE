#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "persona.h"
#include <QList>
#include <QMap>

class Estudiante : public Persona
{
public:
    Estudiante(const QString &nombre = "", const QString &dni = "");

    void agregarMateria(const QString &materia, double calificacion);
    double getCalificacion(const QString &materia) const;
    QList<QString> getMateriasCursadas() const;

    void getInfo() const override;

private:
    QList<QString> m_materias;
    QMap<QString, double> m_calificaciones;
};

#endif // ESTUDIANTE_H
