#include "cryptoengine.h"

CryptoEngine::CryptoEngine(int argc, char *argv[])
{
    try{
            OpenSSLState::instance().setFipsModeOn();
            OpenSSLState::instance().addAllAlgorithms();
        }catch(std::string ex){
            std::cout << "Ocurrio una excepcion: " << ex << " , abortando..." << std::endl;
            //return ERROR_INTERNO;
            return;
        }

        try{
            int val =  ejecutarParametros(argc,argv);
            OpenSSLState::instance().cleanAll();
            //return val;
            return;
        }catch(const char* mess){
            OpenSSLState::instance().cleanAll();
            std::cout << "Ocurrio una excepcion: " << mess << std::endl;
            //return ERROR_INTERNO;
            return;
        }

}



int CryptoEngine::ejecutarParametros(int argc,char* argv[])
{
    if (argc == 1){
        showHelp();
        return ERROR_INTERNO;
    }

    std::string workPath=".";
    bool generarClaves=false;
    int  accionIdx = -1;
    bool firmarArch=false;
    bool verificarArch=false;
    bool usarFrase=false;
    int usarFraseIdx=-1;
    bool inputList=false;
    int  inputListIdx=-1;

    for(int c=0;c<argc;c++){
        if(!strcmp(argv[c],"-g")){
            generarClaves = true;
            accionIdx=c;
        }

        if(!strcmp(argv[c], "-f")){
            firmarArch = true;
            accionIdx=c;
        }

        if(!strcmp(argv[c],"-v")){
            verificarArch = true;
            accionIdx=c;
        }

        if(!strcmp(argv[c],"-i")){
            inputList = true;
            inputListIdx=c;
        }

        if(!strcmp(argv[c],"-d")){
            if(c+1<argc && !strchr(argv[c+1],'-'))
                workPath.insert(0,argv[c+1]);
        }

        if(!strcmp(argv[c],"-e")){
            usarFrase = true;
            usarFraseIdx = c;
        }
    }

    if( (firmarArch && verificarArch) ||
        (generarClaves && firmarArch) ||
        (generarClaves && verificarArch)){
        showHelp();
        return ERROR_INTERNO;
    }

    if( (firmarArch && !inputList) ||
        (verificarArch && !inputList)){
        showHelp();
        return ERROR_INTERNO;
    }

    if(generarClaves){
        if(accionIdx+1<argc){
            std::string filename(argv[accionIdx+1]);
            ParDeClaves* claves = new ParDeClaves(1024,65537);
            std::string filenamePrivada = filename+".privada.pem";
            std::string filenamePublica = filename+".publica.pem";

            std::string frase = "";
            if(usarFrase && usarFraseIdx+1<argc && !esParametro(argv[usarFraseIdx+1]))
              frase = std::string(argv[usarFraseIdx+1]);

            // La privada contiene el par de claves, utilizar el binario de la openssl
            // si se quiere extraer la publica
            claves->imprimirPublica(filenamePublica);
            claves->imprimirClaves(filenamePrivada,frase,usarFrase);

            delete claves;

            return OK;
        }else{
            showHelp();
            return ERROR_INTERNO;
        }
    }else if(firmarArch || verificarArch){
        std::vector<std::string> aInputList;

        if(verificarArch && usarFrase){
          showHelp();
          return ERROR_INTERNO;
        }

        if(inputList){
            for(int i=inputListIdx+1; (i<argc) && !esParametro(argv[i]) ; i++){
                aInputList.push_back(std::string(argv[i]));
            }
        }

        std::string frase = "";
        if(usarFrase && !esParametro(argv[usarFraseIdx+1]))
            frase = std::string(argv[usarFraseIdx+1]);

        ParDeClaves* claves;
        if( (accionIdx+1<argc) && !esParametro(argv[accionIdx+1])){
            claves = new ParDeClaves(std::string(argv[accionIdx+1]),firmarArch,frase);
        }else{
            claves = new ParDeClaves();
        }

        int retVal = OK;
        for(int i=0;i<aInputList.size();i++){
            std::string nombreArchivoOrigen = aInputList[i];
            std::string nombreArchivoSalida = workPath + "/" +
                nombreArchivoOrigen.substr(
                    nombreArchivoOrigen.find_last_of("/")+1,
                    nombreArchivoOrigen.length()) + ".sign";

            if(firmarArch){
                firmar(nombreArchivoOrigen,nombreArchivoSalida,*claves);
            }else if(verificarArch){
                retVal = verificar(nombreArchivoOrigen,nombreArchivoSalida,*claves);
            }
        }

        delete claves;

        return retVal;
    }
    return 0;
}


