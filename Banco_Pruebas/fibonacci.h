#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <QDialog>
#include <QElapsedTimer>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <QMessageBox>

using namespace std;


namespace Ui {
class Fibonacci;
}

class Fibonacci : public QDialog
{
    Q_OBJECT

public:
    explicit Fibonacci(QWidget *parent = nullptr);
    ~Fibonacci();

    void escribirFichero(QString cadena);

    int seleccionarFicheroNumero();


private slots:
    //Método botón resetear
    void on_Reset_clicked();
    //Método botón ejecutar
    void on_Ejecutar_clicked();

private:
    Ui::Fibonacci *ui;

   //Variables
    int contador;
    int longitud;
    float media;
    QFile archivo;
};

#endif // FIBONACCI_H
