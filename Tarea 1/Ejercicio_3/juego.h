#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "jugador.h"

class Juego : public QGraphicsView
{
    Q_OBJECT
public:
    Juego(QWidget *parent = nullptr);

private slots:
    void crearEnemigo();
    void incrementarPuntaje();
    void gameOver();

private:
    void iniciarPartida();
    void reiniciarJuego();

    QGraphicsScene *m_escena;
    Jugador *m_jugador;
    QTimer *m_timerEnemigos;
    QTimer *m_timerPuntaje;
    QGraphicsTextItem *m_textoPuntaje;
    int m_puntaje;
};

#endif // JUEGO_H
