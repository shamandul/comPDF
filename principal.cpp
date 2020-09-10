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

principal::principal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::principal)
{
    ui->setupUi(this);
    setWindowTitle("ComPdf");
   /* mListview = new QListView(this);
    mListview->setDragEnabled(true);
    mListview->setAcceptDrops(true);
    mListview->setDropIndicatorShown(true);
    mListview->setDefaultDropAction(Qt::MoveAction);*/
    ui->lista->setDragEnabled(true);
    ui->lista->setAcceptDrops(true);
    ui->lista->setDropIndicatorShown(true);
    ui->lista->setDefaultDropAction(Qt::MoveAction);
    setAcceptDrops(true);
    //ui->listView->setDragEnabled(true);
    mProcess = new QProcess(this);

    //connect (mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readyRead()));
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
    QString pathArchivo;
    QList<QUrl> urls;
    QList<QUrl>::Iterator i;
    urls = event->mimeData()->urls();

    for(i = urls.begin(); i != urls.end(); ++i)
    {
        //nombreArchivo = i->fileName();
        pathArchivo = i->path();
        ui->lista->addItem(pathArchivo);
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
    ui->tx_origen->setText("");
    ui->tx_destino->setText("");
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
    if(uriOrigen!="" && uriDestino!=""){
        const char *comando= "gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/ebook -dNOPAUSE -dQUIET -dBATCH -sOutputFile="+uriDestino+"/destino.pdf " + uriOrigen;
        mProcess->start("/bin/sh", QStringList()<< "-c" << comando);
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
