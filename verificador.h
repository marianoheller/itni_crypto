#ifndef __VERIFICADOR_H__
#define __VERIFICADOR_H__

#include "big_num.h"
#include "par_de_claves.h"

#include <fstream>


class Verificador{
private:
    static const unsigned int tamanio_de_buffer_default = 2048;

public:
    bool verificar(ParDeClaves& parDeClaves, std::istream& mensaje, std::istream& firma);
    void leerInput(std::istream& input, std::string& contenido);

private:
    bool verificarFirma(ParDeClaves& parDeClaves,const std::string& firma,std::istream& mensaje);
};



#endif //__VERIFICADOR_H__
