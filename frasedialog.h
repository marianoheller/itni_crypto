#ifndef FRASEDIALOG_H
#define FRASEDIALOG_H

#include <QDialog>
#include <QString>


namespace Ui {
class FraseDialog;
}

class FraseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FraseDialog(QWidget *parent = 0);
    ~FraseDialog();
    void SetFrase(QString frase);
    QString GetFrase();

private slots:
    void on_pushButton_aceptar_clicked();

    void on_pushButton_cancelar_clicked();

    void on_lineEdit_frase_textChanged(const QString &arg1);

private:
    Ui::FraseDialog *ui;
};

#endif // FRASEDIALOG_H
