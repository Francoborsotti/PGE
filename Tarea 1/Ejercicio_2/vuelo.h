#ifndef VUELO_H
#define VUELO_H

#include "asiento.h"
#include <QString>
#include <QMap>

class Vuelo
{
public:
    Vuelo(const QString &numeroVuelo);

    QString getNumeroVuelo() const;
    void mostrarAsientosDisponibles() const;
    Asiento* getAsiento(const QString & numeroAsiento);

private:
    QString m_numeroVuelo;
    QMap<QString, Asiento> m_asientos;
};

#endif // VUELO_H
