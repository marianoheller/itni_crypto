#ifndef CRYPTOENGINE_H
#define CRYPTOENGINE_H

/*
 * Define para que no haya errores de compatibilidad entre diferentes GCC's
 * Source: GCC 5 Release Notes/Dual ABI
 * https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dual_abi.html
 * */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#include <QString>
#include <QVector>


#include "verificador.h"
#include "firmado.h"
#include "firma.h"
#include "par_de_claves.h"
#include "open_ssl_state.h"

#include <openssl/pem.h>

#define ERROR_INTERNO		-1
#define ERROR_VERIFICACION	-2
#define ERROR_FIRMA			-3
#define OK					0



class CryptoEngine
{
public:
    CryptoEngine( int argc,char* argv[] );
    ~CryptoEngine();
    void showHelp();
    int firmar(QString nombreArchivoOrigen,QString nombreArchivoSalida,ParDeClaves& parDeClaves);
    int verificar(QString nombreArchivoOrigen,QString nombreArchivoSalida,ParDeClaves& parDeClaves);

private:
    int ejecutarParametros(int argc,char* argv[]);
    bool esParametro(char* str);

};

#endif // CRYPTOENGINE_H
