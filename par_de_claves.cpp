#include "par_de_claves.h"
#include "par_de_claves_default.h"
#include "big_num.h"

#include <openssl/pem.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <string.h>

#include <openssl/rand.h>



ParDeClaves::ParDeClaves(){
    this->rsa = claveDefaultComoRSA();
    longitudDeDEnBits = ParDeClaves::longitud_de_d_en_bits_default;
    longitudDeNEnBits = ParDeClaves::longitud_de_n_en_bits_default;
}

ParDeClaves::ParDeClaves(int modulo,int exponente){
    this->rsa = FIPS_rsa_new();
    // FIPS_rsa_new no setea las referencias en 1 es necesario hacerlo a mano
    this->rsa->references=1;

    // No hace falta configurar la semilla, al iniciar el modo fips se realiza
    //RAND_poll();
    BIGNUM* e = BN_new();
    BN_set_word(e,65537);
    RSA_X931_generate_key_ex(this->rsa, modulo, e, NULL);
    BN_free(e);

    longitudDeDEnBits = modulo;
    longitudDeNEnBits = modulo;
}

ParDeClaves::ParDeClaves(QString filename, bool privada,QString frase){
    FILE* fp = fopen(filename.toStdString().c_str(),"rb");
    this->rsa = FIPS_rsa_new();
    // FIPS_rsa_new no setea las referencias en 1 es necesario hacerlo a mano
    this->rsa->references = 1;

    if(privada){

        if(frase.isEmpty()){
            if(!PEM_read_RSAPrivateKey(fp,&this->rsa,0,0)){
                fclose(fp);
                throw "Error al leer la clave";
            }
        }else{
            if(!PEM_read_RSAPrivateKey(fp,&this->rsa,NULL,(void *)frase.toStdString().c_str())){
                fclose(fp);
                throw "Error al leer la clave";
            }
        }
        longitudDeDEnBits = BN_num_bytes(this->rsa->d)*8;
    }else{
        if(!PEM_read_RSA_PUBKEY(fp,&this->rsa,0,0)){
            fclose(fp);
            throw "Error al leer la clave";
        }
    }
    fclose(fp);

    longitudDeNEnBits = BN_num_bytes(this->rsa->n)*8;
}

ParDeClaves::~ParDeClaves(){
    FIPS_rsa_free(this->rsa);
}

unsigned short int ParDeClaves::obtenerExponente(){
    return (unsigned short int)atoi(BN_bn2dec(this->rsa->e));
}

const unsigned char* ParDeClaves::obtenerD(){
    return (const unsigned char*)BN_bn2hex(this->rsa->d);
}

unsigned int ParDeClaves::obtenerLongitudDeDEnBits()const{
    return longitudDeDEnBits;
}

unsigned int ParDeClaves::obtenerLongitudDeDEnBytes()const{
    return longitudDeDEnBits/8;
}

unsigned int ParDeClaves::obtenerLongitudDeNEnBits()const{
    return longitudDeNEnBits;
}

unsigned int ParDeClaves::obtenerLongitudDeNEnBytes()const{
    return longitudDeNEnBits/8;
}

ParDeClaves::operator RSA*()const{
    return this->rsa;
}

void ParDeClaves::imprimirClaves( QString filePath,QString frase,bool encriptar){
    FILE* fp = fopen(filePath.toStdString().c_str(),"wb");
    if(fp==NULL)
        throw "Error al abrir el archivo";


    if(!frase.isEmpty() || encriptar){
        if(!frase.isEmpty()){
            if(!PEM_write_RSAPrivateKey(fp,this->rsa,EVP_des_ede3_cbc(),(unsigned char*)frase.toStdString().c_str(),frase.length(),NULL,NULL)){
                fclose(fp);
                throw "Error al escribir la clave";
            }
        }else{
            if(!PEM_write_RSAPrivateKey(fp,this->rsa,EVP_des_ede3_cbc(),NULL,0,NULL,NULL)){
                fclose(fp);
                throw "Error al escribir la clave";
            }
        }
    }else{
        if(!PEM_write_RSAPrivateKey(fp,this->rsa,0,0,0,0,0)){
            fclose(fp);
            throw "Error al escribir la clave";
        }
    }

    fclose(fp);
}

void ParDeClaves::imprimirPublica( QString filePath){
    FILE* fp = fopen(filePath.toStdString().c_str(),"wb");
    if(fp==NULL)
        throw "Error al abrir el archivo";

    if(!PEM_write_RSA_PUBKEY(fp,this->rsa)){
        fclose(fp);
        throw "Error al escribir la clave";
    }

    fclose(fp);
}
