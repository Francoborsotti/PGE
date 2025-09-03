#ifndef GERENTE_H
#define GERENTE_H

#include "empleado.h"

class Gerente : public Empleado
{
public:
    Gerente(const QString &id, const QString &nombre, double salarioBase, double bonoGestion);

    double calcularSalarioAnual() const override;
    void mostrarDetalles() const override;

private:
    double m_bonoGestion;
};

#endif // GERENTE_H
