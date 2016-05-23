#include "verificador.h"

#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/fips.h>
#include <cstring>


bool Verificador::verificar(ParDeClaves& parDeClaves, std::istream& mensaje, std::istream& firma){
    std::string firmaString;
    leerInput(firma, firmaString);

    //ByteUtils::convertStringBytesToHex(firmaString, firmaString);
    bool verifica =  verificarFirma(parDeClaves,firmaString, mensaje);

    return verifica;
}

void Verificador::leerInput(std::istream& input, std::string& contenido){
    while(!input.eof()){
        unsigned char buffer[1024];
        input.read((char*)buffer,1024);
        contenido.append((char*) buffer, input.gcount());
        //contenido += std::string((char*) buffer, input.gcount());
    }
}

bool Verificador::verificarFirma(ParDeClaves& parDeClaves,const std::string& firma,std::istream& mensaje){
    RSA* rsa = parDeClaves;

    EVP_PKEY* pk = EVP_PKEY_new();
    EVP_MD_CTX ctx;

    EVP_PKEY_set1_RSA(pk,parDeClaves);

    EVP_MD_CTX_init(&ctx);
    M_EVP_MD_CTX_set_flags(&ctx, EVP_MD_CTX_FLAG_PAD_PKCS1/*EVP_MD_CTX_FLAG_PAD_X931*/);
    EVP_VerifyInit_ex(&ctx, EVP_get_digestbynid(NID_sha1), NULL);

    while(!mensaje.eof()){
        unsigned char buffer[tamanio_de_buffer_default];
        mensaje.read((char*)buffer,tamanio_de_buffer_default);
        EVP_VerifyUpdate(&ctx, buffer, mensaje.gcount());
        mensaje.peek();
    }

    int ok = EVP_VerifyFinal(&ctx, (unsigned char*)firma.c_str(), firma.size(), pk);
    EVP_MD_CTX_cleanup(&ctx);

    // El free esta en el constructor de ParDeClaves no puede
    // liberarse aca
    //FIPS_rsa_free(pk.pkey.rsa);

    EVP_PKEY_free(pk);

    return ok==1;
}
