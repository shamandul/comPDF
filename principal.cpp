#include "principal.h"
#include "ui_principal.h"
#include <QFileDialog>
#include <QDir>
#include <QByteArray>
#include <stdio.h>
#include <stdlib.h>
#include <QProcess>
#include <QDragEnterEvent>
#include <QMimeData>


QByteArray uriOrigen, uriDestino;
QString pathArchivo;

principal::principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::principal)
{
    ui->setupUi(this);
    setWindowTitle("ComPdf");
    ui->lista->setDragEnabled(true);
    ui->lista->setAcceptDrops(true);
    ui->lista->setDropIndicatorShown(true);
    ui->lista->setDefaultDropAction(Qt::MoveAction);
    setAcceptDrops(true);
    mProcess = new QProcess(this);

    connect (mProcess, SIGNAL(started()), this, SLOT(readyRead()));
    connect (mProcess, SIGNAL(finished (int, QProcess::ExitStatus)), this, SLOT(finished()));

}

principal::~principal()
{
    delete ui;
}
/**
 * Método que nos permite controlar eventos cuando
 * algo entra en la aplicación
 * @brief principal::dragEnterEvent
 * @param event
 */
void principal::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}
/**
 * Método que nos permite controlar eventos cuando
 * sacamos algo de la aplicación
 * @brief principal::dragLeaveEvent
 * @param event
 */
void principal::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}
/**
 * Método que nos permite controlar eventos cuando
 * movemos algo dentro de la aplicación
 * @brief principal::dragMoveEvent
 * @param event
 */
void principal::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

/**
 * Método que nos permite controlar eventos y
 * nos permite arrastrar archivos
 * desde fuera de la aplicación
 * @brief principal::dropEvent
 * @param event
 */
void principal::dropEvent(QDropEvent *event)
{
    //QString pathArchivo;
    QList<QUrl> urls;
    QList<QUrl>::Iterator i;
    urls = event->mimeData()->urls();

    for(i = urls.begin(); i != urls.end(); ++i)
    {
       int lastPoint = i->fileName().lastIndexOf(".");
       QString extension = i->fileName().mid(lastPoint);
       if(extension==".pdf" || extension ==".PDF"){
            pathArchivo = i->path();
            ui->lista->addItem(pathArchivo);
        }


    }
}
/**
 * Método que nos permite controlar eventos on click
 * del botón agregar y nos permite agregar el archivo pdf
 * para el origen
 * @brief principal::on_btn_agregar_clicked
 */
void principal::on_btn_agregar_clicked()
{
    QString origen = QFileDialog::getOpenFileName(this, "Archivo a agregar", QDir::homePath());
    uriOrigen = origen.toLocal8Bit();
    ui->tx_origen->setText(origen);

}
/**
 * Método que nos permite controlar eventos on click
 * del botón eliminar, nos permite eliminar los
 * todos valores de la aplicación
 * @brief principal::on_btn_eliminar_clicked
 */
void principal::on_btn_eliminar_clicked()
{
    //TODO: Limpiar lista y destino
    ui->tx_origen->setText("");
    ui->tx_destino->setText("");
    ui->tx_destino_unir->setText("");
    ui->lista->clear();
    uriOrigen = "";
    uriDestino= "";
    ui->tx_mensaje->setText("Elige un Origen y un Destino.");
}
/**
 * Método que nos permite controlar eventos on click
 * del botón comprimir y nos permite comprimir el archivo
 * origen y lo guarda en el archivo destino
 * @brief principal::on_btn_comprimir_clicked
 */
void principal::on_btn_comprimir_clicked()
{
    if(uriOrigen==""){
      ui->tx_mensaje->setText("Elige un Origen");
    }else if(uriDestino==""){
      ui->tx_mensaje->setText("Elige un Destino");
    }
    /*if(uriOrigen!="" && uriDestino!=""){
        const char *comando= "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -dNOPAUSE -dQUIET -dBATCH -sOutputFile="+uriDestino+"/destino.pdf " + uriOrigen;
        mProcess->start("/bin/sh", QStringList()<< "-c" << comando);
    }*/
    if(uriOrigen!="" && uriDestino!=""){
        QString comando, programa;
        if(QSysInfo::productType() == "windows"){

            comando="C:/gs/gswin64c.exe -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -dNOPAUSE -dQUIET -dBATCH -sOutputFile="+uriDestino+"/destino.pdf " + uriOrigen;
        }
        else{
           comando="gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -dNOPAUSE -dQUIET -dBATCH -sOutputFile="+uriDestino+"/destino.pdf " + uriOrigen;
        }
        mProcess->start(getProcess(), QStringList()<< "-c" << comando);
     }
}
/**
 * Método que nos permite saber cuando ha terminado
 * el proceso de la compresión
 * @brief principal::finished
 */
