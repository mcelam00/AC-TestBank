#include "fibonacci.h"
#include "ui_fibonacci.h"


Fibonacci::Fibonacci(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fibonacci)
{
    ui->setupUi(this);
    contador = 0;
    media = 0.0;
}

Fibonacci::~Fibonacci()
{
    delete ui;
}

void Fibonacci::on_Reset_clicked()
{
    media = 0.0;
    contador = 0;

    // RESETEA TODOS LOS TIEMPOS PUESTOS ANTERIORMENTE
    ui->T1TextField->clear();
    ui->T2TextField->clear();
    ui->T3TextField->clear();
    ui->T4TextField->clear();
    ui->T5TextField->clear();

    // Y LA MEDIA
    ui->TMediaTextField->clear();
}

void Fibonacci::on_Ejecutar_clicked()
{
    QElapsedTimer contadorTiempo;
    int tiempo = 0;
   archivo.setFileName("fibonacci.txt");

    longitud = seleccionarFicheroNumero();


   //EMPEZAR CONTAR EL TIEMPO
    contadorTiempo.start();

    //ABRIR EL ARCHIVO
    archivo.open(QIODevice::WriteOnly);

    unsigned long int num=1;
    unsigned long int anterior=0;
    unsigned long int auxiliar;

    this->escribirFichero(QString::number(anterior));
    this->escribirFichero(QString::number(num));

    //BUCLE RECORRE PRIMEROS 1000 NUMEROS
    for(int i = 0; i < longitud-2; i++)
    {
        auxiliar=num;

        num=num+anterior;

        anterior=auxiliar;

        //cout << num << endl;
        escribirFichero(QString::number(num));
    }

    //CERRAR ARCHIVO
    archivo.close();

    tiempo = contadorTiempo.elapsed();

    //HACER EL SWITCH
    switch(contador)
    {
        case 0:
            ui->T1TextField->setText(QString::number(tiempo) + " ms");
            break;
        case 1:
            ui->T2TextField->setText(QString::number(tiempo) + " ms");
            break;
        case 2:
            ui->T3TextField->setText(QString::number(tiempo) + " ms");
            break;
        case 3:
            ui->T4TextField->setText(QString::number(tiempo) + " ms");
            break;
        case 4:
            ui->T5TextField->setText(QString::number(tiempo) + " ms");
            break;
    }

    //SI EL CONTADOR YA ES 5, ESCRIBES LA MEDIA EN EL LABEL
    if(contador < 5){
        contador++;
        media = media + tiempo / 5.0;
    }
    if (contador == 5){
        ui->TMediaTextField->setText(QString::number(media));
    }


}


void Fibonacci::escribirFichero(QString cadena)
{
    QTextStream escritor(&archivo);
    escritor << cadena;
    escritor << "\n";
}

int Fibonacci::seleccionarFicheroNumero()
{
    int num = 1000;
       int numLeido = 0;
       fstream ficheroNumero("NumeroFibonacci.txt");
       ficheroNumero >> numLeido;
       if((numLeido == 0 || numLeido <= 0) && contador == 0)
       {
           QMessageBox mensaje;
           mensaje.setText("El archivo no contiene un número correcto, se utiliza 1000 como valor por defecto");
           mensaje.exec();
       }
       else
       {
           num = numLeido;
       }

       return num;

}



