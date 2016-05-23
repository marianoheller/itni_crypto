#ifndef __FIRMA_H__
#define __FIRMA_H__

#include "byte_utils.h"


class Firma{
    unsigned char* firma;
    unsigned int longitud;

public:
    Firma(unsigned int longitud);

    ~Firma();

    void imprimir(std::ostream& salida);

    operator unsigned char*();
    unsigned int obtenerLongitud();
    unsigned int* obtenerReferenciaALongitud();
};

#endif //__FIRMA_H__
