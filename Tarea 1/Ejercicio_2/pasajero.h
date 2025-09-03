#ifndef PASAJERO_H
#define PASAJERO_H

#include <QString>

class Pasajero
{
public:
    Pasajero(const QString &nombre, const QString &dni);

    QString getNombre() const;
    QString getDni() const;

private:
    QString m_nombre;
    QString m_dni;
};

#endif // PASAJERO_H
