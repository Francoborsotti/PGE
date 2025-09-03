#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QString>

class Producto
{
public:
    Producto(const QString &id = "", const QString &nombre = "", int cantidad = 0, double precio = 0.0);

    QString getId() const;
    QString getNombre() const;
    int getCantidad() const;
    double getPrecio() const;


    void setNombre(const QString &nombre);
    void setCantidad(int cantidad);
    void setPrecio(double precio);

private:
    QString m_id;
    QString m_nombre;
    int m_cantidad;
    double m_precio;
};

#endif // PRODUCTO_H
