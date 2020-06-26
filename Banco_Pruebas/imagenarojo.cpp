#include "imagenarojo.h"
#include "ui_imagenarojo.h"
#include "mainwindow.h"


ImagenARojo::ImagenARojo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImagenARojo)
{
    ui->setupUi(this);

        /* VALORES INICIALES AL CARGAR EL DIALOGO */

    ui->RutaImagen->setText("Ningun Directorio Seleccionado.");         /* Se settea el valor del qlabel que indica la ruta origen */
    ui->RutaImagen_2->setText("");           /* Se settea el valor del qlabel que indica la ruta destino */
    ui->Preview->hide();            /* Se oculta el boton preview */
    ui->PrevImagen->hide();        /* Se oculta el frame de la preview */
    semaforo = false;            /* Se inicializa el semaforo del slot del combo */

    contador = 0;
    media = 0.0;
    rutaCargar = "";
    rutaGuardar = "";
}

ImagenARojo::~ImagenARojo()
{
    delete ui;
}



void ImagenARojo::on_Reset_clicked()
{

        /*Elementos Graficos*/

    ui->T1TextField->clear();
    ui->T2TextField->clear();
    ui->T3TextField->clear();
    ui->T4TextField->clear();
    ui->T5TextField->clear();
    ui->RutaImagen->setText("Ningun Directorio Seleccionado.");
    ui->RutaImagen_2->setText("");
    ui->Preview->hide();
    ui->ImgCombo->clear();
    ui->MediaTextField->clear();

       /*Codigo*/

    listaImagenes.clear();
    contador = 0;
    media = 0.0;
    rutaCargar = "";
    rutaGuardar = "";

}

void ImagenARojo::on_Ejecutar_clicked()
{
    int tiempoTotal = 0;

    QElapsedTimer timer;

        /* Por si se trata de ejecutar sin directorio */

    if(rutaCargar == NULL || rutaGuardar == NULL)
    {

        QMessageBox alerta;
        alerta.setText("Por favor, debe seleccionar dos directorios\n\nUno del que cargar las Imágenes\nY otro en el que salvarlas\n");
        alerta.exec();
    }
    else
    {

            /* Se inicializa el cronometro */

        timer.start();


                        /* Recorrido de la lista imagen por imagen y pasandolas a rojo */

                    for(int i = 0; i < lista.size(); i++)
                    {


                        if(lista.at(i) != "." && lista.at(i) != "..")
                        {

                                 /* Se transforma la imagen a Rojo */

                            imagen = new QImage();

                            QString rutaImg = rutaCargar +"/"+ lista.at(i); /* Se concatena el nombre de la imagen de la entrylist */

                            imagen->load(rutaImg); /* Se carga la imagen fresca del directorio */

                            QColor changeColor;

                            for(int x = 0; x < imagen->width(); x++)
                            {
                                for(int y = 0; y < imagen->height(); y++)
                                {
                                    changeColor = QColor(imagen->pixel(x, y));

                                    imagen->setPixel(x, y, QColor(changeColor.red(), 0, 0).rgb());
                                }
                            }

                            QString rutaGuardarImg = rutaGuardar +"/"+ lista.at(i);

                            imagen->save(rutaGuardarImg);

                                    /* Se salva la imagen transformada en el array de imagenes para tener la preview de la ultima version de cada imagen a Rojo */

                            listaImagenes[i-2] = imagen; /* Sobreescrita en su misma posicion, es -2 porque estan . y .. delante en la lista entrylist */

                        }
                    }




            /* Se detiene el cronometro */

        tiempoTotal = timer.elapsed();


             /* Settea los tiempos en la interface */

        switch(this->contador)
        {
            case 0:
                ui->T1TextField->setText(QString::number(tiempoTotal) + "ms");
                break;
            case 1:
               ui->T2TextField->setText(QString::number(tiempoTotal) + "ms");
               break;
            case 2:
                ui->T3TextField->setText(QString::number(tiempoTotal) + "ms");
                break;
            case 3:
                ui->T4TextField->setText(QString::number(tiempoTotal) + "ms");
                break;
            case 4:
                ui->T5TextField->setText(QString::number(tiempoTotal) + "ms");
                break;
         }


            /* Calculo de la media */

        if(contador < 5)
        {

          media += tiempoTotal / 5.0;
          contador++;

        }
        if(contador == 5)
        {

           ui->MediaTextField->setText(QString::number(media));

        }


    }

}


