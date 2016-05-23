#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    firmData = new QFile(this);
    firmPrivateKey = new QFile(this);
    verifData = new QFile(this);
    verifFirma = new QFile(this);
    verifPublicKey = new QFile(this);

    ui->pushButton_firm_firmar->setDisabled(true);
    ui->pushButton_firm_firmar->setToolTip("Debe cargar la clave privada Y el archivo a firmar");
    ui->pushButton_firm_loadData->setToolTip("Cargar el archivo a firmar");
    ui->pushButton_firm_privateKey->setToolTip("Cargar la clave privada");

    ui->pushButton_verif_verificar->setDisabled(true);
    ui->pushButton_verif_verificar->setToolTip("Debe cargar TODOS los archivos necesarios para poder verificar");
    ui->pushButton_verif_firma->setToolTip("Cargar el archivo de firma");
    ui->pushButton_verif_publicKey->setToolTip("Cargar clave publica");
    ui->pushButton_verif_loadData->setToolTip("Cargar archivo a verificar");

    ui->tabWidget->setCurrentIndex(0);

    this->setWindowIcon( QIcon(":/new/prefix1/icons/key.png"));
    this->setWindowTitle("Crypto - INTI");
    ui->plainTextEdit_log->appendHtml("<html><b>Crypto - INTI</b></html>");
    ui->plainTextEdit_log->appendHtml("<html><font color=\"green\"><b>Listo.</b></font></html>");

}

MainWindow::~MainWindow()
{
    verifData->close();
    verifFirma->close();
    verifPublicKey->close();

    firmData->close();
    firmPrivateKey->close();

    delete ui;
}

void MainWindow::on_pushButton_firm_loadData_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo a firmar"));
    if (!fileName.isEmpty() )
    {
        if (firmData->isOpen())
            firmData->close();
        firmData->setFileName(fileName);
        if(!firmData->open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Error al leer el archivo", firmData->errorString());
        }
        ui->label_firm_loadData->setText(QFileInfo(fileName).fileName());
        QString msj = "Firma - Cargado archivo a firmar.";
        ui->plainTextEdit_log->appendPlainText(msj);
        ui->plainTextEdit_log->verticalScrollBar()->setValue( ui->plainTextEdit_log->verticalScrollBar()->maximum() );
        if ( firmPrivateKey->isOpen() && firmData->isOpen() ) {
            ui->pushButton_firm_firmar->setEnabled(true);
            ui->pushButton_firm_firmar->setToolTip("Realizar la firma del archivo");
            ui->plainTextEdit_log->appendPlainText("Listo para firmar.");
        }
        else {
            ui->pushButton_firm_firmar->setDisabled(true);
            ui->pushButton_firm_firmar->setToolTip("Debe cargar la clave privada Y el archivo a firmar");
        }
    }

}

void MainWindow::on_pushButton_firm_privateKey_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir clave privada"));
    if (!fileName.isEmpty() )
    {
        if (firmPrivateKey->isOpen())
            firmPrivateKey->close();
        firmPrivateKey->setFileName(fileName);
        if(!firmPrivateKey->open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Error al leer el archivo", firmPrivateKey->errorString());
        }
        ui->label_firm_privateKey->setText(QFileInfo(fileName).fileName());
        //    QTextStream in(firmPrivateKey);
        //    while(!in.atEnd()) {
        //        QString line = in.readLine();
        //        ui->plainTextEdit_log->appendPlainText(line);
        //        ui->plainTextEdit_log->verticalScrollBar()->setValue( ui->plainTextEdit_log->verticalScrollBar()->maximum() );
        //    }
        QString msj = "Firma - Cargada clave privada.";
        ui->plainTextEdit_log->appendPlainText(msj);
        ui->plainTextEdit_log->verticalScrollBar()->setValue( ui->plainTextEdit_log->verticalScrollBar()->maximum() );
        if ( firmPrivateKey->isOpen() && firmData->isOpen() ) {
            ui->pushButton_firm_firmar->setEnabled(true);
            ui->pushButton_firm_firmar->setToolTip("Realizar la firma del archivo");
            ui->plainTextEdit_log->appendPlainText("Firma - Listo para firmar.");
        }
        else {
            ui->pushButton_firm_firmar->setDisabled(true);
            ui->pushButton_firm_firmar->setToolTip("Debe cargar la clave privada Y el archivo a firmar");
        }
    }
}

