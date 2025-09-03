#include "producto.h"

Producto::Producto(const QString &id, const QString &nombre, int cantidad, double precio)
    : m_id(id), m_nombre(nombre), m_cantidad(cantidad), m_precio(precio)
{
}

QString Producto::getId() const
{
    return m_id;
}

QString Producto::getNombre() const
{
    return m_nombre;
}

int Producto::getCantidad() const
{
    return m_cantidad;
}

double Producto::getPrecio() const
{
    return m_precio;
}

void Producto::setNombre(const QString &nombre)
{
    m_nombre = nombre;
}

void Producto::setCantidad(int cantidad)
{
    m_cantidad = cantidad;
}

void Producto::setPrecio(double precio)
{
    m_precio = precio;
}
