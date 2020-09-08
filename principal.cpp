#include "principal.h"
#include "ui_principal.h"
#include <QFileDialog>
#include <QDir>
#include <QByteArray>
#include <stdio.h>
#include <stdlib.h>

QByteArray uriOrigen, uriDestino;

principal::principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::principal)
{
    ui->setupUi(this);
    setWindowTitle("ComPdf");
}

principal::~principal()
{
    delete ui;
}


void principal::on_btn_agregar_clicked()
{
    QString origen = QFileDialog::getOpenFileName(this, "Archivo a agregar", QDir::homePath());
    //QMessageBox::information(this, "Información", archivo);
    uriOrigen = origen.toLocal8Bit();
    //const char *comando= "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -dNOPAUSE -dQUIET -dBATCH -sOutputFile=destino.pdf " + uri;
    //system(comando);
    ui->tx_origen->setText(origen);

}

void principal::on_btn_eliminar_clicked()
{
    ui->tx_origen->setText("");
    ui->tx_destino->setText("");
    uriOrigen = "";
    uriDestino= "";
    ui->tx_mensaje->setText("Elige un Origen y un Destino.");
}

void principal::on_btn_comprimir_clicked()
{

    if(uriOrigen==""){
      ui->tx_mensaje->setText("Elige un Origen");
    }else if(uriDestino==""){
      ui->tx_mensaje->setText("Elige un Destino");
    }
    if(uriOrigen!="" && uriDestino!=""){
        const char *comando= "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -dNOPAUSE -dQUIET -dBATCH -sOutputFile="+uriDestino+"/destino.pdf " + uriOrigen;
        system(comando);
        ui->tx_mensaje->setText("Compresión terminada");
    }

}

void principal::on_btn_destino_clicked()
{
    QString destino = QFileDialog::getExistingDirectory(0, ("Selecciona un directorio"), QDir::currentPath());
    uriDestino= destino.toLocal8Bit();
    ui->tx_destino->setText(destino);
}