void MainWindow::on_pushButton_verif_loadData_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo a verificar"));
    if (!fileName.isEmpty() )
    {
        if (verifData->isOpen())
            verifData->close();
        verifData->setFileName(fileName);
        if(!verifData->open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Error al leer el archivo", verifData->errorString());
        }
        ui->label_verif_loadData->setText(QFileInfo(fileName).fileName());

        QString msj = "Verificacion - Cargado archivo a verificar.";
        ui->plainTextEdit_log->appendPlainText(msj);
        ui->plainTextEdit_log->verticalScrollBar()->setValue( ui->plainTextEdit_log->verticalScrollBar()->maximum() );
        if ( verifData->isOpen() && verifFirma->isOpen() && verifPublicKey->isOpen() ) {
            ui->pushButton_verif_verificar->setEnabled(true);
            ui->pushButton_verif_verificar->setToolTip("Realizar la verificacion del archivo");
            ui->plainTextEdit_log->appendPlainText("Listo para verificar.");
        }
        else {
            ui->pushButton_verif_verificar->setDisabled(true);
            ui->pushButton_verif_verificar->setToolTip("Debe cargar TODOS los archivos necesarios para poder verificar");
        }
    }
}

void MainWindow::on_pushButton_verif_publicKey_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir clave publica"));
    if (!fileName.isEmpty() )
    {
        if (verifPublicKey->isOpen())
            verifPublicKey->close();
        verifPublicKey->setFileName(fileName);
        if(!verifPublicKey->open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Error al leer el archivo", verifPublicKey->errorString());
        }
        ui->label_verif_publicKey->setText(QFileInfo(fileName).fileName());

        QString msj = "Verificacion - Cargada clave publica.";
        ui->plainTextEdit_log->appendPlainText(msj);
        ui->plainTextEdit_log->verticalScrollBar()->setValue( ui->plainTextEdit_log->verticalScrollBar()->maximum() );

        if ( verifData->isOpen() && verifFirma->isOpen() && verifPublicKey->isOpen() ) {
            ui->pushButton_verif_verificar->setEnabled(true);
            ui->pushButton_verif_verificar->setToolTip("Realizar la verificacion del archivo");
            ui->plainTextEdit_log->appendPlainText("Listo para verificar.");
        }
        else {
            ui->pushButton_verif_verificar->setDisabled(true);
            ui->pushButton_verif_verificar->setToolTip("Debe cargar TODOS los archivos necesarios para poder verificar");
        }
    }
}

void MainWindow::on_pushButton_verif_firma_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir firma"));
    if (!fileName.isEmpty() )
    {
        if (verifFirma->isOpen())
            verifFirma->close();
        verifFirma->setFileName(fileName);
        if(!verifFirma->open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Error al leer el archivo", verifFirma->errorString());
        }
        ui->label_verif_firma->setText(QFileInfo(fileName).fileName());

        QString msj = "Verificacion - Cargada firma.";
        ui->plainTextEdit_log->appendPlainText(msj);
        ui->plainTextEdit_log->verticalScrollBar()->setValue( ui->plainTextEdit_log->verticalScrollBar()->maximum() );

        if ( verifData->isOpen() && verifFirma->isOpen() && verifPublicKey->isOpen() ) {
            ui->pushButton_verif_verificar->setEnabled(true);
            ui->pushButton_verif_verificar->setToolTip("Realizar la verificacion del archivo");
            ui->plainTextEdit_log->appendPlainText("Listo para verificar.");
        }
        else {
            ui->pushButton_verif_verificar->setDisabled(true);
            ui->pushButton_verif_verificar->setToolTip("Debe cargar TODOS los archivos necesarios para poder verificar");
        }
    }

}



