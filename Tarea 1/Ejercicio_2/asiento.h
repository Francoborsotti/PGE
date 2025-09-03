#ifndef ASIENTO_H
#define ASIENTO_H

#include <QString>

class Asiento
{
public:
    Asiento(const QString &numero = "");

    QString getNumero() const;
    bool isDisponible() const;
    void ocupar();
    void liberar();

private:
    QString m_numero;
    bool m_disponible;
};

#endif // ASIENTO_H
