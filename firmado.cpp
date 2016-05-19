#include "firmado.h"

Firmado::Firmado(){

}

Firmado::~Firmado(){

}

Firma* Firmado::firmar( const ParDeClaves& ParDeClaves , std::istream& mensaje ){
    /* EVP_PKEY structure */

    EVP_PKEY* pk = EVP_PKEY_new();
    EVP_MD_CTX ctx;

    EVP_PKEY_set1_RSA(pk,ParDeClaves);

    //pk.type = EVP_PKEY_RSA;
    //Esto devuelve el RSA de ParDeClaves, NO LIBERAR!
    //pk.pkey.rsa = ParDeClaves;

    // Firmado
    Firma* firma = new Firma(ParDeClaves.obtenerLongitudDeNEnBytes());

    EVP_MD_CTX_init(&ctx);
    M_EVP_MD_CTX_set_flags(&ctx, EVP_MD_CTX_FLAG_PAD_PKCS1/*EVP_MD_CTX_FLAG_PAD_X931*/);
    EVP_SignInit_ex(&ctx, EVP_get_digestbynid(NID_sha1), NULL);

    while(!mensaje.eof()){
        unsigned char buffer[tamanio_de_buffer_default];
        mensaje.read((char*)buffer,tamanio_de_buffer_default);
        EVP_SignUpdate(&ctx, buffer, mensaje.gcount());
        mensaje.peek();
    }

    EVP_SignFinal(&ctx, *firma, (unsigned int *)firma->obtenerReferenciaALongitud(), pk);
    EVP_MD_CTX_cleanup(&ctx);

    // El free esta en el constructor de ParDeClaves no puede
    // liberarse aca
    //FIPS_rsa_free(pk.pkey.rsa);

    EVP_PKEY_free(pk);

    return firma;
}
