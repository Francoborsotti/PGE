#ifndef DESARROLLADOR_H
#define DESARROLLADOR_H

#include "empleado.h"

class Desarrollador : public Empleado
{
public:
    Desarrollador(const QString &id, const QString &nombre, double salarioBase, const QString &lenguaje);

    void setHorasExtras(int horas);

    double calcularSalarioAnual() const override;
    void mostrarDetalles() const override;

private:
    QString m_lenguajePrincipal;
    int m_horasExtras;
    double m_tarifaHoraExtra;
};

#endif // DESARROLLADOR_H