void principal::finished()
{
  ui->tx_mensaje->setText("Compresión terminada");
}
/**
 * Método que nos permite saber cuando ha empezado
 * el proceso de la compresión
 * @brief principal::readyRead
 */
void principal::readyRead()
{
  /*if (!mProcess)
    return;*/
  // Para este comando no se utiliza ya que no devuelve ningun valor
  //QString str = mProcess->readAllStandardOutput();
  ui->tx_mensaje->setText("Comienza la compresión");


}
/**
 * Método que nos permite controlar eventos on click
 * del botón destino y nos permite agregar la ruta
 * del archivo de destino
 * @brief principal::on_btn_destino_clicked
 */
void principal::on_btn_destino_clicked()
{
    QString destino = QFileDialog::getExistingDirectory(0, ("Selecciona un directorio"), QDir::currentPath());
    uriDestino= destino.toLocal8Bit();
    ui->tx_destino->setText(destino);
}
/**
 * Método que nos permite añadir archivos a
 * la lita
 * @brief principal::onAdd
 */
void principal::onAdd()
{

}
/**
 * Método que nos permite eliminar archivos de la lista
 * @brief principal::onRemove
 */
void principal::onRemove()
{

}
/**
 * Método que nos permite controlar el evento on click
 * del botón destino_unir y nos permite elegir la carpeta
 * de destino
 * @brief principal::on_btn_destino_unir_clicked
 */
void principal::on_btn_destino_unir_clicked()
{
    QString destino = QFileDialog::getExistingDirectory(0, ("Selecciona un directorio"), QDir::currentPath());
    uriDestino= destino.toLocal8Bit();
    ui->tx_destino_unir->setText(destino);
}
/**
 * Método que nos permite controlar el evento on click
 * del botón unir que nos permite unir varios PDF en uno solo
 * @brief principal::on_bt_unir_clicked
 */
void principal::on_bt_unir_clicked()
{

    QString comando;
    //comando="gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=";
    if(QSysInfo::productType() == "windows"){
        comando="C:/gs/gswin64c.exe -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=";
    }
    else{
       comando="gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=";
    }
    unirPdf(comando);
}
/**
 * Método que nos permite controlar el evento on click
 * del botón unir y comprimir que nos permite  unir varios
 * PDF en uno solo y comprimirlo
 * @brief principal::on_bt_unir_comprimir_clicked
 */
void principal::on_bt_unir_comprimir_clicked()
{
    QString comando;
    if(QSysInfo::productType() == "windows"){
        comando="c:/gs/gswin64c.exe -dBATCH -dNOPAUSE -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -q -sDEVICE=pdfwrite -sOutputFile=";
    }
    else{
       comando="gs -dBATCH -dNOPAUSE -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -q -sDEVICE=pdfwrite -sOutputFile=";
    }
    unirPdf(comando);
}
/**
 * Método que nos permite unir PDF
 * @brief principal::unirPdf
 * @param comando
 * @param archivos
 */
void principal::unirPdf(QString comando)
{
    QString archivos;
    if(uriDestino=="")
    {
        char *home;
        if(QSysInfo::productType() == "window"){
             home=getenv("USERS");
            //home=_dupenv_s("Users");
         }else {
             home = getenv("HOME");
         }
        uriDestino=home;
    }
    ui->tx_destino_unir->setText(uriDestino);
    comando += uriDestino + "/salida.pdf";

    for(int i = 0; i != ui->lista->count(); ++i)
    {
      archivos += ui->lista->item(i)->text() + " ";
    }
    comando += " " + archivos;
    mProcess->start(getProcess(), QStringList()<< "-c" << comando);
}

QString principal::getProcess()
{
    if(QSysInfo::productType() == "windows") return "cmd";
    if(QSysInfo::productType() == "osx") return "/bin/zsh";

    return "bash";
}