void ImagenARojo::on_SelDir_clicked()
{

         /* Se abre el cuadro de dialogo que permite la seleccion de las imagenes */

    QFileDialog cuadroDeDialogo;

         /* Se Limpia la combo y la lista de Imagenes guardadas por si hubiera alguna de una carga anterior */

    ui->ImgCombo->clear();
    listaImagenes.clear();

         /* Se Pregunta de dónde se desean cargar */

    rutaCargar = cuadroDeDialogo.getExistingDirectory(this, tr("Cargar Imagen"), "", cuadroDeDialogo.ShowDirsOnly);


         /* Se Pregunta dónde se desean guardar */


    rutaGuardar = cuadroDeDialogo.getExistingDirectory(this, tr("Guardar Imagen"), "", cuadroDeDialogo.ShowDirsOnly);


        /* Comprobar si se ha dado en cancelar en ningun cuadro de dialogo */

    if(rutaCargar == NULL || rutaGuardar == NULL)
    {

        QMessageBox alerta;
        alerta.setText("Por favor, debe seleccionar dos directorios\n\nUno del que cargar las Imágenes\nY otro en el que salvarlas\n");
        alerta.exec();

    }
    else
    {

             /* Vamos a pasar todas las imagenes del directorio al vector de preview */
            /* Del directorio seleccionado obtenemos la lista de imagenes que hay */

        lista = QDir(rutaCargar).entryList();



            /* Se rellena el vector para la previsualizacion con las imagenes frescas */

        for(int i = 0; i < lista.size(); i++)
        {

                /* Se ignoran las entradas . y .. que nos crea la entrylist */

            if(lista.at(i) != "." && lista.at(i) != "..")
            {

                    imagen = new QImage();

                    QString rutaImg = rutaCargar +"/"+ lista.at(i);

                    imagen->load(rutaImg); /* Se carga la imagen */

                    listaImagenes.push_back(imagen); /* Se agrega al vector de preview */


                    ui->ImgCombo->addItem(lista.at(i)); /* Se pone en la combo el nombre de la imagen que me lo da la entrada de la lista */
            }
         }


            /* Finalmente Vamos a cargar los directorios y el boton de preview */

        ui->RutaImagen->setText("Dir. Entrada: " + rutaCargar);
        ui->RutaImagen_2->setText("Dir. Salida: " + rutaGuardar);
        ui->Preview->show();


    }

}


void ImagenARojo::on_Preview_clicked()
{
        /* Se ha solicitado la previsualizacion de la imagen segun el estado que tenga en ese momento */
        /* Se abre el semaforo del slot del combo */

    semaforo = true;

        /* Se muestra la combo 0 aquí porque si no se queda con la imagen que tenia antes de cambiarlas a rojo (no se actualiza) */

    ui->ImgCombo->setCurrentIndex(0);

        /* Se necesita la indireccion, es decir la propia imagen y no la direcion de memoria */

    QImage imagenCargada = *(listaImagenes[0]);

    imagenCargada = imagenCargada.scaledToWidth(ui->Imagen->width(), Qt::SmoothTransformation);

    ui->Imagen->setPixmap(QPixmap::fromImage(imagenCargada));

        /* Se muestra el panel con todo */

    ui->PrevImagen->show();

}


void ImagenARojo::on_Cerrar_clicked()
{
     /* Cierra la previsualizacion de la imagen, esto es, oculta el frame */

    semaforo = false;
    ui->PrevImagen->hide();

}


void ImagenARojo::on_ImgCombo_currentIndexChanged(int index)
{
    if(semaforo == true)
    {
            /* La combo va a representar la lista de imagenes que se han cargado */

        QImage imagenCargada = *(listaImagenes[index]);

            /* Ha cambiado el panel, escalo la imagen al label */

        imagenCargada = imagenCargada.scaledToWidth(ui->Imagen->width(), Qt::SmoothTransformation);

            /* Se ponge en un label el mapa de pixeles correspondiente a la imagen seleccionada en la combo*/

        ui->Imagen->setPixmap(QPixmap::fromImage(imagenCargada));

    }
}
