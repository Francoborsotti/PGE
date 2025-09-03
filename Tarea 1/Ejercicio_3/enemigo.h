#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QObject>
#include <QGraphicsRectItem>

class Enemigo : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Enemigo(QGraphicsItem *parent = nullptr);

public slots:
    void mover();
};

#endif // ENEMIGO_H
