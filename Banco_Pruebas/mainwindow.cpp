#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fibonacci.h"
#include "imagenarojo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Fibonacci_clicked()
{
    /*Cuando se pincha sobre el boton Fibonacci, se abre su ventana de medición*/

    Fibonacci ventana;
    ventana.exec();

}

void MainWindow::on_ImagenARojo_clicked()
{
    /*Al hacer click sobre el boton imagen a rojo, se abre su correspondiente cuadro de dialogo*/

       ImagenARojo ventana;
       ventana.exec();
}
