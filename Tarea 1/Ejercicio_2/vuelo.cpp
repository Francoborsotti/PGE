#include "vuelo.h"
#include <QDebug>


Vuelo::Vuelo(const QString &numeroVuelo)
    : m_numeroVuelo(numeroVuelo)
{
    for (int i = 1; i <= 2; i++)
    {
        m_asientos.insert(QString::number(i) + "A", Asiento(QString::number(i) + "A"));
        m_asientos.insert(QString::number(i) + "B", Asiento(QString::number(i) + "B"));
        m_asientos.insert(QString::number(i) + "C", Asiento(QString::number(i) + "C"));
    }
}

QString Vuelo::getNumeroVuelo() const
{
    return m_numeroVuelo;
}

void Vuelo::mostrarAsientosDisponibles() const
{
    QStringList disponibles;
    for(const Asiento &asiento : m_asientos)
    {
        if(asiento.isDisponible())
        {
            disponibles.append(asiento.getNumero());
        }
    }
    qDebug() << "asientos disponibles" << m_numeroVuelo << ":" << disponibles.join(", ");
}

Asiento* Vuelo::getAsiento(const QString &numeroAsiento)
{
    if(m_asientos.contains(numeroAsiento))
    {
        return &m_asientos[numeroAsiento];
    }
    return nullptr;
}
