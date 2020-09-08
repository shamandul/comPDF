#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class principal; }
QT_END_NAMESPACE

class principal : public QWidget
{
    Q_OBJECT

public:
    principal(QWidget *parent = nullptr);
    ~principal();

private slots:
    void on_btn_agregar_clicked();
    void on_btn_eliminar_clicked();
    void on_btn_comprimir_clicked();
    void on_btn_destino_clicked();

private:
    Ui::principal *ui;
};
#endif // PRINCIPAL_H
