#ifndef IMAGENAROJO_H
#define IMAGENAROJO_H

#include <QFileDialog>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QImage>
#include<iostream>
#include <QDir>
#include <vector>

using namespace std;


namespace Ui {
class ImagenARojo;
}

class ImagenARojo : public QDialog
{
    Q_OBJECT

public:
    explicit ImagenARojo(QWidget *parent = nullptr);
    ~ImagenARojo();



private slots:


    void on_Reset_clicked();

    void on_Ejecutar_clicked();

    void on_SelDir_clicked();

    void on_Preview_clicked();

    void on_Cerrar_clicked();

    void on_ImgCombo_currentIndexChanged(int index);

private:
    Ui::ImagenARojo *ui;

    QString rutaCargar;
    QString rutaGuardar;
    int contador;
    float media;
    QImage * imagen;
    //Almacenamos las imagenes segun el estado en cada momento para mostrarlas
    vector<QImage *> listaImagenes;
    //Lista con los archivos que tenga el directorio
    QStringList lista;
    //Evitar que esté escuchando continuamente el slot del combo
    bool semaforo;



};

#endif // IMAGENAROJO_H
