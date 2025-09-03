#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <QString>
#include <QDebug>

class Empleado
{
public:
    Empleado(const QString &id, const QString &nombre, double salarioBase);
    virtual ~Empleado() = default;

    virtual double calcularSalarioAnual() const = 0;
    virtual void mostrarDetalles() const = 0;

    QString getId() const;
    QString getNombre() const;

protected:
    QString m_id;
    QString m_nombre;
    double m_salarioBase;
};

#endif // EMPLEADO_H
