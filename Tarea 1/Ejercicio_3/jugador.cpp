#include "jugador.h"
#include "enemigo.h"
#include <QBrush>
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

Jugador::Jugador(QGraphicsItem *parent) : QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, 50, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);

    m_estaSaltando = false;
    m_velocidadVertical = 0;

    QTimer *timerGravedad = new QTimer(this);
    connect(timerGravedad, &QTimer::timeout, this, &Jugador::aplicarGravedad);
    timerGravedad->start(16);
}

void Jugador::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space && !m_estaSaltando) {
        m_estaSaltando = true;
        m_velocidadVertical = -20;
    }
}

void Jugador::aplicarGravedad()
{
    if (m_estaSaltando) {
        setPos(x(), y() + m_velocidadVertical);
        m_velocidadVertical += 1;
    }

    if (y() > 350) {
        setPos(x(), 350);
        m_velocidadVertical = 0;
        m_estaSaltando = false;
    }

    QList<QGraphicsItem *> itemsEnColision = collidingItems();
    for (QGraphicsItem* item : itemsEnColision) {
        Enemigo *enemigo = dynamic_cast<Enemigo*>(item);
        if (enemigo) {
            emit juegoTerminado();
            return;
        }
    }
}
