// Clave privada a utilizar en el proceso de firmado

#ifndef __PAR_DE_CLAVES_H__
#define __PAR_DE_CLAVES_H__


#include <string>
#include <cstring>
#include <openssl/fips.h>
#include <openssl/rsa.h>
#include <memory>

#include <QString>


class ParDeClaves{
    static unsigned int longitud_de_d_en_bits_default;
    static unsigned int longitud_de_n_en_bits_default;
    static short unsigned int exponente_default;
    static unsigned char d_default[];
    static unsigned char n_default[];

    static RSA* claveDefaultComoRSA();

    unsigned int longitudDeDEnBits;
    unsigned int longitudDeNEnBits;
    RSA* rsa;

public:

    ParDeClaves();
    ParDeClaves(int modulo,int exponente);
    ParDeClaves(QString filename,bool privada,QString frase);

    ~ParDeClaves();

    unsigned short int obtenerExponente();

    unsigned int obtenerLongitudDeDEnBits()const;

    unsigned int obtenerLongitudDeDEnBytes()const;

    unsigned int obtenerLongitudDeNEnBits()const;

    unsigned int obtenerLongitudDeNEnBytes()const;

    const unsigned char* obtenerD();

    operator RSA*()const;

    void imprimirClaves( QString filePath,  QString frase,bool encriptar);

    void imprimirPublica( QString filePath);

};

#endif // __PAR_DE_CLAVES_H__
