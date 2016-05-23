#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QProcess>
#include <QScrollBar>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "frasedialog.h"
#include "cryptoengine.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_firm_loadData_clicked();
    void on_pushButton_firm_privateKey_clicked();
    void on_pushButton_verif_loadData_clicked();
    void on_pushButton_verif_publicKey_clicked();
    void on_pushButton_verif_firma_clicked();
    void on_pushButton_firm_firmar_clicked();

private:
    Ui::MainWindow *ui;

    QFile* firmPrivateKey;
    QFile* firmData;

    QFile* verifPublicKey;
    QFile* verifData;
    QFile* verifFirma;
};

#endif // MAINWINDOW_H
