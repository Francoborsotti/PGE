#ifndef VENTANAINVENTARIO_H
#define VENTANAINVENTARIO_H

#include <QWidget>
#include "inventario.h"

class QTableWidget;
class QLineEdit;
class QPushButton;

class VentanaInventario : public QWidget
{
    Q_OBJECT

public:
    VentanaInventario(QWidget *parent = nullptr);
    ~VentanaInventario();

private slots:
    void onAgregarProducto();
    void onEliminarProducto();
    void onActualizarCantidad();

    void agregarFila(const Producto &producto);
    void eliminarFila(const QString &id);
    void actualizarFila(const Producto &producto);

private:
    void setupUI();
    int encontrarFilaPorId(const QString &id);

    Inventario *m_inventario;

    QTableWidget *m_tablaProductos;
    QLineEdit *m_idEdit;
    QLineEdit *m_nombreEdit;
    QLineEdit *m_cantidadEdit;
    QLineEdit *m_precioEdit;
    QPushButton *m_btnAgregar;
    QPushButton *m_btnEliminar;
    QPushButton *m_btnActualizar;
};

#endif // VENTANAINVENTARIO_H
