#ifndef __OPEN_SSL_STATE_H__
#define __OPEN_SSL_STATE_H__

#include <openssl/fips.h>
#include <openssl/evp.h>


class OpenSSLState{
    bool isFipsOn;

    OpenSSLState(){
        isFipsOn = false;
    }

    ~OpenSSLState(){
    }
public:
    static OpenSSLState& instance(){
        static OpenSSLState state;
        return state;
    }

    void setFipsModeOn(){
        if(!isFipsOn){
            isFipsOn = true;
            if(!FIPS_mode_set(1)){
              throw std::string("Error al iniciar el modo FIPS");
            }
        }

    }

    void addAllDigests(){
        OpenSSL_add_all_digests();
    }

    void addAllCiphers(){
        OpenSSL_add_all_ciphers();
    }

    void addAllAlgorithms(){
        OpenSSL_add_all_algorithms();
    }

    void cleanAll(){
        /* No comprendo mucho el proceso de cleanup
           pero sin esto siempre queda memoria reservada al finalizar el programa*/
        CRYPTO_cleanup_all_ex_data();
        EVP_cleanup();
    }

};

#endif // __OPEN_SSL_STATE_H__
