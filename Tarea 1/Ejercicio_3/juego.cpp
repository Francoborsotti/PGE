#include "juego.h"
#include "enemigo.h"
#include <QGraphicsLineItem>
#include <QTimer>
#include <QFont>
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>

Juego::Juego(QWidget *parent) : QGraphicsView(parent)
{
    m_escena = new QGraphicsScene();
    m_escena->setSceneRect(0, 0, 800, 450);
    setScene(m_escena);

    setFixedSize(800, 450);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    iniciarPartida();
}

void Juego::iniciarPartida()
{
    m_escena->clear();

    m_jugador = new Jugador();
    m_jugador->setPos(100, 350);
    m_escena->addItem(m_jugador);
    m_jugador->setFlag(QGraphicsItem::ItemIsFocusable);
    m_jugador->setFocus();

    connect(m_jugador, &Jugador::juegoTerminado, this, &Juego::gameOver);

    m_escena->addLine(0, 400, 800, 400);

    m_puntaje = 0;
    m_textoPuntaje = new QGraphicsTextItem();
    m_textoPuntaje->setPlainText("Puntaje: 0");
    m_textoPuntaje->setDefaultTextColor(Qt::darkGray);
    m_textoPuntaje->setFont(QFont("times", 16));
    m_textoPuntaje->setPos(10, 10);
    m_escena->addItem(m_textoPuntaje);

    m_timerPuntaje = new QTimer(this);
    connect(m_timerPuntaje, &QTimer::timeout, this, &Juego::incrementarPuntaje);
    m_timerPuntaje->start(100);

    m_timerEnemigos = new QTimer(this);
    connect(m_timerEnemigos, &QTimer::timeout, this, &Juego::crearEnemigo);
    m_timerEnemigos->start(2000);
}

void Juego::crearEnemigo()
{
    Enemigo *enemigo = new Enemigo();
    m_escena->addItem(enemigo);
}

void Juego::incrementarPuntaje()
{
    m_puntaje++;
    m_textoPuntaje->setPlainText("Puntaje: " + QString::number(m_puntaje));
}

void Juego::gameOver()
{
    m_timerEnemigos->stop();
    m_timerPuntaje->stop();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Juego Terminado");
    msgBox.setText("¡Has chocado! 💥\nTu puntaje final es: " + QString::number(m_puntaje));
    msgBox.setIcon(QMessageBox::Information);

    QAbstractButton *botonReiniciar = msgBox.addButton("Reiniciar", QMessageBox::ActionRole);
    QAbstractButton *botonSalir = msgBox.addButton("Salir", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == botonReiniciar) {
        reiniciarJuego();
    } else if (msgBox.clickedButton() == botonSalir) {
        QApplication::quit();
    }
}

void Juego::reiniciarJuego()
{
    iniciarPartida();
}
