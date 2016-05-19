#ifndef __FIRMADO_H__
#define __FIRMADO_H__

#include <stddef.h>
#include <openssl/fips.h>

#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/err.h>
#include <openssl/x509v3.h>

//#include "fipsmod/include/openssl/fips.h"
#include "par_de_claves.h"
#include "firma.h"

class Firmado{
private:
    static const unsigned int tamanio_de_buffer_default = 2048;

    Firmado();

    ~Firmado();
public:
    static Firmado& instance(){
        static Firmado aInstance;
        return aInstance;
    }

    void inicializar();

    Firma* firmar( const ParDeClaves& ParDeClaves , std::istream& mensaje );
};

#endif //__FIRMADO_H__
