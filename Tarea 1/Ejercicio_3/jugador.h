#ifndef JUGADOR_H
#define JUGADOR_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Jugador : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Jugador(QGraphicsItem *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

signals:
    void juegoTerminado();

public slots:
    void aplicarGravedad();

private:
    bool m_estaSaltando;
    qreal m_velocidadVertical;
};

#endif // JUGADOR_H
