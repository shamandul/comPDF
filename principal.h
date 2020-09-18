#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
//#include <QListView>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class principal; }
QT_END_NAMESPACE
class QProcess;

class principal : public QWidget
{
    Q_OBJECT

protected:

    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);


public:
    principal(QWidget *parent = nullptr);
    ~principal();

    void unirPdf(QString comando);
    
private slots:
    void on_btn_agregar_clicked();
    void on_btn_eliminar_clicked();
    void on_btn_comprimir_clicked();
    void on_btn_destino_clicked();
    void readyRead();
    void finished();
    void onAdd();
    void onRemove();
    void on_btn_destino_unir_clicked();
    void on_bt_unir_clicked();
    void on_bt_unir_comprimir_clicked();

private:
    Ui::principal *ui;
    QProcess *mProcess;
    QAction* mActAdd = nullptr;
    QAction* mActRemove = nullptr;

};
#endif // PRINCIPAL_H
