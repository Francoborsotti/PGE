#include "ventanainventario.h"
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>

VentanaInventario::VentanaInventario(QWidget *parent)
    : QWidget(parent)
{
    m_inventario = new Inventario(this);

    setupUI();

    connect(m_inventario, &Inventario::productoAgregado, this, &VentanaInventario::agregarFila);
    connect(m_inventario, &Inventario::productoEliminado, this, &VentanaInventario::eliminarFila);
    connect(m_inventario, &Inventario::productoActualizado, this, &VentanaInventario::actualizarFila);

    m_inventario->agregarProducto(Producto("SKU001", "Laptop", 10, 1500.00));
    m_inventario->agregarProducto(Producto("SKU002", "Mouse", 50, 25.50));
}

VentanaInventario::~VentanaInventario() {}

void VentanaInventario::setupUI()
{
    setWindowTitle("Gestión de Inventario");
    resize(600, 400);

    m_tablaProductos = new QTableWidget(0, 4);
    m_tablaProductos->setHorizontalHeaderLabels({"ID", "Nombre", "Cantidad", "Precio"});
    m_tablaProductos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tablaProductos->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tablaProductos->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_idEdit = new QLineEdit;
    m_nombreEdit = new QLineEdit;
    m_cantidadEdit = new QLineEdit;
    m_precioEdit = new QLineEdit;

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("ID (SKU):", m_idEdit);
    formLayout->addRow("Nombre:", m_nombreEdit);
    formLayout->addRow("Cantidad:", m_cantidadEdit);
    formLayout->addRow("Precio:", m_precioEdit);

    m_btnAgregar = new QPushButton("Agregar");
    m_btnEliminar = new QPushButton("Eliminar Seleccionado");
    m_btnActualizar = new QPushButton("Actualizar Cantidad");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_btnAgregar);
    buttonLayout->addWidget(m_btnEliminar);
    buttonLayout->addWidget(m_btnActualizar);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_tablaProductos);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    connect(m_btnAgregar, &QPushButton::clicked, this, &VentanaInventario::onAgregarProducto);
    connect(m_btnEliminar, &QPushButton::clicked, this, &VentanaInventario::onEliminarProducto);
    connect(m_btnActualizar, &QPushButton::clicked, this, &VentanaInventario::onActualizarCantidad);
}

void VentanaInventario::onAgregarProducto()
{
    Producto p(m_idEdit->text(), m_nombreEdit->text(), m_cantidadEdit->text().toInt(), m_precioEdit->text().toDouble());
    if (!m_inventario->agregarProducto(p)) {
        QMessageBox::warning(this, "Error", "No se pudo agregar el producto. El ID ya podría existir.");
    }
}

void VentanaInventario::onEliminarProducto()
{
    int fila = m_tablaProductos->currentRow();
    if (fila < 0) return;
    QString id = m_tablaProductos->item(fila, 0)->text();
    m_inventario->eliminarProducto(id);
}

void VentanaInventario::onActualizarCantidad()
{
    int fila = m_tablaProductos->currentRow();
    if (fila < 0) return;
    QString id = m_tablaProductos->item(fila, 0)->text();
    int nuevaCantidad = m_cantidadEdit->text().toInt();
    m_inventario->actualizarCantidad(id, nuevaCantidad);
}

void VentanaInventario::agregarFila(const Producto &producto)
{
    int fila = m_tablaProductos->rowCount();
    m_tablaProductos->insertRow(fila);
    m_tablaProductos->setItem(fila, 0, new QTableWidgetItem(producto.getId()));
    m_tablaProductos->setItem(fila, 1, new QTableWidgetItem(producto.getNombre()));
    m_tablaProductos->setItem(fila, 2, new QTableWidgetItem(QString::number(producto.getCantidad())));
    m_tablaProductos->setItem(fila, 3, new QTableWidgetItem(QString::number(producto.getPrecio())));
}

void VentanaInventario::eliminarFila(const QString &id)
{
    int fila = encontrarFilaPorId(id);
    if (fila >= 0) {
        m_tablaProductos->removeRow(fila);
    }
}

void VentanaInventario::actualizarFila(const Producto &producto)
{
    int fila = encontrarFilaPorId(producto.getId());
    if (fila >= 0) {
        m_tablaProductos->item(fila, 2)->setText(QString::number(producto.getCantidad()));
    }
}

int VentanaInventario::encontrarFilaPorId(const QString &id)
{
    for (int i = 0; i < m_tablaProductos->rowCount(); ++i) {
        if (m_tablaProductos->item(i, 0)->text() == id) {
            return i;
        }
    }
    return -1;
}
