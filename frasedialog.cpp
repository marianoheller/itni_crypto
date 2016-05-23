#include "frasedialog.h"
#include "ui_frasedialog.h"


FraseDialog::FraseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FraseDialog)
{
    ui->setupUi(this);
    ui->pushButton_aceptar->setDisabled(true);
    //ui->pushButton_aceptar->setEchoMode(QLineEdit::Password);
    ui->lineEdit_frase->setMinimumWidth(300);
}

FraseDialog::~FraseDialog()
{
    delete ui;
}

void FraseDialog::on_pushButton_aceptar_clicked()
{
    this->accept();
}

void FraseDialog::on_pushButton_cancelar_clicked()
{
    this->close();
}

void FraseDialog::on_lineEdit_frase_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
        ui->pushButton_aceptar->setDisabled(true);
    else
        ui->pushButton_aceptar->setEnabled(true);
}

void FraseDialog::SetFrase(QString frase) {
    ui->lineEdit_frase->setText(frase);
}

QString FraseDialog::GetFrase() {
    return ui->lineEdit_frase->text();
}
