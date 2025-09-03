#include "enemigo.h"
#include <QBrush>
#include <QTimer>
#include <QGraphicsScene>

Enemigo::Enemigo(QGraphicsItem *parent) : QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, 50, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    setPos(800, 350);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemigo::mover);
    timer->start(16); // ~60 FPS
}

void Enemigo::mover()
{
    setPos(x() - 5, y());

    if (x() + rect().width() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
