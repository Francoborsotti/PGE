#include "inventario.h"

Inventario::Inventario(QObject *parent) : QObject(parent)
{
}

bool Inventario::agregarProducto(const Producto &producto)
{
    if (m_productos.contains(producto.getId())) {
        return false;
    }
    m_productos.insert(producto.getId(), producto);
    emit productoAgregado(producto);
    return true;
}

bool Inventario::eliminarProducto(const QString &id)
{
    if (!m_productos.contains(id)) {
        return false;
    }
    m_productos.remove(id);
    emit productoEliminado(id);
    return true;
}

bool Inventario::actualizarCantidad(const QString &id, int nuevaCantidad)
{
    if (!m_productos.contains(id)) {
        return false;
    }
    m_productos[id].setCantidad(nuevaCantidad);
    emit productoActualizado(m_productos[id]);
    return true;
}

QList<Producto> Inventario::getTodosLosProductos() const
{
    return m_productos.values();
}
