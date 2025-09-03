#ifndef PERSONA_H
#define PERSONA_H

#include <QString>
#include <QDebug>

class Persona
{
public:
    Persona(const QString &nombre = "", const QString &dni = "");

    void setNombre(const QString &nombre);
    QString getNombre() const;

    void setDni(const QString &dni);
    QString getDni() const;

    virtual void getInfo() const;

private:
    QString m_nombre;
    QString m_dni;
};

#endif // PERSONA_H
