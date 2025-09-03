#include <QCoreApplication>
#include <QDebug>
#include "persona.h"
#include "estudiante.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Crear una instancia de Persona
    Persona persona1("Juan Perez", "30123456");
    qDebug() << "--- Información de la Persona ---";
    persona1.getInfo();
    qDebug() << "---------------------------------";

    // Crear una instancia de Estudiante
    Estudiante estudiante1("Ana Gomez", "40987654");

    // Registrar materias y calificaciones
    estudiante1.agregarMateria("Matemática", 8.5);
    estudiante1.agregarMateria("Programación", 9.0);
    estudiante1.agregarMateria("Física", 7.2);

    // Consultar información del estudiante
    estudiante1.getInfo();

    // Consultar una calificación específica
    qDebug() << "La calificación de Programación es:" << estudiante1.getCalificacion("Programación");

    return a.exec();
}
