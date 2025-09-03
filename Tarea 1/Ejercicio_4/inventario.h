#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <QObject>
#include <QMap>
#include "producto.h"

class Inventario : public QObject
{
    Q_OBJECT

public:
    explicit Inventario(QObject *parent = nullptr);

    bool agregarProducto(const Producto &producto);
    bool eliminarProducto(const QString &id);
    bool actualizarCantidad(const QString &id, int nuevaCantidad);
    QList<Producto> getTodosLosProductos() const;

signals:
    void productoAgregado(const Producto &producto);
    void productoEliminado(const QString &id);
    void productoActualizado(const Producto &producto);

private:
    QMap<QString, Producto> m_productos;
};

#endif // INVENTARIO_H