int CryptoEngine:: verificar(const std::string& nombreArchivoOrigen,const std::string& nombreArchivoSalida,ParDeClaves& parDeClaves)
{
    std::ifstream archivoMensaje(nombreArchivoOrigen.c_str(), std::fstream::binary);
    std::ifstream archivoFirma(nombreArchivoSalida.c_str());

    if (!archivoMensaje.is_open()){
        std::cout << "Se ignora la verificacion del archivo " << nombreArchivoOrigen << " debido a que no se pudo abrir. Compruebe si lo tipeo correctamente." << std::endl;
        return ERROR_INTERNO;
    }

    if (!archivoFirma.is_open()){
        std::cout << "Se ignora la verificacion del el archivo " << nombreArchivoOrigen << " debido a que no se encontro el archivo de firma " << nombreArchivoSalida << "." << std::endl;
        return ERROR_INTERNO;
    }

    bool verif = false;
    Verificador verificador;
    try{
        if (verificador.verificar(parDeClaves, archivoMensaje, archivoFirma)){
            std::cout << nombreArchivoSalida << " verifica." << std::endl;
            verif = true;
        } else {
            std::cout << "ERROR , " << nombreArchivoSalida << " NO verifica" << std::endl;
        }
    }catch(std::string ex){
        std::cout << ex << std::endl;
    }

    archivoMensaje.close();
    archivoFirma.close();

    if(!verif)
        return ERROR_INTERNO;

    return OK;
}


bool CryptoEngine::esParametro(char* str){
    if(str==NULL)
        return false;

    if(strlen(str)==0)
        return false;

    return str[0]=='-';
}

void CryptoEngine::showHelp(){
    std::cout << "Existen 3 formas de uso: " << std::endl << std::endl;
    std::cout << "Generacion de claves: " << std::endl;
    std::cout << "./firmar -g salida [-e frase]" << std::endl;
    std::cout << "-g : Se genera un par de claves (n=1024,e=65537) y se almacenan en salida.privada.pem y salida.publica.pem"  << std::endl;
    std::cout << "-e : Si se indica este parametro se encripta la salida con usa frase secreta,si no se indica se pedira por la entrada estandar" << std::endl << std::endl;
    std::cout << "Firmado: "  << std::endl;
    std::cout << "./firmar -f [privada.pem] [-e frase] [-d carpeta_trabajo] -i archivos_a_utilizar"  << std::endl;
    std::cout << "-f : Firma los archivos, si no se indica archivo se utiliza una clave por defecto"  << std::endl;
    std::cout << "-d : Indica la carpeta de trabajo, esto es donde se almacena la firma.(def=.)"  << std::endl;
    std::cout << "-i : Se indican los archivos de entrada a procesar"  << std::endl << std::endl;
    std::cout << "-e : Se utiliza una frase para desencriptar la clave privada" << std::endl  << std::endl;
    std::cout << "Verificacion: "  << std::endl;
    std::cout << "./firmar -v [publica.pem] [-d carpeta_trabajo] -i archivos_a_utilizar"  << std::endl;
    std::cout << "-v : Verifica la firma de cada archivo con la clave pública, si no se indica archivo se utiliza una clave por defecto"  << std::endl;
    std::cout << "-d : Indica la carpeta de trabajo donde se busca el archivo con la firma para verificar.(def=.)"  << std::endl;
    std::cout << "-i : Se indican los archivos de entrada a procesar"  << std::endl;
    std::cout << "Ejemplo: "  << std::endl;
    std::cout << "./firmar -f my_privada.pem -i archivo1.cpp archivo2.cpp"  << std::endl;
    std::cout <<  std::endl;
    std::cout << "salida generada:"  << std::endl;
    std::cout << "archivo1.cpp.sign archivo2.cpp.sign"  << std::endl;
    std::cout <<  std::endl;
}
