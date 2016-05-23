#include <cstring>
#include "firma.h"


Firma::Firma(unsigned int longitud){
    this->longitud = longitud;
    this->firma = new unsigned char[longitud];
    memset(this->firma,0,sizeof(unsigned char)*longitud);
}

Firma::~Firma(){
    delete[] this->firma;
}

void Firma::imprimir(std::ostream& salida){
    std::string strFirma;
    /*if(!binario){
        ByteUtils::convertHexArrayToString(std::string((char*)firma,longitud),strFirma);
        salida << strFirma;
    }else{*/
        salida.write((char*)firma,longitud);
    //}
}


Firma::operator unsigned char*(){
    return this->firma;
}

unsigned int* Firma::obtenerReferenciaALongitud(){
    return &this->longitud;
}

unsigned int Firma::obtenerLongitud(){
    return this->longitud;
}