void MainWindow::on_pushButton_firm_firmar_clicked()
{
    FraseDialog *dialog = new FraseDialog(this);
    if ( dialog->exec() == QDialog::Accepted )
    {
        QString dir = QFileDialog::getExistingDirectory(this,
                                                        tr("Elegir carpeta"),
                                                        QString(),
                                                        QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        if ( !dir.isEmpty())
        {
            if ( !firmData->isOpen() && !firmPrivateKey->isOpen() ) {
                ui->plainTextEdit_log->appendPlainText("Error de firmado. Archivos no se pudieron abrir");
                return;
            }
            firmData->close();
            firmPrivateKey->close();
            QString commandParams = "cryptoEngine -f " + firmPrivateKey->fileName() + " -i " + firmData->fileName();
            if ( !dialog->GetFrase().isEmpty() )
                commandParams += " -e " + dialog->GetFrase();
            if ( !dir.isEmpty() ) {
                if ( dir.at(dir.size()-1) != QChar('/') )
                    dir.append("/");
                commandParams += " -d " + dir;
            }
            QStringList commandParamsList = commandParams.split(" ");
            char **argv = new char*[commandParamsList.size()];
            int argc = commandParamsList.size();
            qDebug("Input:");
            qDebug(QString::number(argc).toStdString().c_str());
            for ( int i=0 ; i<commandParamsList.size() ; i++ ) {
                argv[i] = new char [strlen(commandParamsList.at(i).toStdString().c_str()) + 1];
                strcpy(argv[i], commandParamsList.at(i).toStdString().c_str());
                qDebug("%d) %s",i,argv[i]);
            }
            qDebug("=========================================");
            CryptoEngine* engine = new CryptoEngine( argc , argv );
            if ( engine->GetCryptoEngineStatus() == OK) {
                ui->plainTextEdit_log->appendPlainText("Firmando el archivo " + QFileInfo(firmData->fileName()).fileName() + " ...");
                ui->plainTextEdit_log->appendHtml("<html><font color=\"green\"><b>Firmado correctamente.</b></font></html>");
            }
            else {
                ui->plainTextEdit_log->appendHtml("<html><font color=\"red\"><b>Error de firmado.</b></font></html>");
                if (!engine->GetCryptoEngineStatusString().isEmpty())
                    ui->plainTextEdit_log->appendHtml("<html><font color=\"red\">"+engine->GetCryptoEngineStatusString()+"</font></html>");
            }

            //ReOpen stuff
            if(!firmPrivateKey->open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, "Error al leer el archivo", firmPrivateKey->fileName()+" "+firmPrivateKey->errorString());
            }
            if(!firmData->open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, "Error al leer el archivo", firmData->fileName()+" "+firmData->errorString());
            }
        }
    }
    else {
        ui->plainTextEdit_log->appendPlainText("Debe ingresar la frase de la Clave Privada para poder firmar.");
    }
}

void MainWindow::on_pushButton_verif_verificar_clicked()
{
    if ( !verifData->isOpen() && !verifFirma->isOpen() && !verifPublicKey->isOpen() ) {
        ui->plainTextEdit_log->appendPlainText("Error de verificacion. Archivos no se pudieron abrir");
        return;
    }
    verifData->close();
    verifFirma->close();
    verifPublicKey->close();

    QString commandParams = "cryptoEngine -v " + verifPublicKey->fileName() + " -i " + verifData->fileName();
    QString dir = QFileInfo(verifFirma->fileName()).absolutePath();
    if ( dir.at(dir.size()-1) != QChar('/') )
        dir.append("/");
    commandParams += " -d " + dir;

    QStringList commandParamsList = commandParams.split(" ");
    char **argv = new char*[commandParamsList.size()];
    int argc = commandParamsList.size();
    qDebug("Input:");
    qDebug(QString::number(argc).toStdString().c_str());
    for ( int i=0 ; i<commandParamsList.size() ; i++ ) {
        argv[i] = new char [strlen(commandParamsList.at(i).toStdString().c_str()) + 1];
        strcpy(argv[i], commandParamsList.at(i).toStdString().c_str());
        qDebug("%d) %s",i,argv[i]);
    }
    qDebug("=========================================");
    CryptoEngine* engine = new CryptoEngine( argc , argv );
    if ( engine->GetCryptoEngineStatus() == OK) {
        ui->plainTextEdit_log->appendPlainText("Verificando el archivo " + QFileInfo(verifData->fileName()).fileName() + " ...");
        ui->plainTextEdit_log->appendHtml("<html><font color=\"green\"><b>Verificado correctamente.</b></font></html>");
    }
    else {
        ui->plainTextEdit_log->appendHtml("<html><font color=\"red\"><b>Error de verificacion.</b></font></html>");
        if (!engine->GetCryptoEngineStatusString().isEmpty())
            ui->plainTextEdit_log->appendHtml("<html><font color=\"red\">"+engine->GetCryptoEngineStatusString()+"</font></html>");
    }

    //ReOpen stuff
    if(!verifPublicKey->open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Error al leer el archivo", verifPublicKey->fileName()+" "+verifPublicKey->errorString());
    }
    if(!verifData->open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Error al leer el archivo", verifData->fileName()+" "+verifData->errorString());
    }
    if(!verifFirma->open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Error al leer el archivo", verifFirma->fileName()+" "+verifFirma->errorString());
    }
}
